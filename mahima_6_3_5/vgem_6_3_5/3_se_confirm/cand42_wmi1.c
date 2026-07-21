#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 vgem_postproc_ctx_alloc — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
int main(void){
  unsigned int desc_count; klee_make_symbolic(&desc_count, sizeof(desc_count), "desc_count");
  unsigned int completions_cap; klee_make_symbolic(&completions_cap, sizeof(completions_cap), "completions_cap");
  assert(desc_count <= completions_cap);
  return 0;}
