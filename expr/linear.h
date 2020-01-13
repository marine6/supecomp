#ifndef LINEAR_H
#define LINEAR_H

#include "rtl.h"

typedef struct linear_prog {
  char* fname;
  list* args;
  list* ops;
} linear_prog;

#endif
