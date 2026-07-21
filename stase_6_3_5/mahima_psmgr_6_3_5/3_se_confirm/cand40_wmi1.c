#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 psmgr_setsockopt — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
#define PSMGR_CLASS_BASIC 0
#define PSMGR_CLASS_EXTENDED 2
#define BASIC_MODE_MAX 4
#define EXTENDED_MODE_MAX 16
int main(void){
  unsigned int opt_enc_mode; klee_make_symbolic(&opt_enc_mode, sizeof(opt_enc_mode), "opt_enc_mode");
  unsigned int sess_enc_class; klee_make_symbolic(&sess_enc_class, sizeof(sess_enc_class), "sess_enc_class");
  klee_assume(opt_enc_mode < EXTENDED_MODE_MAX);
  klee_assume(sess_enc_class == PSMGR_CLASS_BASIC);
  assert(opt_enc_mode < BASIC_MODE_MAX);
  return 0;}
