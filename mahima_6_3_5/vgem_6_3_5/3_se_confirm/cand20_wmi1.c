#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 dmamove_job_execute — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
int main(void){
  unsigned long completion_token; klee_make_symbolic(&completion_token, sizeof(completion_token), "completion_token");
  unsigned int completion_value; klee_make_symbolic(&completion_value, sizeof(completion_value), "completion_value");
  unsigned long dst_buf_size; klee_make_symbolic(&dst_buf_size, sizeof(dst_buf_size), "dst_buf_size");
  klee_assume(completion_token != 0);
  assert(completion_token < dst_buf_size);
  return 0;}
