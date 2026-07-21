#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 postproc_release — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define S32_MIN -2147483648
#define S32_MAX 2147483647
int main(void){
  int status; klee_make_symbolic(&status, sizeof(status), "status");
  assert(status >= S32_MIN && status <= S32_MAX);
  return 0;}
