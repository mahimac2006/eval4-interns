#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdint.h>

struct sockaddr_psmgr { uint16_t spsmgr_family; uint32_t spsmgr_id; } __attribute__((packed));
struct psmgr_local_ctx { uint8_t xfrm_type; uint8_t enc_mode; uint16_t window_sz; uint32_t proc_param; };
struct psmgr_msghdr { uint8_t msg_type; uint8_t session_id_lo; uint16_t payload_len; uint32_t seq; };

#define AF_PSMGR 46
#define PSMGR_SOL 282
#define PSMGR_OPT_SET_ROLE 1
#define PSMGR_OPT_LOCAL_CTX 4
#define PSMGR_ROLE_MANAGED 0x01
#define PSMGR_XFRM_WINDOW 0x02
#define PSMGR_MODE_LINEAR 0x01
#define PSMGR_MSG_DATA 0x05

int main() {
    int fd;

    // Step 1: socket
    fd = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd < 0) {
        printf("socket error: errno=%d (%s)\n", errno, strerror(errno));
        return 1;
    }
    printf("socket success (fd=%d)\n", fd);

    // Step 2: bind
    struct sockaddr_psmgr addr = {.spsmgr_family=AF_PSMGR, .spsmgr_id=1};
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        printf("bind error: errno=%d (%s)\n", errno, strerror(errno));
        close(fd);
        return 1;
    }
    printf("bind success\n");

    // Step 3: setsockopt SET_ROLE
    uint8_t role = PSMGR_ROLE_MANAGED;
    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role)) < 0) {
        printf("setsockopt SET_ROLE error: errno=%d (%s)\n", errno, strerror(errno));
        close(fd);
        return 1;
    }
    printf("setsockopt SET_ROLE success\n");

    // Step 4: setsockopt LOCAL_CTX
    struct psmgr_local_ctx ctx = {.xfrm_type=PSMGR_XFRM_WINDOW, .enc_mode=PSMGR_MODE_LINEAR, .window_sz=0, .proc_param=127};
    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_LOCAL_CTX, &ctx, sizeof(ctx)) < 0) {
        printf("setsockopt LOCAL_CTX error: errno=%d (%s)\n", errno, strerror(errno));
        close(fd);
        return 1;
    }
    printf("setsockopt LOCAL_CTX success\n");

    // Step 5-6: build and send message
    struct psmgr_msghdr hdr = {.msg_type=PSMGR_MSG_DATA, .session_id_lo=1, .payload_len=16, .seq=1};
    char payload[16];
    memset(payload, 0x41, 16);

    char buffer[sizeof(struct psmgr_msghdr) + 16];
    memcpy(buffer, &hdr, sizeof(struct psmgr_msghdr));
    memcpy(buffer + sizeof(struct psmgr_msghdr), payload, 16);

    if (write(fd, buffer, sizeof(buffer)) < 0) {
        printf("write error: errno=%d (%s)\n", errno, strerror(errno));
        close(fd);
        return 1;
    }
    printf("write success (sent %zu bytes)\n", sizeof(buffer));

    close(fd);
    return 0;
}

