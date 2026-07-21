#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_sendmsg — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define PSMGR_MSGHDR_SZ 8
#define PSMGR_MSG_MAX_SZ 4096
int main(void){
  unsigned int len; klee_make_symbolic(&len, sizeof(len), "len");
  unsigned int payload_len; klee_make_symbolic(&payload_len, sizeof(payload_len), "payload_len");
  klee_assume(len >= PSMGR_MSGHDR_SZ);
  klee_assume(len <= PSMGR_MSG_MAX_SZ);
  assert(payload_len <= len - PSMGR_MSGHDR_SZ);
  return 0;}
