#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_sendmsg — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define WUP_SZ 8
int main(void){
  unsigned int hdr_payload_len; klee_make_symbolic(&hdr_payload_len, sizeof(hdr_payload_len), "hdr_payload_len");
  unsigned int wup_len; klee_make_symbolic(&wup_len, sizeof(wup_len), "wup_len");
  klee_assume(wup_len == (hdr_payload_len < WUP_SZ ? hdr_payload_len : WUP_SZ));
  klee_assume(wup_len >= WUP_SZ);
  assert(wup_len <= WUP_SZ);
  return 0;}
