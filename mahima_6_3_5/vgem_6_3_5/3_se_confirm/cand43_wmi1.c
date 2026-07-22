#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 postproc_job_submit — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
#define VGEM_PP_FLAG_STAGE_INTERMEDIATE 1
int main(void){
  unsigned int flags; klee_make_symbolic(&flags, sizeof(flags), "flags");
  assert(flags <= VGEM_PP_FLAG_STAGE_INTERMEDIATE);
  return 0;}
