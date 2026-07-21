#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_init — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
int main(void){
  unsigned int write_count_off; klee_make_symbolic(&write_count_off, sizeof(write_count_off), "write_count_off");
  unsigned int data_sz; klee_make_symbolic(&data_sz, sizeof(data_sz), "data_sz");
  klee_assume(write_count_off == data_sz + 4);
  assert(write_count_off == data_sz + 4);
  return 0;}
