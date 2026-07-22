#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-3 dmamove_job_submit — SE oracle from SA rule ? */
int main(void){
  int resource_live; klee_make_symbolic(&resource_live, sizeof(resource_live), "resource_live");
  int resource_inconsistent; klee_make_symbolic(&resource_inconsistent, sizeof(resource_inconsistent), "resource_inconsistent");
  int content_attacker; klee_make_symbolic(&content_attacker, sizeof(content_attacker), "content_attacker");
  int content_trusted; klee_make_symbolic(&content_trusted, sizeof(content_trusted), "content_trusted");
  klee_assume(resource_live == 1);
  klee_assume(resource_inconsistent == 1);
  klee_assume(content_attacker == 1);
  assert(content_trusted == 1);
  return 0;}
