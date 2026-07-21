#ifndef KLEE_REPLAY_SHIM_H
#define KLEE_REPLAY_SHIM_H
#include <stddef.h>
void klee_make_symbolic(void *addr, size_t nbytes, const char *name);
void klee_assume(unsigned long condition);
unsigned klee_int(const char *name);
void klee_assert(int condition);
#endif
