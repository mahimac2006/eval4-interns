#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-3 psmgr_process_commit_req — SE oracle from SA rule WMI-3c_AttackerContent_PreinstalledPointerGate */
int main(void){
  unsigned long handler_ptr; klee_make_symbolic(&handler_ptr, sizeof(handler_ptr), "handler_ptr");
  int is_valid_handler; klee_make_symbolic(&is_valid_handler, sizeof(is_valid_handler), "is_valid_handler");
  klee_assume(handler_ptr != 0);
  assert(is_valid_handler != 0);
  return 0;}
