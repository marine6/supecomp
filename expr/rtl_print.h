#ifndef RTL_PRINT_H
#define RTL_PRINT_H

#include <stdio.h>
#include "rtl.h"

void print_rtl_op(FILE* fd, rtl_op* n);
void print_rtl_ops(FILE* fd, list* ns);
void print_rtl_prog(FILE*, rtl_prog*);

#endif
