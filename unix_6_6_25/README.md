# stase eval4 — unix

## Pipeline summary

| Stage | What it does | Count |
|---|---|---|
| **SA (CodeQL)** | WMI rules flag candidate sites in source. | **4** detections |
| **Symex (KLEE)** | Replay symbolic execution over each candidate. | **4** confirmed / 0 discarded / 4 total |
| **Agent filter** | LLM review of SE replay + chain co-occurrence. | **4** kept / 0 dropped |
| **Concrete boot** | KASAN replay on real kernel. | pending (no kernel_image provided) |

---

## WMI-3 — Attacker Content in Authoritative Position

**WMI-3: Attacker-Determined Content in an Authoritative Position @ unix_detach_fds**
Site: `scm.c:unix_detach_fds` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/6be79974…/`](1_wmi_findings/findings/wmi-3/6be79974-a514-4e43-8d98-e23bdd46b13d/)

**WMI-3: Attacker-Determined Content in an Authoritative Position @ copy_peercred**
Site: `af_unix.c:copy_peercred` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/82329ed3…/`](1_wmi_findings/findings/wmi-3/82329ed3-38ad-48be-b8b3-812bca4a92e2/)

**WMI-3: Attacker-Determined Content in an Authoritative Position @ unix_peek_fds**
Site: `af_unix.c:unix_peek_fds` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/9bdb0cab…/`](1_wmi_findings/findings/wmi-3/9bdb0cab-44bf-474c-b317-24172fa17402/)

---

## Reference for `1_wmi_findings/findings/<uuid>/wmi.json`

| Field | Meaning |
|---|---|
| `operation.name` | identifier of the abstract operation |
| `operation.effects[]` | what the operation does — `type`, `arguments.destinations[]` (struct.field segments) |
| `trigger.function` | function where the bug fires |
| `trigger.file` | source file |
| `name` | human-readable WMI check identifier |
| `metadata.wmi_index` | WMI check number (1–4) |
| `metadata.verdict_kind` | `concrete_confirmed` \| `symex_explored` \| `static_candidate` |
| `metadata.detected_by[]` | SA detections — `{engine, rule, mechanism, file, line}` (SE-confirmed only) |
| `metadata.symex_oracle` | KLEE run record |
| `metadata.concrete_oracle` | Boot corroboration (when kernel_image provided) |

Internal pipeline stages: `2_sa_codeql/` (CodeQL output), `3_se_confirm/` (KLEE harnesses + SE confirm),
`4_concrete/` (replay filter + agent verdict). `detection_summary.csv` is a per-mechanism roll-up.
