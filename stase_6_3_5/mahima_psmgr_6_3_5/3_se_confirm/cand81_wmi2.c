#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_connect — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
int main(void){
  unsigned int sess_session_id; klee_make_symbolic(&sess_session_id, sizeof(sess_session_id), "sess_session_id");
  unsigned int peer_session_id; klee_make_symbolic(&peer_session_id, sizeof(peer_session_id), "peer_session_id");
  assert(sess_session_id != peer_session_id);
  return 0;}
