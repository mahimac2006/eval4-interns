#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_process_data — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define PSMGR_ROLE_FORWARD 3
int main(void){
  unsigned int role; klee_make_symbolic(&role, sizeof(role), "role");
  unsigned int peer_null; klee_make_symbolic(&peer_null, sizeof(peer_null), "peer_null");
  unsigned int peer_sk_null; klee_make_symbolic(&peer_sk_null, sizeof(peer_sk_null), "peer_sk_null");
  klee_assume(role == PSMGR_ROLE_FORWARD);
  klee_assume(peer_null == 0);
  klee_assume(peer_sk_null == 0);
  assert(peer_sk_null == 0);
  return 0;}
