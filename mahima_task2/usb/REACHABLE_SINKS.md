# Reachable WMI-3 sinks — drivers/usb (6.6.25)

Total distinct sinks: 702  |  Reachable from given USB sources: 13

Resolved source handlers (23) from: ioctl_ops:hub_driver[disconnect], ioctl_ops:hub_driver[post_reset], ioctl_ops:hub_driver[pre_reset], ioctl_ops:hub_driver[probe], ioctl_ops:hub_driver[unlocked_ioctl], ioctl_ops:mon_fops_binary[mmap], ioctl_ops:mon_fops_binary[open], ioctl_ops:mon_fops_binary[poll], ioctl_ops:mon_fops_binary[read], ioctl_ops:mon_fops_binary[release], ioctl_ops:mon_fops_binary[unlocked_ioctl], ioctl_ops:usbdev_file_operations[mmap], ioctl_ops:usbdev_file_operations[open], ioctl_ops:usbdev_file_operations[poll], ioctl_ops:usbdev_file_operations[read], ioctl_ops:usbdev_file_operations[release], ioctl_ops:usbdev_file_operations[unlocked_ioctl], ioctl_ops:usblp_fops[open], ioctl_ops:usblp_fops[poll], ioctl_ops:usblp_fops[read], ioctl_ops:usblp_fops[release], ioctl_ops:usblp_fops[unlocked_ioctl], ioctl_ops:usblp_fops[write]

| source (struct[slot]) | sink file:line | sink func | call chain |
|---|---|---|---|
| ioctl_ops:usbdev_file_operations[mmap] | drivers/usb/core/devio.c:260 | usbdev_mmap | usbdev_mmap |
| ioctl_ops:usbdev_file_operations[mmap] | drivers/usb/core/devio.c:263 | usbdev_mmap | usbdev_mmap |
| ioctl_ops:usbdev_file_operations[release] | drivers/usb/core/devio.c:422 | free_async | usbdev_release → free_async |
| ioctl_ops:usbdev_file_operations[open] | drivers/usb/core/devio.c:1059 | usbdev_open | usbdev_open |
| ioctl_ops:usbdev_file_operations[open] | drivers/usb/core/devio.c:1060 | usbdev_open | usbdev_open |
| ioctl_ops:usbdev_file_operations[unlocked_ioctl] | drivers/usb/core/devio.c:1783 | proc_do_submiturb | usbdev_ioctl → usbdev_do_ioctl → proc_submiturb → proc_do_submiturb |
| ioctl_ops:usbdev_file_operations[unlocked_ioctl] | drivers/usb/core/devio.c:1917 | proc_do_submiturb | usbdev_ioctl → usbdev_do_ioctl → proc_submiturb → proc_do_submiturb |
| ioctl_ops:hub_driver[probe] | drivers/usb/core/endpoint.c:163 | usb_create_ep_devs | hub_probe → usb_set_interface → create_intf_ep_devs → usb_create_ep_devs |
| ioctl_ops:hub_driver[probe] | drivers/usb/core/hub.c:1411 | hub_configure | hub_probe → hub_configure |
| ioctl_ops:hub_driver[probe] | drivers/usb/core/hub.c:1897 | hub_probe | hub_probe |
| ioctl_ops:hub_driver[probe] | drivers/usb/misc/onboard_usb_hub_pdevs.c:117 | onboard_hub_create_pdevs | hub_probe → onboard_hub_create_pdevs |
| ioctl_ops:mon_fops_binary[unlocked_ioctl] | drivers/usb/mon/mon_bin.c:1052 | mon_bin_ioctl | mon_bin_ioctl |
| ioctl_ops:mon_fops_binary[unlocked_ioctl] | drivers/usb/mon/mon_bin.c:1054 | mon_bin_ioctl | mon_bin_ioctl |
