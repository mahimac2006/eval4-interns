#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 dmamove_job_submit — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
#define VGEM_DMA_FLAG_SRC_STAGING 1
int main(void){
  unsigned int flags; klee_make_symbolic(&flags, sizeof(flags), "flags");
  unsigned int src_role; klee_make_symbolic(&src_role, sizeof(src_role), "src_role");
  klee_assume(src_role == (flags & VGEM_DMA_FLAG_SRC_STAGING));
  assert(src_role == 0 || src_role == VGEM_DMA_FLAG_SRC_STAGING);
  return 0;}
