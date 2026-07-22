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

int main(int argc, char **argv)
{
    int sv[2];
    int fd_to_pass;
    struct msghdr msg = {0};
    struct iovec iov;
    char buf[64];
    char cmsg_buf[CMSG_SPACE(sizeof(int))];
    struct cmsghdr *cmsg;

    /* Create a socket pair */
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) < 0) {
        perror("socketpair");
        return 1;
    }

    /* Open a file to pass */
    fd_to_pass = open("/etc/passwd", O_RDONLY);
    if (fd_to_pass < 0) {
        perror("open");
        return 1;
    }

    /* Prepare message to send */
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);
    memset(buf, 0x41, sizeof(buf));

    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = cmsg_buf;
    msg.msg_controllen = sizeof(cmsg_buf);

    cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int));
    memcpy(CMSG_DATA(cmsg), &fd_to_pass, sizeof(int));

    /* Send message */
    if (sendmsg(sv[0], &msg, 0) < 0) {
        perror("sendmsg");
        return 1;
    }

    printf("Sent SCM_RIGHTS with fd=%d\n", fd_to_pass);

    /* Receive with MSG_PEEK first */
    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);
    memset(buf, 0, sizeof(buf));

    char recv_cmsg_buf[CMSG_SPACE(sizeof(int))];
    msg.msg_control = recv_cmsg_buf;
    msg.msg_controllen = sizeof(recv_cmsg_buf);

    int ret = recvmsg(sv[1], &msg, MSG_PEEK);
    printf("PEEK recvmsg returned %d (errno=%d)\n", ret, errno);
    if (ret < 0) {
        perror("PEEK recvmsg");
    }

    /* Now receive without PEEK */
    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);

    msg.msg_control = recv_cmsg_buf;
    msg.msg_controllen = sizeof(recv_cmsg_buf);

    ret = recvmsg(sv[1], &msg, 0);
    printf("RECV recvmsg returned %d (errno=%d)\n", ret, errno);
    if (ret < 0) {
        perror("RECV recvmsg");
    }

    close(sv[0]);
    close(sv[1]);
    close(fd_to_pass);

    printf("Done.\n");
    return 0;
}
