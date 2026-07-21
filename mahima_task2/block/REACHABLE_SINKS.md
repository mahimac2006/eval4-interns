# Reachable WMI-3 sinks — drivers/block (kernel 6.6.25)

**ABI source:** `ioctl_ops:lo_fops[ioctl,release], ioctl_ops:loop_ctl_fops[ioctl,open]`

**Resolved source handlers (4):** ioctl_ops:lo_fops[free_disk] (lo_free_disk), ioctl_ops:lo_fops[ioctl] (lo_ioctl), ioctl_ops:lo_fops[release] (lo_release), ioctl_ops:loop_ctl_fops[unlocked_ioctl] (loop_control_ioctl)

Method: native CodeQL build-mode=none call graph; BFS from source handlers to each WMI-3 sink's enclosing function (direct-call reachability). Sinks limited to those in `drivers/block/*.c` (header-inlined sinks are generic kernel code, not evaluated).

**In-module distinct sinks:** 253   **Reachable from source:** 5

| source (struct[slot]) | sink file:line | sink func | call chain |
|---|---|---|---|
| ioctl_ops:lo_fops[ioctl] | drivers/block/loop.c:608 | loop_change_fd | lo_ioctl → loop_change_fd |
| ioctl_ops:lo_fops[ioctl] | drivers/block/loop.c:744 | loop_sysfs_init | lo_ioctl → loop_configure → loop_sysfs_init |
| ioctl_ops:loop_ctl_fops[unlocked_ioctl] | drivers/block/loop.c:2037 | loop_add | loop_control_ioctl → loop_add |
| ioctl_ops:loop_ctl_fops[unlocked_ioctl] | drivers/block/loop.c:2079 | loop_add | loop_control_ioctl → loop_add |
| ioctl_ops:loop_ctl_fops[unlocked_ioctl] | drivers/block/loop.c:2080 | loop_add | loop_control_ioctl → loop_add |
