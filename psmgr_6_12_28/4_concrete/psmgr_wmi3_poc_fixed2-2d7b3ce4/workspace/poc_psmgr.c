#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>

#define AF_PSMGR 46
#define PSMGR_SOL 282
#define PSMGR_OPT_SET_ROLE 1
#define PSMGR_OPT_LOCAL_CTX 4
#define PSMGR_ROLE_MANAGED 0x01
#define PSMGR_XFRM_WINDOW 0x02
#define PSMGR_MODE_LINEAR 0x01
#define PSMGR_MSG_DATA 0x05

struct sockaddr_psmgr {
    uint16_t family;
    uint16_t pad;
    uint32_t id;
};

struct psmgr_local_ctx {
    uint8_t xfrm_type;
    uint8_t enc_mode;
    uint16_t window_sz;
    uint32_t proc_param;
};

struct psmgr_msghdr {
    uint8_t msg_type;
    uint8_t session_id_lo;
    uint16_t payload_len;
    uint32_t seq;
};

int main() {
    int sock = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (sock < 0) {
        printf("socket failed, errno = %d\n", errno);
        return 1;
    }
    printf("socket OK\n");

    struct sockaddr_psmgr addr;
    memset(&addr, 0, sizeof(addr));
    addr.family = AF_PSMGR;
    addr.pad = 0;
    addr.id = 12345;

    int ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        printf("bind failed, errno = %d\n", errno);
        close(sock);
        return 1;
    }
    printf("bind OK\n");

    uint8_t role = PSMGR_ROLE_MANAGED;
    ret = setsockopt(sock, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role));
    if (ret < 0) {
        printf("setsockopt SET_ROLE failed, errno = %d\n", errno);
        close(sock);
        return 1;
    }
    printf("setsockopt SET_ROLE OK\n");

    struct psmgr_local_ctx ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.xfrm_type = PSMGR_XFRM_WINDOW;
    ctx.enc_mode = PSMGR_MODE_LINEAR;
    ctx.window_sz = 32;
    ctx.proc_param = 0;
    ret = setsockopt(sock, PSMGR_SOL, PSMGR_OPT_LOCAL_CTX, &ctx, sizeof(ctx));
    if (ret < 0) {
        printf("setsockopt LOCAL_CTX failed, errno = %d\n", errno);
        close(sock);
        return 1;
    }
    printf("setsockopt LOCAL_CTX OK\n");

    char payload[] = "Hello PSMGR";
    uint16_t payload_len = strlen(payload);

    struct psmgr_msghdr hdr;
    memset(&hdr, 0, sizeof(hdr));
    hdr.msg_type = PSMGR_MSG_DATA;
    hdr.session_id_lo = 0;
    hdr.payload_len = payload_len;
    hdr.seq = 1;

    struct iovec iov[2];
    iov[0].iov_base = &hdr;
    iov[0].iov_len = sizeof(hdr);
    iov[1].iov_base = payload;
    iov[1].iov_len = payload_len;

    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));

    ret = sendmsg(sock, &msg, 0);
    if (ret < 0) {
        printf("sendmsg failed, errno = %d\n", errno);
        close(sock);
        return 1;
    }
    printf("sendmsg OK, sent %d bytes\n", ret);

    close(sock);
    return 0;
}

