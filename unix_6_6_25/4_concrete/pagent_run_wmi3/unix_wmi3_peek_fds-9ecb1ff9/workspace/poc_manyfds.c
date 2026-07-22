/*
 * Send 253 file descriptors via SCM_RIGHTS (max allowed)
 * Then peek to trigger unix_peek_fds with large fp list
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

#define MAX_FDS 253

int main(void)
{
    int sv[2];
    int fds[MAX_FDS];
    struct msghdr msg = {0};
    struct iovec iov;
    char buf[64];
    char cmsg_buf[CMSG_SPACE(MAX_FDS * sizeof(int))];
    struct cmsghdr *cmsg;
    int ret;
    int i;

    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) < 0) {
        perror("socketpair");
        return 1;
    }

    for (i = 0; i < MAX_FDS; i++) {
        fds[i] = open("/etc/passwd", O_RDONLY);
        if (fds[i] < 0) {
            perror("open");
            return 1;
        }
    }

    memset(buf, 0x41, sizeof(buf));
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = cmsg_buf;
    msg.msg_controllen = sizeof(cmsg_buf);

    cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(MAX_FDS * sizeof(int));
    for (i = 0; i < MAX_FDS; i++)
        ((int *)CMSG_DATA(cmsg))[i] = fds[i];

    ret = sendmsg(sv[0], &msg, 0);
    if (ret < 0) {
        perror("sendmsg");
        return 1;
    }
    printf("Sent %d fds\n", MAX_FDS);

    /* Peek */
    memset(&msg, 0, sizeof(msg));
    memset(cmsg_buf, 0, sizeof(cmsg_buf));
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = cmsg_buf;
    msg.msg_controllen = sizeof(cmsg_buf);

    ret = recvmsg(sv[1], &msg, MSG_PEEK);
    if (ret < 0) {
        perror("recvmsg");
        return 1;
    }
    printf("Peek succeeded, got cmsg_len=%zu\n", 
           msg.msg_controllen);

    /* Consume */
    memset(&msg, 0, sizeof(msg));
    memset(cmsg_buf, 0, sizeof(cmsg_buf));
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = cmsg_buf;
    msg.msg_controllen = sizeof(cmsg_buf);

    ret = recvmsg(sv[1], &msg, 0);
    if (ret < 0) {
        perror("recvmsg");
        return 1;
    }
    printf("Consumed\n");

    for (i = 0; i < MAX_FDS; i++)
        close(fds[i]);
    close(sv[0]);
    close(sv[1]);
    return 0;
}
