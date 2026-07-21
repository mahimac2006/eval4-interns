#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 pipeline_ioctl_submit_dma — SE oracle from SA rule ? */
int main(void){
  int attacker_input; klee_make_symbolic(&attacker_input, sizeof(attacker_input), "attacker_input");
  int producer_view; klee_make_symbolic(&producer_view, sizeof(producer_view), "producer_view");
  int consumer_view; klee_make_symbolic(&consumer_view, sizeof(consumer_view), "consumer_view");
  klee_assume(attacker_input == 1);
  assert(producer_view == consumer_view);
  return 0;}
