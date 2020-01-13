#include <stdio.h>
#include "elang.h"
#include "state.h"


int run_unop(enum unop_t u, int e);

int run_binop(enum binop_t b, int e1, int e2);

int run_expression(string_int_state_t*, struct expression* e);
int run_eprog(struct eprog*, struct list* args);
