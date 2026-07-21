#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 psmgr_connect — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
#define PSMGR_ENC_MODE_MAX 16
#define PSMGR_WINDOW_MAX 65535
int main(void){
  unsigned int enc_mode; klee_make_symbolic(&enc_mode, sizeof(enc_mode), "enc_mode");
  unsigned int proc_param; klee_make_symbolic(&proc_param, sizeof(proc_param), "proc_param");
  unsigned int window_sz; klee_make_symbolic(&window_sz, sizeof(window_sz), "window_sz");
  assert(enc_mode < PSMGR_ENC_MODE_MAX && window_sz > 0 && window_sz <= PSMGR_WINDOW_MAX);
  return 0;}
