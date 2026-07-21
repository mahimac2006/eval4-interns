#!/bin/bash
# unified-PAGENT (kernel mode) PoC submission client — the agent's only link to
# the dynamic validator. POSTs your PoC **C source** to the validator, which
# cross-compiles it with the trusted Buildroot toolchain, boots a QEMU VM running
# the sanitizer-instrumented kernel, runs the PoC, and prints the JSON verdict
# (sanitizer crash report + region match, or coverage/profiling on no-crash).
#
# Usage:
#   bash submit.sh <poc_source.c>                 # default sanitizer (kasan)
#   bash submit.sh <poc_source.c> --name my_poc   # set the PoC name
#   bash submit.sh <poc_source.c> --sanitizer kasan|kmsan|ubsan
set -euo pipefail

VALIDATOR_URL="http://127.0.0.1:8650"
DEFAULT_SANITIZER="kasan"

if [ "$#" -lt 1 ]; then
    echo "usage: bash submit.sh <poc_source.c> [--name NAME] [--sanitizer kasan|kmsan|ubsan]" >&2
    exit 2
fi
POC="$1"; shift
if [ ! -f "$POC" ]; then
    echo "poc source not found: $POC" >&2
    exit 2
fi

POC_NAME="$(basename "$POC" .c)"
SANITIZER="$DEFAULT_SANITIZER"
while [ "$#" -gt 0 ]; do
    case "$1" in
        --name)      POC_NAME="$2"; shift 2 ;;
        --sanitizer) SANITIZER="$2"; shift 2 ;;
        *)           shift ;;
    esac
done

META="$(python3 - "$POC_NAME" "$SANITIZER" <<'PY'
import json, sys
print(json.dumps({"poc_name": sys.argv[1], "sanitizer": sys.argv[2]}))
PY
)"

# POST the PoC; capture the full JSON, then print a COMPACT verdict (small enough
# to not be truncated by the agent CLI) while persisting the full per-function
# coverage + full verdict to workspace files for drill-down.
TMPR="$(mktemp)"
trap 'rm -f "$TMPR"' EXIT
curl -sS -X POST "$VALIDATOR_URL/validate" \
    -F "file=@${POC};type=text/x-csrc" \
    -F "metadata=${META}" > "$TMPR"

python3 - "$TMPR" <<'PY'
import json, sys
try:
    r = json.load(open(sys.argv[1]))
except Exception:
    sys.stdout.write(open(sys.argv[1]).read()); sys.exit(0)

# persist full detail to the workspace (read these on demand)
cov = r.get("coverage")
if cov:
    json.dump(cov, open(".last_coverage.json", "w"), indent=2)
json.dump(r, open(".last_response.json", "w"), indent=2)

# crash excerpt: the sanitizer report head (BUG line + a few frames)
out = (r.get("output") or "").replace("\r", "")
lines = out.split("\n")
exc = ""
for i, l in enumerate(lines):
    if "BUG:" in l or "UBSAN:" in l:
        exc = "\n".join(lines[i:i + 12]); break
if not exc:
    exc = "\n".join(lines[:8])

compact = {
    "verdict": r.get("verdict"),
    "pass_reason": r.get("pass_reason"),        # "sanitizer" | "pattern" | null
    "pattern_gate_enabled": r.get("pattern_gate_enabled"),
    "pattern_match": r.get("pattern_match"),
    "crash_type": r.get("crash_type"),
    "crash_location": r.get("crash_location"),
    "top_app_frames": (r.get("top_app_frames") or [])[:5],
    "signature_match": r.get("signature_match"),
    "reproducible": r.get("reproducible"),
    "sanitizer_variant": r.get("sanitizer_variant"),
    "profiling": r.get("profiling"),
    "coverage_summary": r.get("coverage_summary"),
    "crash_excerpt": exc[:700],
    "note": ("full per-function coverage -> .last_coverage.json ; "
             "full verdict (incl. complete dmesg) -> .last_response.json"),
}
if r.get("error"):
    compact["error"] = r.get("error")
print(json.dumps(compact, indent=2))
PY
