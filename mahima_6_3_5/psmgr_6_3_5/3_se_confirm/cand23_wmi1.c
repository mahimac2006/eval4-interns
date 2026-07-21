#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 psmgr_connect — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
#define ROLE_PRIMARY 0
#define ROLE_SECONDARY 1
#define ROLE_FORWARD 2
#define STATE_NEGO_2 5
int main(void){
  unsigned int role; klee_make_symbolic(&role, sizeof(role), "role");
  unsigned int sess_state; klee_make_symbolic(&sess_state, sizeof(sess_state), "sess_state");
  unsigned int peer_state; klee_make_symbolic(&peer_state, sizeof(peer_state), "peer_state");
  klee_assume(!(role == ROLE_PRIMARY || role == ROLE_SECONDARY) || (sess_state == STATE_NEGO_2 && peer_state == STATE_NEGO_2));
  assert(sess_state == STATE_NEGO_2 && peer_state == STATE_NEGO_2);
  return 0;}
