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
    struct sockaddr_un addr;
    
    unlink("/tmp/poc3.sock");
    
    /* Create socketpair */
    ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sv);
    if (ret < 0) { perror("socketpair"); return 1; }
    printf("[+] socketpair: fds %d, %d\n", sv[0], sv[1]);
    
    /* Create a server */
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) { perror("socket"); return 1; }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/poc3.sock", sizeof(addr.sun_path)-1);
    
    ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("bind"); return 1; }
    
    ret = listen(fd, 8);
    if (ret < 0) { perror("listen"); return 1; }
    
    printf("[+] Server listening\n");
    
    /* Connect */
    int cfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (cfd < 0) { perror("client socket"); return 1; }
    
    ret = connect(cfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("connect"); return 1; }
    
    printf("[+] Connected\n");
    
    /* Accept */
    int afd = accept(fd, NULL, NULL);
    if (afd < 0) { perror("accept"); return 1; }
    printf("[+] Accepted\n");
    
    /* Now: try to call listen() again on the parent socket */
    ret = listen(fd, 8);
    printf("[+] listen again: %d\n", ret);
    
    /* Connect again (should work since server listened again) */
    int cfd2 = socket(AF_UNIX, SOCK_STREAM, 0);
    if (cfd2 < 0) { perror("client2 socket"); return 1; }
    
    ret = connect(cfd2, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("connect2"); }
    else {
        printf("[+] Connected again\n");
        int afd2 = accept(fd, NULL, NULL);
        if (afd2 >= 0) {
            printf("[+] Accepted again\n");
            close(afd2);
        }
        close(cfd2);
    }
    
    close(afd);
    close(cfd);
    close(fd);
    close(sv[0]);
    close(sv[1]);
    unlink("/tmp/poc3.sock");
    
    printf("[+] Done\n");
    return 0;
}
