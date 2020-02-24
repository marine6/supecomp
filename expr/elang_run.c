#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "ast.h"
#include "tree_dump.h"
#include "elang.h"
#include "state.h"

int run_unop(enum unop_t u, int e) {
    switch (u) {
        case ENEG:
            return -e;
        default:
            return e;
    }
}

int run_binop(enum binop_t b, int e1, int e2){
    switch(b){
        case EADD: return e1+e2;
        case ESUB: return e1-e2;
        case EMUL: return e1*e2;
        case EDIV: return e1/e2;
        case EMOD: return e1%e2;
        case CEQ: return e1==e2;
        case CNEQ: return e1!=e2;
        case CLT: return e1<e2;
        case CGT: return e1>e2;
        case CLE: return e1<=e2;
        case CGE: return e1>=e2;
        default:
            printf("Unexpected binop");
            exit(1);
    }
    // assert(0);
}

int run_expression(string_int_state_t* s, struct expression* e){
    switch(e->etype){
        case EINT:
           return e->eint.i;
        case EVAR:
            return string_int_get_val(s,e->var.s);
        case EUNOP:
            return run_unop(e->unop.unop,run_expression(s,e->unop.e));
        case EBINOP:
            return run_binop(e->binop.binop,run_expression(s,e->binop.e1),run_expression(s,e->binop.e2));
        default:
            printf("run_expression: unexpected expression type: %d \n", e->etype);
            exit(1);
    }
}

int* run_instruction(string_int_state_t** s, struct instruction* i){
    // printf("run_instruction: instruction type: %d \n", i->type);
    if( i == NULL) {
        return NULL;
    }
    switch(i->type){
        case IIFTHENELSE:
            if(run_expression(*s,i->iif.cmp) > 0){
                run_instruction(s,i->iif.ithen);
            } else {
                run_instruction(s,i->iif.ielse);
            }
            break;
        case IWHILE:
            while(run_expression(*s,i->iwhile.cmp) > 0){
                run_instruction(s,i->iwhile.i);
            }
            break;
        case IASSIGN:
            *s = string_int_set_val(*s, i->iassign.var, run_expression(*s, i->iassign.e));
            break;
        case IRETURN:;
            int *i_return = malloc(sizeof(int));
            *i_return = run_expression(*s,i->ireturn.e);
            return i_return;
        case IPRINT:
            printf("%i\n", run_expression(*s,i->iprint.e));
            break;
        case IBLOCK:;
            struct list *n = i->iblock.l;
            while(n != NULL){
                int *response = run_instruction(s, n->elt);
                if (response != NULL) {
                    return response;
                }
                n = n -> next;
            }
            break;
        default:
            printf("run_instruction: unexpected instruction type: %d \n", i->type);
            break;
    }
    return NULL;
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

  while (args_name) {
      char *name = list_nth_string(args_name, 0);
      int value = list_nth_int(args_val, 0);
      s = string_int_set_val(s,name, value);
      args_name = args_name->next;
      args_val = args_val->next;
  }

  // Appel de run_instruction et retour de la valeur de retour
  int *response  = run_instruction(&s, p->body);
  if (response == NULL) {
      exit(1);
  }
  terminate_string_int_state(s);
  return *response;
}
