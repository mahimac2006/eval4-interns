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
#define MAX_SCATTER_LINEAR 63
#define MAX_SCATTER_INTERLEAVE 31
#define MAX_SCATTER_OTHER 15
#define MAX_WINREF_LINEAR 127
#define MAX_WINREF_INTERLEAVE 63
#define MAX_WINREF_OTHER 31
#define MAX_COMMIT_LINEAR 31
#define MAX_COMMIT_INTERLEAVE 15
#define MAX_COMMIT_OTHER 7
#define PARAM_MAX_GLOBAL 127
int main(void){
  unsigned int xfrm_type; klee_make_symbolic(&xfrm_type, sizeof(xfrm_type), "xfrm_type");
  unsigned int enc_mode; klee_make_symbolic(&enc_mode, sizeof(enc_mode), "enc_mode");
  unsigned int proc_param; klee_make_symbolic(&proc_param, sizeof(proc_param), "proc_param");
  klee_assume(xfrm_type == XFRM_SCATTER || xfrm_type == XFRM_WINDOW || xfrm_type == XFRM_REFLECT || xfrm_type == XFRM_COMMIT);
  klee_assume((xfrm_type == XFRM_SCATTER && ((enc_mode == MODE_LINEAR && proc_param <= MAX_SCATTER_LINEAR) || (enc_mode == MODE_INTERLEAVE && proc_param <= MAX_SCATTER_INTERLEAVE) || (enc_mode != MODE_LINEAR && enc_mode != MODE_INTERLEAVE && proc_param <= MAX_SCATTER_OTHER))) || ((xfrm_type == XFRM_WINDOW || xfrm_type == XFRM_REFLECT) && ((enc_mode == MODE_LINEAR && proc_param <= MAX_WINREF_LINEAR) || (enc_mode == MODE_INTERLEAVE && proc_param <= MAX_WINREF_INTERLEAVE) || (enc_mode != MODE_LINEAR && enc_mode != MODE_INTERLEAVE && proc_param <= MAX_WINREF_OTHER))) || (xfrm_type == XFRM_COMMIT && ((enc_mode == MODE_LINEAR && proc_param <= MAX_COMMIT_LINEAR) || (enc_mode == MODE_INTERLEAVE && proc_param <= MAX_COMMIT_INTERLEAVE) || (enc_mode != MODE_LINEAR && enc_mode != MODE_INTERLEAVE && proc_param <= MAX_COMMIT_OTHER))));
  assert(proc_param <= PARAM_MAX_GLOBAL);
  return 0;}
