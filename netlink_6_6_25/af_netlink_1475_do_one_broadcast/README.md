# netlink 6.6.25 WMI-3: af_netlink.c:1475

Sink: `net/netlink/af_netlink.c:1475`
Function: `do_one_broadcast`
Run directory: `stase_6_3_5/pagent_runs/netlink_6_6_25_wmi3_af_netlink_1475_do_one_broadcast-190d9eb9`

## PAGENT Result

`NO_POC`

PAGENT ran against the 6.6.25 KASAN kernel image:

```text
/data/images/bzImage_kasan_nogcov_extroot_nopsmgr
```

The final validator response was `FAIL`, with no sanitizer crash and no
accepted region match:

```text
coverage_summary: call-path: do_one_broadcast x | NOT reached: do_one_broadcast
pattern_gate_enabled: false
sanitizer_variant: kernel
exit_code: 0
timed_out: false
```

The final PoC demonstrated netlink broadcast delivery by sending attacker-
controlled content to multiple subscribed receivers. PAGENT concluded that the
finding is a WMI-3 trust/integrity issue, not a KASAN-visible memory-safety
defect. GCOV was unavailable in this no-GCOV image, so coverage-based
confirmation was also unavailable.

## Included Artifacts

- `result.json`: PAGENT top-level result.
- `NO_POC_REASON.txt`: agent-written explanation of the no-PoC verdict.
- `last_response.json`: final validator response.
- `last_coverage.json`: final coverage sidecar.
- `validator.log`: validator lifecycle log.
- `sa_report.json`: SA finding used for the run.
- `poc_netlink_broadcast.c`: generated PoC submitted during the run.
