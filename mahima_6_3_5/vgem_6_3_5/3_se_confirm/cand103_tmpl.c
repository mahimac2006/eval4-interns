#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 pipeline_ioctl_submit_pp — SE oracle from SA rule ? */
int main(void){
  int signal_ungoverned; klee_make_symbolic(&signal_ungoverned, sizeof(signal_ungoverned), "signal_ungoverned");
  int view_a; klee_make_symbolic(&view_a, sizeof(view_a), "view_a");
  int view_b; klee_make_symbolic(&view_b, sizeof(view_b), "view_b");
  int freed; klee_make_symbolic(&freed, sizeof(freed), "freed");
  klee_assume(signal_ungoverned == 1);
  klee_assume(freed == 0);
  assert(view_a == view_b);
  return 0;}
