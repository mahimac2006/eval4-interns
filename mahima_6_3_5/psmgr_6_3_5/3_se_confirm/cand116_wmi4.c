#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-4 psmgr_exec — SE oracle from SA rule WMI-4_ArbitraryAccess_TargetOrExtentFromField */
#define PSMGR_BUF_COMMITTED 1
#define VALID_HANDLER 4096
int main(void){
  unsigned long handler; klee_make_symbolic(&handler, sizeof(handler), "handler");
  unsigned int token; klee_make_symbolic(&token, sizeof(token), "token");
  unsigned int write_count; klee_make_symbolic(&write_count, sizeof(write_count), "write_count");
  klee_assume(write_count == PSMGR_BUF_COMMITTED);
  klee_assume(token != 0);
  klee_assume(handler != 0);
  assert(handler == VALID_HANDLER);
  return 0;}
