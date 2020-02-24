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
    }
    assert(0);
}

int run_expression(string_int_state_t* s, struct expression* e){
    switch(e->etype){
        case EINT:
           return e->eint.i;
        case EVAR:
            return string_int_get_val(s,e->var.s);

        case EUNOP:
            return run_unop(e->unop.unop,run_expression(s->next,e->unop.e));
        case EBINOP:
            return run_binop(e->binop.binop,run_expression(s->next,e->binop.e1),run_expression(s->next,e->binop.e2));

    }
  printf("run_expression: unexpected expression type: %d", e->etype);
  exit(1);
}

int* run_instruction(string_int_state_t** s, struct instruction* i){
    switch(i->type){
        case IIFTHENELSE:
            if(i->iif.cmp){
                int *i_if = malloc(sizeof(int));
                *i_if = run_expression(*s,i->iassign.e);
                return i_if;
            }

            else if(i->iif.ithen){
                return run_instruction(s,i->iif.ithen);
            }

            else if(i->iif.ielse){
                return run_instruction(s,i->iif.ielse);
            }
            break;
        case IWHILE:
            if(i->iwhile.cmp){
                int *i_while = malloc(sizeof(int));
                *i_while = run_expression(*s,i->iwhile.cmp);
                return i_while;
            }
            else if(i->iwhile.i){
                return run_instruction(s,i->iwhile.i);
            }
        case IASSIGN:
            if(i->iassign.var){
                // err de compilation
                // run_expression(*s,i->iassign.var);
                int *i_assign = malloc(sizeof(int));
                *i_assign = run_expression(*s,i->iassign.var);
                return i_assign;
            }
            else if(i->iassign.e){
                int *i_assign = malloc(sizeof(int));
                *i_assign = run_expression(*s,i->iassign.e);
                return i_assign;
            }
            break;
        case IRETURN:{
            int *i_return = malloc(sizeof(int));
            *i_return = run_expression(*s,i->ireturn.e);
            return i_return;
        }
        case IPRINT:{
            int *i_print = malloc(sizeof(int));
            *i_print = run_expression(*s,i->iprint.e);
            return i_print;
        }
        case IBLOCK:
        {
            list* n = i->iblock.l;
            while(n){
                run_instruction(s,n->elt);
                n = n -> next;
            }
        }



    }
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
