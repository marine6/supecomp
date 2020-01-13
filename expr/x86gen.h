#ifndef X86_GEN_H
#define X86_GEN_H
#include "linear.h"
#include "regalloc.h"


void x86_of_lin_prog(FILE* f, linear_prog* rtl, int m64);

#endif
