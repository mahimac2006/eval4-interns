/*
 * PoC for WMI-3: Attacker-Determined Content in an Authoritative Position
 * @ __nlmsg_put (af_netlink.c:2168)
 *
 * Demonstrates: attacker-controlled sequence number flows through __nlmsg_put
 * into the authoritative recvmsg output (netlink_ops.recvmsg).
 *
 * Call path: sendmsg -> rtnetlink_rcv_msg -> netlink_dump_start -> netlink_dump
 *            -> cb->dump (rtnl_dump_ifinfo) -> rtnl_fill_ifinfo -> nlmsg_put
 *            -> __nlmsg_put
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
	int fd;
	struct sockaddr_nl sa;
	struct {
		struct nlmsghdr nlh;
		struct ifinfomsg ifm;
	} req;
	char buf[MAX_PAYLOAD];
	struct iovec iov;
	struct msghdr msg;
	struct nlmsghdr *nlh;
	ssize_t len;
	int ret;
	int found_attacker_seq = 0;

	printf("=== WMI-3 PoC: Attacker Content in Authoritative Position ===\n");
	printf("Target: __nlmsg_put at af_netlink.c:2168\n");
	printf("Target memory: netlink_ops.recvmsg\n\n");

	fd = socket(AF_NETLINK, SOCK_RAW | SOCK_CLOEXEC, NETLINK_ROUTE);
	if (fd < 0) {
		perror("socket");
		return 1;
	}

	memset(&sa, 0, sizeof(sa));
	sa.nl_family = AF_NETLINK;
	if (bind(fd, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
		perror("bind");
		close(fd);
		return 1;
	}

	/* Build RTM_GETLINK dump request with attacker-controlled seq=0xDEAD */
	memset(&req, 0, sizeof(req));
	req.nlh.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
	req.nlh.nlmsg_type = RTM_GETLINK;
	req.nlh.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
	req.nlh.nlmsg_seq = 0xDEAD;
	req.nlh.nlmsg_pid = 0;
	req.ifm.ifi_family = AF_UNSPEC;

	memset(&sa, 0, sizeof(sa));
	sa.nl_family = AF_NETLINK;
	sa.nl_pid = 0;

	printf("[SEND] Sending RTM_GETLINK dump with attacker seq=0xDEAD\n");
	ret = sendto(fd, &req, req.nlh.nlmsg_len, 0,
		     (struct sockaddr *)&sa, sizeof(sa));
	if (ret < 0) {
		perror("sendto");
		close(fd);
		return 1;
	}
	printf("[SEND] sendto returned %d (OK)\n\n", ret);

	/* Receive dump responses */
	iov.iov_base = buf;
	iov.iov_len = sizeof(buf);
	memset(&msg, 0, sizeof(msg));
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	printf("[RECV] Reading dump responses...\n");
	while (1) {
		len = recvmsg(fd, &msg, 0);
		if (len < 0) {
			if (errno == EINTR) continue;
			perror("recvmsg");
			break;
		}
		if (len == 0) break;

		nlh = (struct nlmsghdr *)buf;
		while (NLMSG_OK(nlh, len)) {
			printf("[RECV] type=%-3u len=%-5u seq=0x%04x pid=%u\n",
			       nlh->nlmsg_type, nlh->nlmsg_len,
			       nlh->nlmsg_seq, nlh->nlmsg_pid);

			/* Check if attacker-controlled seq is reflected */
			if (nlh->nlmsg_seq == 0xDEAD) {
				found_attacker_seq = 1;
				printf("[WMI-3] Attacker-controlled seq (0xDEAD) found "
				       "in recvmsg output!\n");
				printf("[WMI-3] This demonstrates attacker-determined "
				       "content in authoritative position\n");
				printf("[WMI-3] (netlink_ops.recvmsg) via __nlmsg_put\n");
			}

			if (nlh->nlmsg_type == NLMSG_DONE ||
			    nlh->nlmsg_type == NLMSG_ERROR)
				goto done;
			nlh = NLMSG_NEXT(nlh, len);
		}
	}

done:
	printf("\n=== RESULT ===\n");
	if (found_attacker_seq) {
		printf("PASS: Attacker-controlled sequence number reaches recvmsg output\n");
		printf("via __nlmsg_put. WMI-3 violation confirmed.\n");
	} else {
		printf("FAIL: Could not demonstrate attacker-controlled data in recvmsg output\n");
	}

	close(fd);
	return found_attacker_seq ? 0 : 1;
}
