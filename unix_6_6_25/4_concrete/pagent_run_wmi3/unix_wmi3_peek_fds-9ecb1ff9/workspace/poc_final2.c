/*
 * PoC for WMI-3: unix_peek_fds
 * Simple, clean PoC that triggers unix_peek_fds
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
    int sv[2];
    int fd;
    struct msghdr msg;
    struct iovec iov;
    char buf[8];
    struct {
        struct cmsghdr h;
        int fd;
    } cmsg;
    int ret;

    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) < 0)
        return 1;

    fd = open("/etc/passwd", O_RDONLY);
    if (fd < 0)
        return 1;

    /* Send */
    memset(&msg, 0, sizeof(msg));
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = &cmsg;
    msg.msg_controllen = sizeof(cmsg);
    cmsg.h.cmsg_level = SOL_SOCKET;
    cmsg.h.cmsg_type = SCM_RIGHTS;
    cmsg.h.cmsg_len = CMSG_LEN(sizeof(int));
    cmsg.fd = fd;

    ret = sendmsg(sv[0], &msg, 0);
    if (ret < 0)
        return 1;

    /* Peek - triggers unix_peek_fds */
    memset(&msg, 0, sizeof(msg));
    memset(&cmsg, 0, sizeof(cmsg));
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = &cmsg;
    msg.msg_controllen = sizeof(cmsg);

    ret = recvmsg(sv[1], &msg, MSG_PEEK);
    if (ret < 0)
        return 1;

    /* Consume */
    memset(&msg, 0, sizeof(msg));
    memset(&cmsg, 0, sizeof(cmsg));
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = &cmsg;
    msg.msg_controllen = sizeof(cmsg);

    ret = recvmsg(sv[1], &msg, 0);
    if (ret < 0)
        return 1;

    close(fd);
    close(sv[0]);
    close(sv[1]);
    return 0;
}
