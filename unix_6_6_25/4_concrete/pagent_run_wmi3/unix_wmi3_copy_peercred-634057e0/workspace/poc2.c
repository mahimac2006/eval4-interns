#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

int main(void)
{
    int sv[2], ret;
    
    /* Create socketpair, which calls init_peercred on both sides */
    ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sv);
    if (ret < 0) { perror("socketpair"); return 1; }
    printf("[+] socketpair created\n");
    
    /* Do many getsockopt SO_PEERCRED to exercise the credential path */
    int i;
    for (i = 0; i < 100; i++) {
        struct {
            unsigned int pid;
            unsigned int uid;
            unsigned int gid;
        } cred;
        socklen_t len = sizeof(cred);
        ret = getsockopt(sv[0], SOL_SOCKET, SO_PEERCRED, &cred, &len);
        if (ret < 0) { perror("getsockopt"); break; }
    }
    printf("[+] getsockopt done\n");
    
    close(sv[0]);
    close(sv[1]);
    return 0;
}
