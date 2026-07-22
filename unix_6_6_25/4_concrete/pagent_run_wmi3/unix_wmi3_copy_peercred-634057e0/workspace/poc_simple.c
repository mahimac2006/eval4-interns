#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

int main(void)
{
    int ret, fd_listen, fd_client;
    struct sockaddr_un addr;
    
    unlink("/tmp/poc.sock");
    
    fd_listen = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd_listen < 0) { perror("socket"); return 1; }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/poc.sock", sizeof(addr.sun_path) - 1);
    
    ret = bind(fd_listen, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("bind"); return 1; }
    
    ret = listen(fd_listen, 8);
    if (ret < 0) { perror("listen"); return 1; }
    
    fd_client = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd_client < 0) { perror("client socket"); return 1; }
    
    ret = connect(fd_client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("connect"); return 1; }
    
    int fd_accepted = accept(fd_listen, NULL, NULL);
    if (fd_accepted < 0) { perror("accept"); return 1; }
    
    printf("[+] Connected - copy_peercred was called\n");
    
    close(fd_accepted);
    close(fd_client);
    close(fd_listen);
    unlink("/tmp/poc.sock");
    
    return 0;
}
