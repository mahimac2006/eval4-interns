#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 postproc_update_buf_state — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
int main(void){
  unsigned int job_desc_buf_nonnull; klee_make_symbolic(&job_desc_buf_nonnull, sizeof(job_desc_buf_nonnull), "job_desc_buf_nonnull");
  unsigned int job_desc_count; klee_make_symbolic(&job_desc_count, sizeof(job_desc_count), "job_desc_count");
  klee_assume(job_desc_buf_nonnull <= 1);
  assert(job_desc_buf_nonnull != 0 || job_desc_count == 0);
  return 0;}
