#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-3 postproc_job_submit — SE oracle from SA rule WMI-3_AttackerContent_IntoAuthoritativePosition */
#define PAGE_SIZE 4096
#define PP_MAX_DESC_COUNT 1024
int main(void){
  unsigned long pixel_size; klee_make_symbolic(&pixel_size, sizeof(pixel_size), "pixel_size");
  unsigned int desc_count; klee_make_symbolic(&desc_count, sizeof(desc_count), "desc_count");
  klee_assume(desc_count == (unsigned int)((pixel_size + PAGE_SIZE - 1) / PAGE_SIZE));
  klee_assume(desc_count <= PP_MAX_DESC_COUNT);
  assert((pixel_size + PAGE_SIZE - 1) / PAGE_SIZE == desc_count);
  return 0;}
