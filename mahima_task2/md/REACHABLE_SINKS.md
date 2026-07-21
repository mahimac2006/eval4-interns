# Reachable WMI-3 sinks — drivers/md (kernel 6.6.25)

**ABI source:** `drm_ioctl:lookup_ioctl._ioctls, ioctl_ops:_ctl_fops, ioctl_ops:dm_blk_dops, ioctl_ops:dm_rq_blk_dops, ioctl_ops:md_fops`

**Resolved source handlers (12):** ioctl_ops:_ctl_fops[unlocked_ioctl] (dm_ctl_ioctl), ioctl_ops:_ctl_fops[open] (dm_open), ioctl_ops:_ctl_fops[poll] (dm_poll), ioctl_ops:_ctl_fops[release] (dm_release), ioctl_ops:md_fops[check_events] (md_check_events), ioctl_ops:md_fops[free_disk] (md_free_disk), ioctl_ops:md_fops[getgeo] (md_getgeo), ioctl_ops:md_fops[ioctl] (md_ioctl), ioctl_ops:md_fops[open] (md_open), ioctl_ops:md_fops[release] (md_release), ioctl_ops:md_fops[set_read_only] (md_set_read_only), ioctl_ops:md_fops[submit_bio] (md_submit_bio)

Method: native CodeQL build-mode=none call graph; BFS from source handlers to each WMI-3 sink's enclosing function (direct-call reachability). Sinks limited to those in `drivers/md/*.c` (header-inlined sinks are generic kernel code, not evaluated).

**In-module distinct sinks:** 598   **Reachable from source:** 29

| source (struct[slot]) | sink file:line | sink func | call chain |
|---|---|---|---|
| ioctl_ops:_ctl_fops[unlocked_ioctl] | drivers/md/dm-ioctl.c:1939 | copy_params | dm_ctl_ioctl → ctl_ioctl → copy_params |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:384 | read_file_page | md_ioctl → do_md_run → md_bitmap_load → md_bitmap_init_from_disk → read_file_page |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:486 | md_bitmap_update_sb | md_ioctl → hot_remove_disk → md_update_sb → md_bitmap_update_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:489 | md_bitmap_update_sb | md_ioctl → hot_remove_disk → md_update_sb → md_bitmap_update_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:497 | md_bitmap_update_sb | md_ioctl → hot_remove_disk → md_update_sb → md_bitmap_update_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:498 | md_bitmap_update_sb | md_ioctl → hot_remove_disk → md_update_sb → md_bitmap_update_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:500 | md_bitmap_update_sb | md_ioctl → hot_remove_disk → md_update_sb → md_bitmap_update_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:501 | md_bitmap_update_sb | md_ioctl → hot_remove_disk → md_update_sb → md_bitmap_update_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:502 | md_bitmap_update_sb | md_ioctl → hot_remove_disk → md_update_sb → md_bitmap_update_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:503 | md_bitmap_update_sb | md_ioctl → hot_remove_disk → md_update_sb → md_bitmap_update_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:598 | md_bitmap_new_disk_sb | md_ioctl → set_bitmap_file → md_bitmap_create → md_bitmap_new_disk_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:604 | md_bitmap_new_disk_sb | md_ioctl → set_bitmap_file → md_bitmap_create → md_bitmap_new_disk_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:605 | md_bitmap_new_disk_sb | md_ioctl → set_bitmap_file → md_bitmap_create → md_bitmap_new_disk_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:708 | md_bitmap_read_sb | md_ioctl → set_bitmap_file → md_bitmap_create → md_bitmap_read_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:747 | md_bitmap_read_sb | md_ioctl → set_bitmap_file → md_bitmap_create → md_bitmap_read_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:754 | md_bitmap_read_sb | md_ioctl → set_bitmap_file → md_bitmap_create → md_bitmap_read_sb |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:1838 | md_bitmap_free | md_ioctl → do_md_run → md_bitmap_destroy → md_bitmap_free |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:1912 | md_bitmap_create | md_ioctl → set_bitmap_file → md_bitmap_create |
| ioctl_ops:md_fops[ioctl] | drivers/md/md-bitmap.c:1918 | md_bitmap_create | md_ioctl → set_bitmap_file → md_bitmap_create |
| ioctl_ops:md_fops[ioctl] | drivers/md/md.c:168 | rdev_init_serial | md_ioctl → hot_add_disk → bind_rdev_to_array → mddev_create_serial_pool → rdev_init_serial |
| ioctl_ops:md_fops[ioctl] | drivers/md/md.c:2471 | bind_rdev_to_array | md_ioctl → hot_add_disk → bind_rdev_to_array |
| ioctl_ops:md_fops[ioctl] | drivers/md/md.c:2472 | bind_rdev_to_array | md_ioctl → hot_add_disk → bind_rdev_to_array |
| ioctl_ops:md_fops[ioctl] | drivers/md/md.c:2474 | bind_rdev_to_array | md_ioctl → hot_add_disk → bind_rdev_to_array |
| ioctl_ops:md_fops[ioctl] | drivers/md/md.c:3707 | md_import_device | md_ioctl → hot_add_disk → md_import_device |
| ioctl_ops:md_fops[ioctl] | drivers/md/md.c:6078 | md_run | md_ioctl → do_md_run → md_run |
| ioctl_ops:md_fops[ioctl] | drivers/md/md.c:6079 | md_run | md_ioctl → do_md_run → md_run |
| ioctl_ops:md_fops[ioctl] | drivers/md/md.c:6080 | md_run | md_ioctl → do_md_run → md_run |
| ioctl_ops:md_fops[ioctl] | drivers/md/md.c:6972 | md_add_new_disk | md_ioctl → md_add_new_disk |
| ioctl_ops:md_fops[ioctl] | drivers/md/md.c:7057 | hot_add_disk | md_ioctl → hot_add_disk |
