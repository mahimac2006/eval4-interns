#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_setsockopt — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define XFRM_SCATTER 1
#define XFRM_WINDOW 2
#define XFRM_REFLECT 3
#define XFRM_COMMIT 4
#define MODE_LINEAR 1
#define MODE_INTERLEAVE 2
#define MAX_PARAM 127
int main(void){
  unsigned int xfrm_type; klee_make_symbolic(&xfrm_type, sizeof(xfrm_type), "xfrm_type");
  unsigned int enc_mode; klee_make_symbolic(&enc_mode, sizeof(enc_mode), "enc_mode");
  unsigned int param_max; klee_make_symbolic(&param_max, sizeof(param_max), "param_max");
  klee_assume(xfrm_type == XFRM_SCATTER || xfrm_type == XFRM_WINDOW || xfrm_type == XFRM_REFLECT || xfrm_type == XFRM_COMMIT);
  klee_assume((xfrm_type != XFRM_SCATTER) || (enc_mode == MODE_LINEAR && param_max == 63) || (enc_mode == MODE_INTERLEAVE && param_max == 31) || (enc_mode != MODE_LINEAR && enc_mode != MODE_INTERLEAVE && param_max == 15));
  klee_assume(((xfrm_type != XFRM_WINDOW) && (xfrm_type != XFRM_REFLECT)) || (enc_mode == MODE_LINEAR && param_max == 127) || (enc_mode == MODE_INTERLEAVE && param_max == 63) || (enc_mode != MODE_LINEAR && enc_mode != MODE_INTERLEAVE && param_max == 31));
  klee_assume((xfrm_type != XFRM_COMMIT) || (enc_mode == MODE_LINEAR && param_max == 31) || (enc_mode == MODE_INTERLEAVE && param_max == 15) || (enc_mode != MODE_LINEAR && enc_mode != MODE_INTERLEAVE && param_max == 7));
  assert(param_max <= MAX_PARAM);
  return 0;}
