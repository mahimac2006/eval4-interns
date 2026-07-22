#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 vgem_dmamove_buf_set_intermediate — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define VGEM_BUF_STATE_INIT 0
#define VGEM_BUF_STATE_POSTPROC 2
#define VGEM_BUF_STATE_COMPLETE 3
int main(void){
  int state_val; klee_make_symbolic(&state_val, sizeof(state_val), "state_val");
  unsigned int intermediate_pending; klee_make_symbolic(&intermediate_pending, sizeof(intermediate_pending), "intermediate_pending");
  klee_assume(state_val == VGEM_BUF_STATE_POSTPROC || state_val == VGEM_BUF_STATE_COMPLETE);
  assert(intermediate_pending > 0);
  return 0;}
