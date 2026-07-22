#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

int main(void)
{
    int ret, fd;
    
    /* Create socket but don't bind it, then try to listen */
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) { perror("socket"); return 1; }
    
    /* Listen without bind - should fail with EINVAL */
    ret = listen(fd, 8);
    printf("[+] listen without bind: ret=%d errno=%d\n", ret, errno);
    
    /* Now bind and listen */
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/poc_unbound.sock", sizeof(addr.sun_path) - 1);
    unlink("/tmp/poc_unbound.sock");
    
    ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("bind"); return 1; }
    
    ret = listen(fd, 8);
    if (ret < 0) { perror("listen"); return 1; }
    
    /* Connect */
    int cfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (cfd < 0) { perror("client socket"); return 1; }
    
    ret = connect(cfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("connect"); return 1; }
    
    printf("[+] Connected - copy_peercred called\n");
    
    close(cfd);
    close(fd);
    unlink("/tmp/poc_unbound.sock");
    
    return 0;
}
