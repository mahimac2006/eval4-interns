#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 token_resolve_write — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define TOKEN_TABLE_SIZE 64
int main(void){
  unsigned int slot; klee_make_symbolic(&slot, sizeof(slot), "slot");
  unsigned int gen; klee_make_symbolic(&gen, sizeof(gen), "gen");
  unsigned int token_gen_invalid; klee_make_symbolic(&token_gen_invalid, sizeof(token_gen_invalid), "token_gen_invalid");
  klee_assume(slot < TOKEN_TABLE_SIZE);
  klee_assume(gen != token_gen_invalid);
  assert(slot < TOKEN_TABLE_SIZE);
  return 0;}
