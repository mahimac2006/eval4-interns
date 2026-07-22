#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>

int main(void)
{
    int sv[2];
    int fd;
    char buf[8];
    char cbuf[CMSG_SPACE(sizeof(int))];
    struct msghdr msg = {0};
    struct iovec iov = {buf, sizeof(buf)};

    socketpair(AF_UNIX, SOCK_DGRAM, 0, sv);
    fd = open("/etc/passwd", O_RDONLY);

    struct cmsghdr *cmsg = (struct cmsghdr *)cbuf;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int));
    *(int *)CMSG_DATA(cmsg) = fd;

    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = cbuf;
    msg.msg_controllen = sizeof(cbuf);
    sendmsg(sv[0], &msg, 0);

    msg.msg_control = cbuf;
    msg.msg_controllen = sizeof(cbuf);
    recvmsg(sv[1], &msg, MSG_PEEK);

    recvmsg(sv[1], &msg, 0);
    close(fd);
    close(sv[0]);
    close(sv[1]);
    return 0;
}
