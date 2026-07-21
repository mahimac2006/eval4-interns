#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 dmamove_finalize_pending — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define DMA_MAX_MOVE_SIZE 65536
int main(void){
  unsigned int pd0_length; klee_make_symbolic(&pd0_length, sizeof(pd0_length), "pd0_length");
  unsigned int pd1_length; klee_make_symbolic(&pd1_length, sizeof(pd1_length), "pd1_length");
  klee_assume(pd0_length == 0);
  assert(pd1_length <= DMA_MAX_MOVE_SIZE);
  return 0;}
