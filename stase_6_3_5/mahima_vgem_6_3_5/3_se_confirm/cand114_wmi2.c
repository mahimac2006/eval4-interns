#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 vgem_postproc_ctx_free — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define PP_MAX_BUFFER_SIZE 67108864
#define ELEM_SZ 4
int main(void){
  unsigned int width; klee_make_symbolic(&width, sizeof(width), "width");
  unsigned int height; klee_make_symbolic(&height, sizeof(height), "height");
  klee_assume(width != 0);
  klee_assume(height != 0);
  klee_assume(((unsigned long)width * (unsigned long)height * ELEM_SZ) <= PP_MAX_BUFFER_SIZE);
  assert(height <= (PP_MAX_BUFFER_SIZE / ELEM_SZ) / width);
  return 0;}
