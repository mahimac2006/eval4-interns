#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-3 pipeline_open — SE oracle from SA rule WMI-3_AttackerContent_IntoAuthoritativePosition */
int main(void){
  int job_count; klee_make_symbolic(&job_count, sizeof(job_count), "job_count");
  klee_assume(job_count == 0);
  assert(job_count == 0);
  return 0;}
