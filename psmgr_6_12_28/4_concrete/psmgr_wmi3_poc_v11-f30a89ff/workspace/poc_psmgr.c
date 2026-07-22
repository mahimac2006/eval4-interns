#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>

#define AF_PSMGR 46
#define PSMGR_SOL 282
#define PSMGR_OPT_SET_ROLE 1
#define PSMGR_OPT_LOCAL_CTX 4
#define PSMGR_ROLE_MANAGED 0x01
#define PSMGR_XFRM_WINDOW 0x02
#define PSMGR_MODE_LINEAR 0x01
#define PSMGR_MSG_DATA 0x05

struct sockaddr_psmgr { uint16_t family; uint16_t pad; uint32_t id; };
struct psmgr_local_ctx { uint8_t xfrm_type; uint8_t enc_mode; uint16_t window_sz; uint32_t proc_param; };
struct psmgr_msghdr { uint8_t msg_type; uint8_t session_id_lo; uint16_t payload_len; uint32_t seq; };

int main(void) {
    int fd;
    struct sockaddr_psmgr addr;
    struct psmgr_local_ctx ctx;
    struct psmgr_msghdr hdr;
    uint8_t payload[16];
    uint8_t buf[sizeof(hdr) + sizeof(payload)];
    uint8_t role = PSMGR_ROLE_MANAGED;
    ssize_t ret;

    printf("step 1: socket\n"); fflush(stdout);
    fd = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd < 0) { printf("socket failed: %d %s\n", errno, strerror(errno)); return 1; }
    printf("socket ok fd=%d\n", fd); fflush(stdout);

    printf("step 2: bind\n"); fflush(stdout);
    memset(&addr, 0, sizeof(addr));
    addr.family = AF_PSMGR;
    addr.id = 42;  /* use non-conflicting session id */
    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("bind failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    printf("bind ok\n"); fflush(stdout);

    printf("step 3: set role MANAGED\n"); fflush(stdout);
    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role)) < 0) {
        printf("set_role failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    printf("set_role ok\n"); fflush(stdout);

    printf("step 4: set LOCAL_CTX\n"); fflush(stdout);
    memset(&ctx, 0, sizeof(ctx));
    ctx.xfrm_type = PSMGR_XFRM_WINDOW;
    ctx.enc_mode = PSMGR_MODE_LINEAR;
    ctx.window_sz = 0;
    ctx.proc_param = 127;
    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_LOCAL_CTX, &ctx, sizeof(ctx)) < 0) {
        printf("local_ctx failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    printf("local_ctx ok\n"); fflush(stdout);

    printf("step 5: send DATA msg\n"); fflush(stdout);
    memset(&hdr, 0, sizeof(hdr));
    hdr.msg_type = PSMGR_MSG_DATA;
    hdr.session_id_lo = 42;
    hdr.payload_len = sizeof(payload);
    hdr.seq = 1;
    memset(payload, 0x41, sizeof(payload));
    memcpy(buf, &hdr, sizeof(hdr));
    memcpy(buf + sizeof(hdr), payload, sizeof(payload));

    ret = write(fd, buf, sizeof(buf));
    if (ret < 0) {
        printf("write failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    printf("write ok ret=%zd\n", ret); fflush(stdout);
    printf("done\n"); fflush(stdout);
    close(fd);
    return 0;
}

