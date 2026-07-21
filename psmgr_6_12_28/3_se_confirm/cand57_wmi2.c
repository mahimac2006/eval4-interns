#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_process_data — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define BUF_COMMITTED 4294967295
#define BUF_WRITE_THRESH 1
#define HANDLER_MAX 16
int main(void){
  unsigned int write_count; klee_make_symbolic(&write_count, sizeof(write_count), "write_count");
  unsigned int handler_idx; klee_make_symbolic(&handler_idx, sizeof(handler_idx), "handler_idx");
  unsigned int token; klee_make_symbolic(&token, sizeof(token), "token");
  klee_assume(write_count != BUF_COMMITTED);
  klee_assume(write_count >= BUF_WRITE_THRESH);
  klee_assume(token != 0);
  assert(handler_idx < HANDLER_MAX);
  return 0;}
