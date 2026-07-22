/*
 * PoC: Pass socket via SCM_RIGHTS and check credentials
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <sys/wait.h>

int main(void)
{
    int sv[2], ret;
    int fd_listen, fd_client, fd_accepted;
    struct sockaddr_un addr;
    pid_t pid;
    int status;
    
    unlink("/tmp/poc.sock");
    
    /* Create a server socket, listen */
    fd_listen = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd_listen < 0) { perror("socket"); return 1; }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/poc.sock", sizeof(addr.sun_path) - 1);
    
    ret = bind(fd_listen, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("bind"); return 1; }
    
    ret = listen(fd_listen, 8);
    if (ret < 0) { perror("listen"); return 1; }
    
    printf("[+] Server listening\n");
    
    /* Fork: child connects, parent waits */
    pid = fork();
    if (pid == 0) {
        /* Child: connect then pass accepted fd back */
        fd_client = socket(AF_UNIX, SOCK_STREAM, 0);
        if (fd_client < 0) { perror("child socket"); exit(1); }
        
        ret = connect(fd_client, (struct sockaddr *)&addr, sizeof(addr));
        if (ret < 0) { perror("child connect"); exit(1); }
        
        printf("[child] Connected\n");
        
        fd_accepted = accept(fd_listen, NULL, NULL);
        if (fd_accepted < 0) { perror("child accept"); exit(1); }
        
        printf("[child] Accepted\n");
        
        /* Close listen socket */
        close(fd_listen);
        
        /* Send fd_accepted back to parent via socketpair */
        ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sv);
        if (ret < 0) { perror("child socketpair"); exit(1); }
        
        /* Send fd_accepted over sv[1] */
        struct msghdr msg;
        struct iovec iov;
        char data[] = "fd";
        char cmsg_buf[CMSG_SPACE(sizeof(int))];
        
        memset(&msg, 0, sizeof(msg));
        
        int myfd = fd_accepted;
        struct cmsghdr *cmsg = (struct cmsghdr *)cmsg_buf;
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        cmsg->cmsg_len = CMSG_LEN(sizeof(int));
        memcpy(CMSG_DATA(cmsg), &myfd, sizeof(int));
        
        iov.iov_base = data;
        iov.iov_len = 3;
        
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = cmsg;
        msg.msg_controllen = CMSG_SPACE(sizeof(int));
        
        ret = sendmsg(sv[1], &msg, 0);
        if (ret < 0) { perror("child sendmsg"); exit(1); }
        
        printf("[child] Sent fd to parent\n");
        
        close(fd_client);
        close(fd_accepted);
        close(sv[1]);
        
        printf("[child] Done\n");
        exit(0);
    }
    
    /* Parent: wait for child */
    close(fd_listen);
    
    waitpid(pid, &status, 0);
    printf("[parent] Child done\n");
    
    printf("[parent] Done\n");
    return 0;
}
