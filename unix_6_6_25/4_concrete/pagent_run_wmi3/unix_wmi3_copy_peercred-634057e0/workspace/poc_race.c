#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <pthread.h>

#define SOCK_PATH "/tmp/poc_race.sock"
#define NUM_THREADS 16

int server_fd;
int count;

void *connect_thread(void *arg)
{
    int fd, ret;
    struct sockaddr_un addr;
    int id = (long)arg;
    
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) return NULL;
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    
    ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret >= 0) {
        __sync_fetch_and_add(&count, 1);
        /* Hold the socket briefly */
        usleep(1000);
        close(fd);
    }
    return NULL;
}

int main(void)
{
    int ret, i;
    struct sockaddr_un addr;
    pthread_t threads[NUM_THREADS];
    
    unlink(SOCK_PATH);
    
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); return 1; }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    
    ret = bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("bind"); return 1; }
    
    ret = listen(server_fd, NUM_THREADS + 8);
    if (ret < 0) { perror("listen"); return 1; }
    
    printf("[+] Server listening\n");
    
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, connect_thread, (void *)(long)i);
    }
    
    /* Accept connections */
    for (i = 0; i < NUM_THREADS; i++) {
        struct timeval tv = {0, 100000};
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(server_fd, &rfds);
        if (select(server_fd+1, &rfds, NULL, NULL, &tv) > 0) {
            int afd = accept(server_fd, NULL, NULL);
            if (afd >= 0) {
                close(afd);
            }
        }
    }
    
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("[+] %d connections handled\n", count);
    
    close(server_fd);
    unlink(SOCK_PATH);
    
    return 0;
}
