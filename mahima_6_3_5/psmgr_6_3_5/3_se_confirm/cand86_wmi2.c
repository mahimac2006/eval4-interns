#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_connect — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define ROLE_PRIMARY 1
#define ROLE_SECONDARY 2
#define ROLE_FORWARD 3
#define STATE_NEGO_2 2
int main(void){
  unsigned int sess_role; klee_make_symbolic(&sess_role, sizeof(sess_role), "sess_role");
  unsigned int peer_role; klee_make_symbolic(&peer_role, sizeof(peer_role), "peer_role");
  unsigned int sess_state; klee_make_symbolic(&sess_state, sizeof(sess_state), "sess_state");
  unsigned int peer_state; klee_make_symbolic(&peer_state, sizeof(peer_state), "peer_state");
  klee_assume(sess_role == ROLE_PRIMARY);
  klee_assume(!(sess_role == ROLE_PRIMARY && peer_role != ROLE_SECONDARY));
  klee_assume(!(sess_role == ROLE_SECONDARY && peer_role != ROLE_PRIMARY));
  klee_assume(!(sess_role == ROLE_FORWARD && peer_role != ROLE_FORWARD));
  klee_assume((sess_role == ROLE_PRIMARY || sess_role == ROLE_SECONDARY) ? (sess_state == STATE_NEGO_2 && peer_state == STATE_NEGO_2) : 1);
  assert(sess_state == STATE_NEGO_2 && peer_state == STATE_NEGO_2);
  return 0;}
