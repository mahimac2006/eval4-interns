#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_recvmsg — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define PSMGR_BUF_COMMITTED 1
int main(void){
  unsigned int write_count; klee_make_symbolic(&write_count, sizeof(write_count), "write_count");
  assert(write_count != PSMGR_BUF_COMMITTED);
  return 0;}
