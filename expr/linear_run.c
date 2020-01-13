#include <stdlib.h>
#include <stdio.h>
#include "state.h"
#include "linear.h"
#include "datatypes.h"
#include "elang_run.h"

int* run_linear_at(int_int_state_t** s, list* whole, int n);

int* run_linear_op(int_int_state_t** s, list* whole, rtl_op* n){
  switch(n->type){
  case RLABEL:
    break;
  case RMOV:
    *s = int_int_set_val(*s, n->mov.rd, int_int_get_val(*s, n->mov.rs));
    break;
  case RIMM:
    *s = int_int_set_val(*s, n->imm.rd, n->imm.imm);
    break;
  case RRET:
    return some((void*)(unsigned long)int_int_get_val(*s, n->ret.rs));
    break;
  case RPRINT:
    printf("%d\n", int_int_get_val(*s, n->print.rs));
    break;
  case RBRANCH:
    if(int_int_get_val(*s, n->branch.rs))
      return run_linear_at(s, whole, n->branch.succtrue);
    return run_linear_at(s, whole, n->branch.succfalse);
    break;
  case RGOTO:
    return run_linear_at(s, whole, n->rgoto.succ);
  case RBINOP:
    {
      int e1 = int_int_get_val(*s, n->binop.rs1);
      int e2 = int_int_get_val(*s, n->binop.rs2);
      *s = int_int_set_val(*s, n->binop.rd, run_binop(n->binop.binop, e1, e2));
    }
    break;
  case RUNOP:
    {
      int e1 = int_int_get_val(*s, n->unop.rs);
      *s = int_int_set_val(*s, n->unop.rd, run_unop(n->unop.unop, e1));
    }
    break;
  }
  return NULL;
}

int* run_linear_ops(int_int_state_t** s, list* whole, list* ops){
  if (ops){
    int* res = run_linear_op(s, whole, ops->elt);
    if(res) return res;
    return run_linear_ops(s, whole, ops->next);
  }
  return NULL;
}

int* run_linear_at(int_int_state_t** s, list* whole, int id){
  list* r = whole;
  while(r){
    rtl_op* op = r->elt;
    if(op->type == RLABEL && op->label.lab == id)
      return run_linear_ops(s, whole, r);
    r = r->next;
  }
  return NULL;
}


int run_linear_prog(linear_prog* p, struct list* args){
  if(!p){
    printf("run_linear_prog: NULL linearprog\n");
    exit(1);
  }
  int_int_state_t * s = NULL;
  list* lparams = p->args;
  list* largs = args;
  while(lparams){
    if(!largs){
      printf("Not enough arguments provided (%d required, %d provided)\n", list_length(p->args), list_length(args));
      exit(1);
    }
    int v = (unsigned long)largs->elt;
    s = int_int_set_val(s, (unsigned long)lparams->elt, v);
    largs = largs->next;
    lparams = lparams->next;
  }

  int* res = run_linear_ops(&s, p->ops, p->ops);
  terminate_int_int_state(s);
  int vres = *res;
  free(res);
  return vres;
}
