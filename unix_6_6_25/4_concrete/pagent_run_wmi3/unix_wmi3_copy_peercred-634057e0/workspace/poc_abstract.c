#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stddef.h>

int main(void)
{
    int ret, fd_listen, fd_client;
    struct sockaddr_un addr;
    
    /* Use abstract socket */
    fd_listen = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd_listen < 0) { perror("socket"); return 1; }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    addr.sun_path[0] = '\0';
    memcpy(addr.sun_path + 1, "poc_abstract", 13);
    
    socklen_t addrlen = offsetof(struct sockaddr_un, sun_path) + 1 + 13;
    
    ret = bind(fd_listen, (struct sockaddr *)&addr, addrlen);
    if (ret < 0) { perror("bind"); return 1; }
    
    ret = listen(fd_listen, 8);
    if (ret < 0) { perror("listen"); return 1; }
    
    fd_client = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd_client < 0) { perror("client socket"); return 1; }
    
    ret = connect(fd_client, (struct sockaddr *)&addr, addrlen);
    if (ret < 0) { perror("connect"); return 1; }
    
    printf("[+] Connected - copy_peercred was called\n");
    
    close(fd_client);
    close(fd_listen);
    
    return 0;
}
