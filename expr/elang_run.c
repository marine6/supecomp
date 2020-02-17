#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "ast.h"
#include "tree_dump.h"
#include "elang.h"
#include "state.h"

int run_unop(enum unop_t u, int e){
  assert(0);
}

int run_binop(enum binop_t b, int e1, int e2){
  assert(0);
}

int run_expression(string_int_state_t* s, struct expression* e){
  printf("run_expression: unexpected expression type: %d", e->etype);
  exit(1);
}

int* run_instruction(string_int_state_t** s, struct instruction* i){
  printf("run_instruction: unexpected instruction type: %d", i->type);
  exit(1);
}

int run_eprog(struct eprog* p, struct list* args){
  if(!p){
    printf("run_eprog: NULL eprog\n");
    exit(1);
  }
  string_int_state_t* s = NULL;
  // Construction de l'état initial

  list* args_name = p->args;
  list* args_val = args;

  while (args_val) {
      int value = * (int *) args_val->elt;
      string_int_set_val(s,args_name->elt, value);
      args_name = args_name->next;
      args_val = args_val->next;
  }

  // Appel de run_instruction et retour de la valeur de retour
     terminate_string_int_state(s);
     return 0;
}
