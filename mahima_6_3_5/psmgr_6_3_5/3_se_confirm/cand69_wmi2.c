#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_sendmsg — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define BASE_MASK 1028
#define IN_BITS 65
int main(void){
  unsigned int write_count; klee_make_symbolic(&write_count, sizeof(write_count), "write_count");
  unsigned int token; klee_make_symbolic(&token, sizeof(token), "token");
  unsigned int mask; klee_make_symbolic(&mask, sizeof(mask), "mask");
  klee_assume((write_count > 0 || token != 0) ? mask == BASE_MASK + IN_BITS : mask == BASE_MASK);
  assert(mask == BASE_MASK || mask == BASE_MASK + IN_BITS);
  return 0;}
