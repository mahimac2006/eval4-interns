#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 psmgr_create — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
int main(void){
  unsigned int role_field; klee_make_symbolic(&role_field, sizeof(role_field), "role_field");
  unsigned int peer_id_field; klee_make_symbolic(&peer_id_field, sizeof(peer_id_field), "peer_id_field");
  klee_assume(role_field == 0);
  klee_assume(peer_id_field == 0);
  assert(role_field == 0 && peer_id_field == 0);
  return 0;}
