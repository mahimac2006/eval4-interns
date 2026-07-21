#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_process_data — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define PSMGR_BUF_DATA_SZ 128
#define PSMGR_BUF_WRITE_THRESH 16
int main(void){
  unsigned int write_count; klee_make_symbolic(&write_count, sizeof(write_count), "write_count");
  unsigned int out_offset; klee_make_symbolic(&out_offset, sizeof(out_offset), "out_offset");
  klee_assume(out_offset < PSMGR_BUF_DATA_SZ);
  klee_assume(write_count < PSMGR_BUF_WRITE_THRESH);
  assert(write_count + 1 <= PSMGR_BUF_WRITE_THRESH);
  return 0;}
