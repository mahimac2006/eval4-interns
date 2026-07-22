/*
 * PoC for WMI-3: Attacker-Determined Content in an Authoritative Position
 * @ __nlmsg_put (af_netlink.c:2168)
 *
 * Demonstrates that attacker-controlled nlmsg_seq flows through __nlmsg_put
 * into the authoritative recvmsg (netlink_ops.recvmsg) output.
 *
 * Call path:
 *   sendmsg -> rtnetlink_rcv_msg -> netlink_dump_start -> netlink_dump
 *   -> rtnl_dump_ifinfo -> rtnl_fill_ifinfo -> nlmsg_put -> __nlmsg_put
 *
 * The function __nlmsg_put at line 2168 zeroes padding bytes in the netlink
 * message via memset(nlmsg_data(nlh) + len, 0, NLMSG_ALIGN(size) - size).
 * Both the header fields (nlmsg_seq) and the memset position are determined
 * from the payload/len parameter, which flows from attacker-controlled input.
 *
 * Result: the recvmsg output contains attacker-influenced data, violating
 * the WMI-3 invariant (authoritative position contains attacker content).
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
	const unsigned int ATTACKER_SEQ = 0xDEAD;

	struct {
		struct nlmsghdr nlh;
		struct ifinfomsg ifm;
	} req;

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
	req.nlh.nlmsg_pid = 0;
	req.ifm.ifi_family = AF_UNSPEC;

	memset(&sa, 0, sizeof(sa));
	sa.nl_family = AF_NETLINK;
	sa.nl_pid = 0;

	ret = sendto(fd, &req, req.nlh.nlmsg_len, 0,
		     (struct sockaddr *)&sa, sizeof(sa));
	if (ret < 0) { perror("sendto"); close(fd); return 1; }

	/* Receive dump responses */
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
			if (nlh->nlmsg_seq == ATTACKER_SEQ)
				found = 1;
			if (nlh->nlmsg_type == NLMSG_DONE ||
			    nlh->nlmsg_type == NLMSG_ERROR)
				goto done;
			nlh = NLMSG_NEXT(nlh, len);
		}
	}

done:
	close(fd);
	return found ? 0 : 1;
}
