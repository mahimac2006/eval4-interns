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
    int fd, ret;
    struct sockaddr_un addr;
    pid_t pid;
    int status;
    
    unlink("/tmp/poc_fork.sock");
    
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) { perror("socket"); return 1; }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/poc_fork.sock", sizeof(addr.sun_path) - 1);
    
    ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("bind"); return 1; }
    
    ret = listen(fd, 8);
    if (ret < 0) { perror("listen"); return 1; }
    
    printf("[+] Server listening (pid=%d)\n", getpid());
    
    pid = fork();
    if (pid == 0) {
        /* Child: connect to the server */
        int cfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (cfd < 0) { perror("child socket"); exit(1); }
        
        ret = connect(cfd, (struct sockaddr *)&addr, sizeof(addr));
        if (ret < 0) { perror("child connect"); exit(1); }
        printf("[child] Connected\n");
        
        /* Check peer credentials */
        struct {
            unsigned int pid;
            unsigned int uid;
            unsigned int gid;
        } cred;
        socklen_t len = sizeof(cred);
        ret = getsockopt(cfd, SOL_SOCKET, SO_PEERCRED, &cred, &len);
        if (ret < 0) { perror("child getsockopt"); }
        else { printf("[child] Peer: pid=%u uid=%u gid=%u\n", cred.pid, cred.uid, cred.gid); }
        
        close(cfd);
        exit(0);
    }
    
    /* Parent: accept connection */
    int afd = accept(fd, NULL, NULL);
    if (afd < 0) { perror("parent accept"); return 1; }
    printf("[parent] Accepted\n");
    
    waitpid(pid, &status, 0);
    
    close(afd);
    close(fd);
    unlink("/tmp/poc_fork.sock");
    
    printf("[+] Done\n");
    return 0;
}
