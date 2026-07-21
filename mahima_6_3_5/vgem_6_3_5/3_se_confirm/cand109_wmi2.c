#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 pipeline_ioctl — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define JOB_TYPE_PP 0
#define JOB_TYPE_DMA 1
int main(void){
  unsigned int job_type; klee_make_symbolic(&job_type, sizeof(job_type), "job_type");
  assert(job_type == JOB_TYPE_PP || job_type == JOB_TYPE_DMA);
  return 0;}
