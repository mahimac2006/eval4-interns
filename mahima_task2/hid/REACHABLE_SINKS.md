# Reachable WMI-3 sinks — drivers/hid (kernel 6.6.25)

**ABI source:** `ioctl_ops:hiddev_fops[...], ioctl_ops:hidraw_ops[...]`

**Resolved source handlers (13):** ioctl_ops:hiddev_fops[fasync] (hiddev_fasync), ioctl_ops:hiddev_fops[open] (hiddev_open), ioctl_ops:hiddev_fops[poll] (hiddev_poll), ioctl_ops:hiddev_fops[read] (hiddev_read), ioctl_ops:hiddev_fops[release] (hiddev_release), ioctl_ops:hiddev_fops[write] (hiddev_write), ioctl_ops:hidraw_ops[fasync] (hidraw_fasync), ioctl_ops:hidraw_ops[unlocked_ioctl] (hidraw_ioctl), ioctl_ops:hidraw_ops[open] (hidraw_open), ioctl_ops:hidraw_ops[poll] (hidraw_poll), ioctl_ops:hidraw_ops[read] (hidraw_read), ioctl_ops:hidraw_ops[release] (hidraw_release), ioctl_ops:hidraw_ops[write] (hidraw_write)

Method: native CodeQL build-mode=none call graph; BFS from source handlers to each WMI-3 sink's enclosing function (direct-call reachability). Sinks limited to those in `drivers/hid/*.c` (header-inlined sinks are generic kernel code, not evaluated).

**In-module distinct sinks:** 274   **Reachable from source:** 1

| source (struct[slot]) | sink file:line | sink func | call chain |
|---|---|---|---|
| ioctl_ops:hidraw_ops[open] | drivers/hid/hidraw.c:309 | hidraw_open | hidraw_open |
