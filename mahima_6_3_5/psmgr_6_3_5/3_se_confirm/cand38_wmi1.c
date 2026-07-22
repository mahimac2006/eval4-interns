#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 psmgr_setsockopt — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
#define STATE_INIT 0
#define STATE_NEGO_1 1
#define STATE_NEGO_2 2
#define ROLE_FORWARD 2
int main(void){
  unsigned int role; klee_make_symbolic(&role, sizeof(role), "role");
  unsigned int cur_state; klee_make_symbolic(&cur_state, sizeof(cur_state), "cur_state");
  unsigned int enc_xfrm_validated; klee_make_symbolic(&enc_xfrm_validated, sizeof(enc_xfrm_validated), "enc_xfrm_validated");
  klee_assume(cur_state == STATE_INIT);
  klee_assume(role == ROLE_FORWARD);
  klee_assume(enc_xfrm_validated == 0);
  assert(!(role == ROLE_FORWARD) || enc_xfrm_validated == 1);
  return 0;}
