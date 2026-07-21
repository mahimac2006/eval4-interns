#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_process_data — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define DATA_SZ 128
#define TOTAL_SZ 144
#define SIZEOF_U32 4
#define XFRM_SCATTER 0
#define XFRM_COMMIT 1
#define XFRM_REFLECT 2
#define XFRM_WINDOW 3
#define ROLE_MANAGED 0
#define ROLE_SECONDARY 1
int main(void){
  unsigned int out_offset; klee_make_symbolic(&out_offset, sizeof(out_offset), "out_offset");
  unsigned int payload_len; klee_make_symbolic(&payload_len, sizeof(payload_len), "payload_len");
  unsigned int xfrm_type; klee_make_symbolic(&xfrm_type, sizeof(xfrm_type), "xfrm_type");
  unsigned int role; klee_make_symbolic(&role, sizeof(role), "role");
  unsigned int token; klee_make_symbolic(&token, sizeof(token), "token");
  unsigned int window_sz; klee_make_symbolic(&window_sz, sizeof(window_sz), "window_sz");
  unsigned int wl0; klee_make_symbolic(&wl0, sizeof(wl0), "wl0");
  unsigned int wl1; klee_make_symbolic(&wl1, sizeof(wl1), "wl1");
  unsigned int write_limit; klee_make_symbolic(&write_limit, sizeof(write_limit), "write_limit");
  unsigned int copy_len; klee_make_symbolic(&copy_len, sizeof(copy_len), "copy_len");
  klee_assume((xfrm_type == XFRM_WINDOW) || (out_offset < DATA_SZ));
  klee_assume((role == ROLE_MANAGED) || (out_offset < TOTAL_SZ));
  klee_assume(wl0 == (token != 0 ? TOTAL_SZ : DATA_SZ + SIZEOF_U32));
  klee_assume(wl1 == ((out_offset < DATA_SZ && wl0 > DATA_SZ) ? DATA_SZ : wl0));
  klee_assume(write_limit == ((role == ROLE_SECONDARY && window_sz > 0 && (out_offset + window_sz) < wl1) ? (out_offset + window_sz) : wl1));
  klee_assume(copy_len == ((payload_len < (write_limit - (out_offset < write_limit ? out_offset : write_limit))) ? payload_len : (write_limit - (out_offset < write_limit ? out_offset : write_limit))));
  klee_assume(copy_len > 0);
  assert(out_offset + copy_len <= TOTAL_SZ);
  return 0;}
