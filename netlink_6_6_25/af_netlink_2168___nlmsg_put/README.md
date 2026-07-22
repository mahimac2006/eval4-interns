# netlink 6.6.25 WMI-3: af_netlink.c:2168

Sink: `net/netlink/af_netlink.c:2168`
Function: `__nlmsg_put`
Run directory: `stase_6_3_5/pagent_runs/netlink_6_6_25_wmi3_af_netlink_2168___nlmsg_put-98055dbc`

## PAGENT Result

`NO_POC`

PAGENT ran against the 6.6.25 KASAN kernel image:

```text
/data/images/bzImage_kasan_nogcov_extroot_nopsmgr
```

The final validator response was `FAIL`, with no sanitizer crash and no
accepted region match:

```text
coverage_summary: call-path: __nlmsg_put x | NOT reached: __nlmsg_put
pattern_gate_enabled: false
sanitizer_variant: kernel
```

The strongest generated PoCs demonstrated semantic WMI-3 behavior: an
attacker-controlled netlink sequence value (`0xdead`) appeared in
`recvmsg` responses flowing through the netlink dump path. No KASAN-visible
memory-safety crash was produced. GCOV was unavailable in this no-GCOV image,
so coverage-based confirmation was also unavailable.

## Included Artifacts

- `result.json`: PAGENT top-level result.
- `NO_POC_REASON.txt`: agent-written explanation of the no-PoC verdict.
- `last_response.json`: final validator response.
- `last_coverage.json`: final coverage sidecar.
- `validator.log`: validator lifecycle log.
- `sa_report.json`: SA finding used for the run.
- `poc*.c`: candidate PoCs generated and submitted during the run.
