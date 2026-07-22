#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-2 psmgr_session_lookup — SE oracle from SA rule WMI-2_LiveResourceInconsistency */
#define CLASS_BASIC 0
#define CLASS_EXTENDED 1
#define CLASS_PRIMARY_EXT 2
#define NUM_CLASSES 3
int main(void){
  unsigned int enc_class; klee_make_symbolic(&enc_class, sizeof(enc_class), "enc_class");
  klee_assume(enc_class == CLASS_BASIC || enc_class == CLASS_EXTENDED || enc_class == CLASS_PRIMARY_EXT);
  assert(enc_class < NUM_CLASSES);
  return 0;}
