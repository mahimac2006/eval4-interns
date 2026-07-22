/*
 * Minimal test: verify the QEMU guest runs and we can get dmesg output.
 * Just create a netlink socket and print success.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

int main(void)
{
	int fd;

	printf("Hello from poc! Starting...\n");

	/* Open a NETLINK_ROUTE socket */
	fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	if (fd < 0) {
		perror("socket");
		printf("FAIL: socket() returned %d\n", errno);
		return 1;
	}
	printf("OK: socket opened, fd=%d\n", fd);

	/* Try a simple getsockname */
	struct sockaddr_nl sa;
	socklen_t salen = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	if (getsockname(fd, (struct sockaddr *)&sa, &salen) < 0) {
		perror("getsockname");
		printf("FAIL: getsockname\n");
		close(fd);
		return 1;
	}
	printf("OK: getsockname, nl_pid=%u\n", sa.nl_pid);

	close(fd);
	printf("DONE\n");
	return 0;
}
