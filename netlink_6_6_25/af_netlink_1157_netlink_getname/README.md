# af_netlink.c:1157 - netlink_getname

PAGENT run: `netlink_6_6_25_wmi3_af_netlink_1157_netlink_getname-c225cdf8`

Finding: WMI-3, attacker-determined content in an authoritative position.

Target: `net/netlink/af_netlink.c:1157`, `netlink_getname`.

Result: `NO_POC`

Notes:
- PAGENT ran as non-root through the validated Docker/QEMU path.
- Validator used KASAN with `bzImage_kasan_nogcov_extroot_nopsmgr`.
- The final PoC exited 0 and demonstrated the WMI-3 semantic flow by binding `nl_groups=0xdeadbeef` and observing the same value returned by `getsockname`.
- No KASAN/UBSAN sanitizer crash fired, so the validator returned `FAIL` for the final candidate and PAGENT reported `NO_POC`.
- GCOV coverage is unavailable because the validated image intentionally disables `CONFIG_GCOV_KERNEL`.

Included artifacts:
- `result.json`: top-level PAGENT result.
- `last_response.json`: final validator response.
- `last_coverage.json`: final coverage metadata.
- `NO_POC_REASON.txt`: PAGENT's blocker analysis.
- `poc.c`: final candidate PoC from the run.
- `sa_report.json`: WMI-3 SA report used for this sink.
- `validator.log`: validator request log.
