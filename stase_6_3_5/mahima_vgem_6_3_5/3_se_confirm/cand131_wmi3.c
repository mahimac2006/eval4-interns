#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-3 postproc_update_buf_state — SE oracle from SA rule WMI-3_AttackerContent_IntoAuthoritativePosition */
#define SIZEOF_U32 4
int main(void){
  unsigned int src_size; klee_make_symbolic(&src_size, sizeof(src_size), "src_size");
  unsigned int dst_size; klee_make_symbolic(&dst_size, sizeof(dst_size), "dst_size");
  klee_assume(dst_size >= src_size);
  assert((src_size / SIZEOF_U32) * SIZEOF_U32 <= dst_size);
  return 0;}
