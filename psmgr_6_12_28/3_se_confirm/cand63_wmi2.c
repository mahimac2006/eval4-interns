#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_check_seq — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define DATA_SZ 256
#define MAX_MULT 8
int main(void){
  unsigned int proc_param; klee_make_symbolic(&proc_param, sizeof(proc_param), "proc_param");
  assert(proc_param * MAX_MULT <= DATA_SZ);
  return 0;}
