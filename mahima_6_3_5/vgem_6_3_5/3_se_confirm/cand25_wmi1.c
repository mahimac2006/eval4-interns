#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 dmamove_job_submit — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
#define MOVE_DESC_SIZE 32
int main(void){
  unsigned int desc_count; klee_make_symbolic(&desc_count, sizeof(desc_count), "desc_count");
  unsigned long desc_buf_size; klee_make_symbolic(&desc_buf_size, sizeof(desc_buf_size), "desc_buf_size");
  klee_assume(desc_buf_size >= (unsigned long)desc_count * MOVE_DESC_SIZE);
  assert((unsigned long)desc_count * MOVE_DESC_SIZE <= desc_buf_size);
  return 0;}
