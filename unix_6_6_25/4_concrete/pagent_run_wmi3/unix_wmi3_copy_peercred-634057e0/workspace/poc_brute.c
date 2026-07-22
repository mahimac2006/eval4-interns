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
    int ret, i;
    int fds[2];
    
    /* Try many socketpairs - each creates two sockets with peer creds set */
    printf("[*] Creating many socketpairs...\n");
    for (i = 0; i < 100; i++) {
        ret = socketpair(AF_UNIX, SOCK_STREAM, 0, fds);
        if (ret < 0) { perror("socketpair"); return 1; }
        
        /* Read SO_PEERCRED on both sides */
        unsigned int cred[3];
        socklen_t len = sizeof(cred);
        ret = getsockopt(fds[0], SOL_SOCKET, SO_PEERCRED, cred, &len);
        if (ret < 0) { perror("getsockopt0"); }
        
        len = sizeof(cred);
        ret = getsockopt(fds[1], SOL_SOCKET, SO_PEERCRED, cred, &len);
        if (ret < 0) { perror("getsockopt1"); }
        
        close(fds[0]);
        close(fds[1]);
    }
    printf("[+] Done creating socketpairs\n");
    
    /* Now try fork model where parent listens, child connects */
    printf("[*] Testing fork model with many iterations...\n");
    for (i = 0; i < 10; i++) {
        int fd;
        struct sockaddr_un addr;
        pid_t pid;
        int status;
        
        unlink("/tmp/poc_brute.sock");
        
        fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (fd < 0) { perror("socket"); return 1; }
        
        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, "/tmp/poc_brute.sock", sizeof(addr.sun_path) - 1);
        
        ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
        if (ret < 0) { perror("bind"); return 1; }
        
        ret = listen(fd, 8);
        if (ret < 0) { perror("listen"); return 1; }
        
        pid = fork();
        if (pid == 0) {
            /* Child: increase our pid namespace depth */
            int cfd = socket(AF_UNIX, SOCK_STREAM, 0);
            if (cfd < 0) exit(1);
            
            ret = connect(cfd, (struct sockaddr *)&addr, sizeof(addr));
            if (ret < 0) exit(1);
            
            close(cfd);
            exit(0);
        }
        
        int afd = accept(fd, NULL, NULL);
        if (afd < 0) { perror("accept"); return 1; }
        close(afd);
        
        waitpid(pid, &status, 0);
        close(fd);
        unlink("/tmp/poc_brute.sock");
    }
    printf("[+] Done with fork model\n");
    
    printf("[*] Done\n");
    return 0;
}
