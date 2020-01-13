#ifndef REGALLOC_H
#define REGALLOC_H

#include "linear.h"

typedef enum loc_t {STACK, PARAM, REG} loc_t;

typedef struct loc {
  enum loc_t type;
  union {
    int stkoffset;
    int paramnum;
    int reg;
  };
} loc;

typedef struct allocation {
  struct allocation* next;
  int pseudoreg;
  struct loc loc;
} allocation;

allocation* regalloc_prog(linear_prog* p, int*);
void print_allocation(FILE* f, allocation* alloc);
loc* get_reg_loc(allocation*, int);
void free_allocation(allocation*);
#endif
