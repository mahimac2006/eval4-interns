#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/uio.h>
#include <errno.h>
#include <sys/wait.h>

static void die(const char *msg) {
    perror(msg);
    exit(1);
}

int main(void) {
    int sv[2];
    struct sockaddr_un addr1, addr2;
    int fd1, fd2;
    socklen_t len;
    pid_t pid;

    /* --- Test 1: af_unix.c:715/716 connect pair to copy_peercred --- */
    printf("[Test 1] Connecting two SOCK_STREAM sockets via explicit connect...\n");
    fflush(stdout);

    fd1 = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd1 < 0) die("socket fd1");
    fd2 = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd2 < 0) die("socket fd2");

    memset(&addr1, 0, sizeof(addr1));
    addr1.sun_family = AF_UNIX;
    snprintf(addr1.sun_path + 1, sizeof(addr1.sun_path) - 2, "test-peercred-1");
    addr1.sun_path[0] = '\0';

    if (bind(fd1, (struct sockaddr*)&addr1, sizeof(addr1)) < 0) die("bind fd1");
    if (listen(fd1, 1) < 0) die("listen fd1");

    memset(&addr2, 0, sizeof(addr2));
    addr2.sun_family = AF_UNIX;
    snprintf(addr2.sun_path + 1, sizeof(addr2.sun_path) - 2, "test-peercred-2");
    addr2.sun_path[0] = '\0';

    if (bind(fd2, (struct sockaddr*)&addr2, sizeof(addr2)) < 0) die("bind fd2");
    if (listen(fd2, 1) < 0) die("listen fd2");

    /* connect fd1 to fd2's address */
    if (connect(fd1, (struct sockaddr*)&addr2, sizeof(addr2)) < 0) {
        if (errno == EINPROGRESS) {
            struct timeval tv = { .tv_sec = 2, .tv_usec = 0 };
            fd_set wset;
            FD_ZERO(&wset);
            FD_SET(fd1, &wset);
            if (select(fd1+1, NULL, &wset, NULL, &tv) <= 0)
                die("select connect");
        } else {
            die("connect fd1->fd2");
        }
    }
    printf("[Test 1] connect succeeded (triggers copy_peercred at line 715/716)\n");
    fflush(stdout);

    /* accept from fd2 to complete pairing */
    int accept_fd = accept(fd2, NULL, NULL);
    if (accept_fd < 0) die("accept");
    close(accept_fd);

    /* clean up test1 sockets */
    close(fd1);
    close(fd2);

    /* --- Test 2 & 3: SCM_RIGHTS sendmsg + recvmsg with MSG_PEEK, then without --- */
    printf("[Test 2] sendmsg with SCM_RIGHTS and recvmsg with MSG_PEEK...\n");
    fflush(stdout);

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) < 0) die("socketpair");

    /* prepare a pipe fd to send */
    int pipefd[2];
    if (pipe(pipefd) < 0) die("pipe");

    struct msghdr msg = {0};
    struct iovec iov;
    char buf[] = "data";
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    /* ancillary data for SCM_RIGHTS */
    char cmsg_buf[CMSG_SPACE(sizeof(int))];
    msg.msg_control = cmsg_buf;
    msg.msg_controllen = sizeof(cmsg_buf);

    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int));
    memcpy(CMSG_DATA(cmsg), &pipefd[0], sizeof(int));

    if (sendmsg(sv[0], &msg, 0) < 0) die("sendmsg scm_rights");
    printf("[Test 2] sent SCM_RIGHTS fd\n");
    fflush(stdout);

    /* recvmsg with MSG_PEEK to trigger unix_peek_fds (af_unix.c:1777) */
    struct msghdr peek_msg = {0};
    char peek_buf[64];
    struct iovec peek_iov;
    peek_iov.iov_base = peek_buf;
    peek_iov.iov_len = sizeof(peek_buf);
    peek_msg.msg_iov = &peek_iov;
    peek_msg.msg_iovlen = 1;

    char peek_cmsg_buf[CMSG_SPACE(sizeof(int))];
    peek_msg.msg_control = peek_cmsg_buf;
    peek_msg.msg_controllen = sizeof(peek_cmsg_buf);

    ssize_t ret = recvmsg(sv[1], &peek_msg, MSG_PEEK);
    if (ret < 0) die("recvmsg MSG_PEEK");
    printf("[Test 2] recvmsg with MSG_PEEK returned %zd (triggers unix_peek_fds)\n", ret);
    fflush(stdout);

    /* --- Test 3: recvmsg without MSG_PEEK to trigger unix_detach_fds (scm.c:131) --- */
    printf("[Test 3] recvmsg without MSG_PEEK to trigger unix_detach_fds...\n");
    fflush(stdout);

    struct msghdr detach_msg = {0};
    char detach_buf[64];
    struct iovec detach_iov;
    detach_iov.iov_base = detach_buf;
    detach_iov.iov_len = sizeof(detach_buf);
    detach_msg.msg_iov = &detach_iov;
    detach_msg.msg_iovlen = 1;

    char detach_cmsg_buf[CMSG_SPACE(sizeof(int))];
    detach_msg.msg_control = detach_cmsg_buf;
    detach_msg.msg_controllen = sizeof(detach_cmsg_buf);

    ret = recvmsg(sv[1], &detach_msg, 0);
    if (ret < 0) die("recvmsg without MSG_PEEK");
    printf("[Test 3] recvmsg without MSG_PEEK returned %zd (triggers unix_detach_fds)\n", ret);
    fflush(stdout);

    /* verify we got the fd */
    struct cmsghdr *cmsg_rcv = CMSG_FIRSTHDR(&detach_msg);
    if (cmsg_rcv && cmsg_rcv->cmsg_type == SCM_RIGHTS) {
        int received_fd;
        memcpy(&received_fd, CMSG_DATA(cmsg_rcv), sizeof(received_fd));
        printf("[Test 3] Received fd = %d\n", received_fd);
        close(received_fd);
    }

    /* cleanup */
    close(sv[0]);
    close(sv[1]);
    close(pipefd[0]);
    close(pipefd[1]);

    printf("All tests passed, exiting 0.\n");
    return 0;
}
