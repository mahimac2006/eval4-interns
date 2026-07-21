#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 psmgr_create — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
#define CEILING 31
int main(void){
  int proc_param; klee_make_symbolic(&proc_param, sizeof(proc_param), "proc_param");
  klee_assume(proc_param <= CEILING);
  assert(proc_param >= 0 && proc_param <= CEILING);
  return 0;}
