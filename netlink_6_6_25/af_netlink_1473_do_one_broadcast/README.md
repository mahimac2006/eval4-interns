# netlink 6.6.25 WMI-3: af_netlink.c:1473

Sink: `net/netlink/af_netlink.c:1473`
Function: `do_one_broadcast`
Run directory: `stase_6_3_5/pagent_runs/netlink_6_6_25_wmi3_af_netlink_1473_do_one_broadcast-afd6228e`

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

The generated candidates exercised NETLINK_USERSOCK broadcast delivery,
multi-threaded broadcast stress, and NETLINK_ROUTE broadcast attempts. The
agent concluded that this WMI-3 finding is an information-flow integrity issue,
not a KASAN-visible memory-safety defect. GCOV was unavailable in this no-GCOV
image, so coverage-based confirmation was also unavailable.

## Included Artifacts

- `result.json`: PAGENT top-level result.
- `NO_POC_REASON.txt`: agent-written explanation of the no-PoC verdict.
- `last_response.json`: final validator response.
- `last_coverage.json`: final coverage sidecar.
- `validator.log`: validator lifecycle log.
- `sa_report.json`: SA finding used for the run.
- `poc*.c`: candidate PoCs generated and submitted during the run.
