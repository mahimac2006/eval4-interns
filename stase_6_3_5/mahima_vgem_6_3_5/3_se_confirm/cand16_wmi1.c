#include "klee.h"
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef unsigned long long u64; typedef signed char s8; typedef short s16; typedef int s32;
typedef unsigned char uint8_t; typedef unsigned short uint16_t; typedef unsigned int uint32_t;
typedef unsigned long long uint64_t; typedef long long int64_t; typedef int int32_t;
typedef unsigned long uintptr_t; typedef unsigned long size_t; typedef long ssize_t;
/* WMI-1 dmamove_finalize_pending — SE oracle from SA rule WMI-1_SignalDivergence_UngovernedSignal */
#define PENDING_DESCS_CAP 64
int main(void){
  unsigned int pending_count; klee_make_symbolic(&pending_count, sizeof(pending_count), "pending_count");
  assert(pending_count <= PENDING_DESCS_CAP);
  return 0;}
