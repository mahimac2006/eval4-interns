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
#define TRAILER 4
int main(void){
  unsigned int out_offset; klee_make_symbolic(&out_offset, sizeof(out_offset), "out_offset");
  unsigned int payload_len; klee_make_symbolic(&payload_len, sizeof(payload_len), "payload_len");
  unsigned int token; klee_make_symbolic(&token, sizeof(token), "token");
  unsigned int base_limit; klee_make_symbolic(&base_limit, sizeof(base_limit), "base_limit");
  unsigned int write_limit; klee_make_symbolic(&write_limit, sizeof(write_limit), "write_limit");
  unsigned int copy_len; klee_make_symbolic(&copy_len, sizeof(copy_len), "copy_len");
  klee_assume(base_limit == (token != 0 ? TOTAL_SZ : (DATA_SZ + TRAILER)));
  klee_assume(write_limit == ((out_offset < DATA_SZ && base_limit > DATA_SZ) ? DATA_SZ : base_limit));
  klee_assume(copy_len == ((payload_len < (write_limit - (out_offset < write_limit ? out_offset : write_limit))) ? payload_len : (write_limit - (out_offset < write_limit ? out_offset : write_limit))));
  assert(copy_len == 0 || (out_offset + copy_len) <= TOTAL_SZ);
  return 0;}
