#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 dmamove_ioctl — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
int main(void){
  unsigned int dst_offset; klee_make_symbolic(&dst_offset, sizeof(dst_offset), "dst_offset");
  unsigned int length; klee_make_symbolic(&length, sizeof(length), "length");
  unsigned int dst_size; klee_make_symbolic(&dst_size, sizeof(dst_size), "dst_size");
  klee_assume(dst_offset <= dst_size);
  klee_assume(length <= dst_size - dst_offset);
  assert(dst_offset + length <= dst_size);
  return 0;}
