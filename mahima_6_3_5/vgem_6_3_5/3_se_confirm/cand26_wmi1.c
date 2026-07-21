#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 dmamove_job_exec — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
int main(void){
  unsigned int pending_count; klee_make_symbolic(&pending_count, sizeof(pending_count), "pending_count");
  unsigned int pending_capacity; klee_make_symbolic(&pending_capacity, sizeof(pending_capacity), "pending_capacity");
  klee_assume(pending_count > 0);
  assert(pending_count <= pending_capacity);
  return 0;}
