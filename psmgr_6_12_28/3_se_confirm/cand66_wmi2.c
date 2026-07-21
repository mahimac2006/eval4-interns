#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_setsockopt — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define PSMGR_STATE_NEGO_2 2
#define ENC_MODE_TABLE_SZ 8
int main(void){
  unsigned int sess_state; klee_make_symbolic(&sess_state, sizeof(sess_state), "sess_state");
  unsigned int ctx_enc_mode; klee_make_symbolic(&ctx_enc_mode, sizeof(ctx_enc_mode), "ctx_enc_mode");
  klee_assume(sess_state == PSMGR_STATE_NEGO_2);
  assert(ctx_enc_mode < ENC_MODE_TABLE_SZ);
  return 0;}
