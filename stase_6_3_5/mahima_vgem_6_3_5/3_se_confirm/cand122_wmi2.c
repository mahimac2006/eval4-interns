#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 postproc_job_desc_query — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
int main(void){
  unsigned int desc_index; klee_make_symbolic(&desc_index, sizeof(desc_index), "desc_index");
  unsigned int desc_count; klee_make_symbolic(&desc_count, sizeof(desc_count), "desc_count");
  unsigned int completions_present; klee_make_symbolic(&completions_present, sizeof(completions_present), "completions_present");
  klee_assume(completions_present != 0);
  klee_assume(desc_index < desc_count);
  assert(desc_index < desc_count);
  return 0;}
