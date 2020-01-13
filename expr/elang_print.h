#include <stdio.h>
#include "elang.h"


char* string_of_unop(enum unop_t u);
char* string_of_binop(enum binop_t b);

void print_expression(FILE*, struct expression*);
void print_eprog(FILE*, struct eprog*);
