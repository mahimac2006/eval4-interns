#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_process_data — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define BUF_DATA_SZ 128
#define BUF_TOTAL_SZ 144
#define ROLE_MANAGED 1
#define UINT_MAX_32 4294967295
int main(void){
  unsigned int out_offset; klee_make_symbolic(&out_offset, sizeof(out_offset), "out_offset");
  unsigned int role; klee_make_symbolic(&role, sizeof(role), "role");
  klee_assume(out_offset != UINT_MAX_32);
  klee_assume(role == ROLE_MANAGED || out_offset < BUF_TOTAL_SZ);
  assert(out_offset < BUF_DATA_SZ);
  return 0;}
