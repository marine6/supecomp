#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "ast.h"
#include "tree_dump.h"
#include "state.h"
#include "elang.h"
#include "elang_run.h"
#include "cfg.h"

node_t* get_cfg_node(cfg* c, int id){
  if(!c) return NULL;
  if(c->id == id) return c->node;
  return get_cfg_node(c->next, id);
}

int run_cfg_node(string_int_state_t** s, cfg* c, int id){
  node_t* n = get_cfg_node(c,id);
  if(!n){
    printf("run_cfg_node: unable to find node with id %d", id);
    exit(1);
  }
  switch(n->type){
  case NODE_GOTO:
    return run_cfg_node(s, c, n->goto_succ);
    break;
  case NODE_COND:
    if(run_expression(*s, n->cond.cond)){
      return run_cfg_node(s, c, n->cond.succ1);
    } else {
      return run_cfg_node(s, c, n->cond.succ2);
    }
    break;
  case NODE_ASSIGN:
    *s = string_int_set_val(*s, n->assign.var, run_expression(*s, n->assign.e));
    return run_cfg_node(s, c, n->assign.succ);
    break;
  case NODE_PRINT:
    printf("%d\n", run_expression(*s, n->print.e));
    return run_cfg_node(s, c, n->print.succ);
    break;
  case NODE_RETURN:
    return run_expression(*s, n->ret.e);
    break;
  }
  printf("run_cfg_node: unexpected node type %d", n->type);
  exit(1);
}

int run_cfg_prog(cfg_prog* p, struct list* args){
  if(!p){
    printf("run_cfg_prog: NULL cfgprog\n");
    exit(1);
  }
  string_int_state_t * s = NULL;
  list* lparams = p->args;
  list* largs = args;
  while(lparams){
    if(!largs){
      printf("Not enough arguments provided (%d required, %d provided)\n", list_length(p->args), list_length(args));
      exit(1);
    }
    int v = (unsigned long)largs->elt;
    s = string_int_set_val(s, lparams->elt, v);
    largs = largs->next;
    lparams = lparams->next;
  }

  int res = run_cfg_node(&s, p->graph, p->entry);
  terminate_string_int_state(s);
  return res;
}
