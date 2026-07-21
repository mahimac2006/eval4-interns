#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 postproc_job_submit — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define PAGE_SIZE 4096
#define PP_MAX_DESC_COUNT 1024
#define TWO32 4294967296
int main(void){
  unsigned long pixel_size; klee_make_symbolic(&pixel_size, sizeof(pixel_size), "pixel_size");
  klee_assume(((pixel_size + PAGE_SIZE - 1) / PAGE_SIZE) % TWO32 <= PP_MAX_DESC_COUNT);
  assert((pixel_size + PAGE_SIZE - 1) / PAGE_SIZE <= PP_MAX_DESC_COUNT);
  return 0;}
