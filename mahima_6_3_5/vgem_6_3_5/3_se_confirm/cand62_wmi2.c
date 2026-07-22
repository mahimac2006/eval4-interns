#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 dmamove_fetch_ring — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define DMA_MAX_DESC_COUNT 64
int main(void){
  unsigned int desc_count; klee_make_symbolic(&desc_count, sizeof(desc_count), "desc_count");
  unsigned int state_desc_count; klee_make_symbolic(&state_desc_count, sizeof(state_desc_count), "state_desc_count");
  klee_assume(desc_count <= DMA_MAX_DESC_COUNT);
  klee_assume(desc_count != 0);
  assert(state_desc_count <= desc_count);
  return 0;}
