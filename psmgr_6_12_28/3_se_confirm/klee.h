#ifndef KLEE_H
#define KLEE_H
#include <stddef.h>
void klee_make_symbolic(void *addr, size_t nbytes, const char *name);
void klee_assume(unsigned long condition);
#endif
