#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 psmgr_create — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
#define PSMGR_ROLE_MAX 3
int main(void){
  unsigned int sess_role; klee_make_symbolic(&sess_role, sizeof(sess_role), "sess_role");
  klee_assume(sess_role == 0);
  assert(sess_role < PSMGR_ROLE_MAX);
  return 0;}
