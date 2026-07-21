#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-4 psmgr_recvmsg — SE oracle from SA rule WMI-4_ArbitraryAccess_TargetOrExtentFromField */
int main(void){
  int content_authoritative; klee_make_symbolic(&content_authoritative, sizeof(content_authoritative), "content_authoritative");
  int content_attacker; klee_make_symbolic(&content_attacker, sizeof(content_attacker), "content_attacker");
  int access_index; klee_make_symbolic(&access_index, sizeof(access_index), "access_index");
  int bound; klee_make_symbolic(&bound, sizeof(bound), "bound");
  klee_assume(content_authoritative == 1);
  klee_assume(content_attacker == 1);
  klee_assume(bound >= 1);
  klee_assume(access_index >= 0);
  assert(access_index < bound);
  return 0;}
