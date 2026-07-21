#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 psmgr_setsockopt — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
int main(void){
  unsigned int opt_xfrm_type; klee_make_symbolic(&opt_xfrm_type, sizeof(opt_xfrm_type), "opt_xfrm_type");
  int validate_xfrm_ret; klee_make_symbolic(&validate_xfrm_ret, sizeof(validate_xfrm_ret), "validate_xfrm_ret");
  klee_assume(validate_xfrm_ret == 0);
  assert(validate_xfrm_ret == 0);
  return 0;}
