# Reachable WMI-3 sinks — drivers/gpu/drm/vgem (kernel 6.6.25)

**ABI source:** `drm_ioctl:vgem_driver, drm_ioctl:vgem_driver_fops, drm_ioctl:vgem_ioctls`

**Resolved source handlers (3):** drm_ioctl:vgem_driver[gem_create_object] (vgem_gem_create_object), drm_ioctl:vgem_driver[open] (vgem_open), drm_ioctl:vgem_driver[postclose] (vgem_postclose)

Method: native CodeQL build-mode=none call graph; BFS from source handlers to each WMI-3 sink's enclosing function (direct-call reachability). Sinks limited to those in `drivers/gpu/drm/vgem/*.c` (header-inlined sinks are generic kernel code, not evaluated).

**In-module distinct sinks:** 1   **Reachable from source:** 1

| source (struct[slot]) | sink file:line | sink func | call chain |
|---|---|---|---|
| drm_ioctl:vgem_driver[open] | drivers/gpu/drm/vgem/vgem_drv.c:68 | vgem_open | vgem_open |
