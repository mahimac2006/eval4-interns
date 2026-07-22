#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int sv[2];
    int fd, dup_fd;
    char buf[8];
    char cbuf[CMSG_SPACE(sizeof(int))];
    struct msghdr msg = {0};
    struct iovec iov = {buf, sizeof(buf)};

    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) < 0) {
        perror("socketpair");
        return 1;
    }
    
    fd = open("/etc/passwd", O_RDONLY);
    if (fd < 0) return 1;

    /* Duplicate to have two references */
    dup_fd = dup(fd);
    if (dup_fd < 0) return 1;
    close(fd); /* Close the original */

    /* Send with dup'd fd */
    struct cmsghdr *cmsg = (struct cmsghdr *)cbuf;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int));
    *(int *)CMSG_DATA(cmsg) = dup_fd;

    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = cbuf;
    msg.msg_controllen = sizeof(cbuf);
    if (sendmsg(sv[0], &msg, 0) < 0) {
        perror("sendmsg");
        return 1;
    }
    printf("Sent fd %d\n", dup_fd);
    close(dup_fd); /* Close sender's copy */

    /* Now peek - triggers unix_peek_fds */
    msg.msg_control = cbuf;
    msg.msg_controllen = sizeof(cbuf);
    if (recvmsg(sv[1], &msg, MSG_PEEK) < 0) {
        perror("recvmsg peek");
        return 1;
    }
    printf("Peek succeeded\n");

    /* Consume */
    msg.msg_control = cbuf;
    msg.msg_controllen = sizeof(cbuf);
    if (recvmsg(sv[1], &msg, 0) < 0) {
        perror("recvmsg");
        return 1;
    }
    printf("Consumed\n");

    close(sv[0]);
    close(sv[1]);
    printf("Done\n");
    return 0;
}
