/*
 * PoC: RTM_GETLINK dump to trigger __nlmsg_put
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

	printf("Opening NETLINK_ROUTE socket...\n");
	fd = socket(AF_NETLINK, SOCK_RAW | SOCK_CLOEXEC, NETLINK_ROUTE);
	if (fd < 0) {
		perror("socket");
		return 1;
	}

	/* Bind the socket */
	memset(&sa, 0, sizeof(sa));
	sa.nl_family = AF_NETLINK;
	if (bind(fd, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
		perror("bind");
		close(fd);
		return 1;
	}
	printf("Socket bound OK\n");

	/* Build RTM_GETLINK dump request */
	memset(&req, 0, sizeof(req));
	req.nlh.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
	req.nlh.nlmsg_type = RTM_GETLINK;
	req.nlh.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
	req.nlh.nlmsg_seq = 1;
	req.nlh.nlmsg_pid = 0;  /* kernel handles this */
	req.ifm.ifi_family = AF_UNSPEC;

	memset(&sa, 0, sizeof(sa));
	sa.nl_family = AF_NETLINK;
	sa.nl_pid = 0;  /* send to kernel */

	printf("Sending RTM_GETLINK dump request (len=%u)...\n", req.nlh.nlmsg_len);
	ret = sendto(fd, &req, req.nlh.nlmsg_len, 0,
		     (struct sockaddr *)&sa, sizeof(sa));
	if (ret < 0) {
		perror("sendto");
		close(fd);
		return 1;
	}
	printf("sendto returned %d\n", ret);

	/* Now receive the dump data */
	printf("Receiving dump data...\n");
	iov.iov_base = buf;
	iov.iov_len = sizeof(buf);
	memset(&msg, 0, sizeof(msg));
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	while (1) {
		len = recvmsg(fd, &msg, 0);
		if (len < 0) {
			if (errno == EINTR) continue;
			perror("recvmsg");
			break;
		}
		if (len == 0) {
			printf("recvmsg returned 0 (EOF)\n");
			break;
		}

		printf("recvmsg returned %zd bytes\n", len);
		nlh = (struct nlmsghdr *)buf;

		while (NLMSG_OK(nlh, len)) {
			printf("  nlmsg_type=%u nlmsg_len=%u flags=0x%x seq=%u pid=%u\n",
			       nlh->nlmsg_type, nlh->nlmsg_len,
			       nlh->nlmsg_flags, nlh->nlmsg_seq, nlh->nlmsg_pid);

			if (nlh->nlmsg_type == NLMSG_DONE) {
				printf("  -> NLMSG_DONE\n");
				goto done;
			}
			if (nlh->nlmsg_type == NLMSG_ERROR) {
				struct nlmsgerr *err = NLMSG_DATA(nlh);
				printf("  -> NLMSG_ERROR: err=%d\n", err->error);
				goto done;
			}
			if (nlh->nlmsg_type == NLMSG_NOOP)
				continue;

			nlh = NLMSG_NEXT(nlh, len);
		}

		/* More data to read? */
		if (msg.msg_flags & MSG_TRUNC) {
			printf("  (MSG_TRUNC)\n");
		}
	}

done:
	close(fd);
	printf("Done\n");
	return 0;
}
