#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 psmgr_sendmsg — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
#define PSMGR_BUF_DATA_SZ 1024
int main(void){
  unsigned int new_window_sz; klee_make_symbolic(&new_window_sz, sizeof(new_window_sz), "new_window_sz");
  klee_assume(new_window_sz != 0);
  klee_assume(new_window_sz <= PSMGR_BUF_DATA_SZ);
  assert(new_window_sz >= 1 && new_window_sz <= PSMGR_BUF_DATA_SZ);
  return 0;}
