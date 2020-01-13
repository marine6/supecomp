#ifndef LINEAR_GEN_H
#define LINEAR_GEN_H

linear_prog* linearize_prog(rtl_prog* rtl);
void free_lin(linear_prog*);
#endif
