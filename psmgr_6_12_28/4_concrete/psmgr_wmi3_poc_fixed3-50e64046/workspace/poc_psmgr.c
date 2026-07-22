#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/types.h>

struct sockaddr_psmgr { uint16_t family; uint16_t pad; uint32_t id; };
struct psmgr_local_ctx { uint8_t xfrm_type; uint8_t enc_mode; uint16_t window_sz; uint32_t proc_param; };
struct psmgr_msghdr { uint8_t msg_type; uint8_t session_id_lo; uint16_t payload_len; uint32_t seq; };

#define AF_PSMGR 46
#define SOCK_SEQPACKET 5
#define PSMGR_SOL 282
#define PSMGR_OPT_SET_ROLE 1
#define PSMGR_OPT_LOCAL_CTX 4
#define PSMGR_ROLE_MANAGED 0x01
#define PSMGR_XFRM_WINDOW 0x02
#define PSMGR_MODE_LINEAR 0x01
#define PSMGR_MSG_DATA 0x05

int main(void) {
    int fd = socket(AF_PSMGR, SOCK_SEQPACKET, 0);
    if (fd < 0) {
        printf("socket failed: %d\n", errno);
        exit(1);
    }
    
    struct sockaddr_psmgr addr = {AF_PSMGR, 0, 1};
    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("bind failed: %d\n", errno);
        close(fd);
        exit(1);
    }
    
    uint8_t role = PSMGR_ROLE_MANAGED;
    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_SET_ROLE, &role, sizeof(role)) < 0) {
        printf("setsockopt role failed: %d\n", errno);
        close(fd);
        exit(1);
    }
    
    struct psmgr_local_ctx ctx = {PSMGR_XFRM_WINDOW, PSMGR_MODE_LINEAR, 0, 127};
    if (setsockopt(fd, PSMGR_SOL, PSMGR_OPT_LOCAL_CTX, &ctx, sizeof(ctx)) < 0) {
        printf("setsockopt ctx failed: %d\n", errno);
        close(fd);
        exit(1);
    }
    
    uint8_t buf[16] = {PSMGR_MSG_DATA, 1, 16, 0, 1, 0, 0, 0, 0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41};
    if (write(fd, buf, 16) < 0) {
        printf("write failed: %d\n", errno);
        close(fd);
        exit(1);
    }
    
    printf("done\n");
    close(fd);
    return 0;
}

