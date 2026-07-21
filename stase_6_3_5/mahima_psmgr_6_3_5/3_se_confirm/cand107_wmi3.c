#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-3 psmgr_process_data — SE oracle from SA rule WMI-3b_AttackerContent_OffsetControlledWrite */
#define DATA_SZ 128
#define TOTAL_SZ 144
#define U32_SZ 4
int main(void){
  unsigned int out_offset; klee_make_symbolic(&out_offset, sizeof(out_offset), "out_offset");
  unsigned int payload_len; klee_make_symbolic(&payload_len, sizeof(payload_len), "payload_len");
  unsigned int token; klee_make_symbolic(&token, sizeof(token), "token");
  unsigned int role_managed; klee_make_symbolic(&role_managed, sizeof(role_managed), "role_managed");
  unsigned int role_secondary; klee_make_symbolic(&role_secondary, sizeof(role_secondary), "role_secondary");
  unsigned int window_sz; klee_make_symbolic(&window_sz, sizeof(window_sz), "window_sz");
  unsigned int wl1; klee_make_symbolic(&wl1, sizeof(wl1), "wl1");
  unsigned int wl2; klee_make_symbolic(&wl2, sizeof(wl2), "wl2");
  unsigned int write_limit; klee_make_symbolic(&write_limit, sizeof(write_limit), "write_limit");
  unsigned int secondary_limit; klee_make_symbolic(&secondary_limit, sizeof(secondary_limit), "secondary_limit");
  unsigned int copy_len; klee_make_symbolic(&copy_len, sizeof(copy_len), "copy_len");
  klee_assume(role_managed || out_offset < TOTAL_SZ);
  klee_assume((token != 0 && wl1 == TOTAL_SZ) || (token == 0 && wl1 == DATA_SZ + U32_SZ));
  klee_assume((out_offset < DATA_SZ && wl1 > DATA_SZ && wl2 == DATA_SZ) || (!(out_offset < DATA_SZ && wl1 > DATA_SZ) && wl2 == wl1));
  klee_assume(secondary_limit == out_offset + window_sz);
  klee_assume((role_secondary && window_sz > 0 && secondary_limit < wl2 && write_limit == secondary_limit) || (!(role_secondary && window_sz > 0 && secondary_limit < wl2) && write_limit == wl2));
  klee_assume((out_offset < write_limit && copy_len == (payload_len < (write_limit - out_offset) ? payload_len : (write_limit - out_offset))) || (out_offset >= write_limit && copy_len == 0));
  klee_assume(copy_len != 0);
  assert(out_offset + copy_len <= TOTAL_SZ);
  return 0;}
