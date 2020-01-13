#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "ast.h"
#include "tree_dump.h"
#include "elang.h"
#include "elang_print.h"
#include "cfg.h"
#include "cfg_print.h"


void print_node(FILE* fd, int id, node_t* n){
  switch(n->type){
  case NODE_GOTO:
    fprintf(fd, "n%d [label=\" goto n%d\"]\n", id, n->goto_succ);
    fprintf(fd, "n%d -> n%d [label=\"\"]\n", id, n->goto_succ);
    break;
  case NODE_COND:
    fprintf(fd, "n%d [label=\"", id);
    print_expression(fd, n->cond.cond);
    fprintf(fd, "\"]\n");
    fprintf(fd, "n%d -> n%d [label=\"then\"]\n", id, n->cond.succ1);
    fprintf(fd, "n%d -> n%d [label=\"else\"]\n", id, n->cond.succ2);
    break;
  case NODE_ASSIGN:
    fprintf(fd, "n%d [label=\"%s = ", id, n->assign.var);
    print_expression(fd, n->assign.e);
    fprintf(fd, "\"]\n");
    fprintf(fd, "n%d -> n%d\n", id, n->assign.succ);
    break;
  case NODE_PRINT:
    fprintf(fd, "n%d [label=\"print ", id);
    print_expression(fd, n->print.e);
    fprintf(fd, "\"]\n");
    fprintf(fd, "n%d -> n%d\n", id, n->print.succ);
    break;
  case NODE_RETURN:
    fprintf(fd, "n%d [label=\"return ", id);
    print_expression(fd, n->ret.e);
    fprintf(fd, "\"]\n");
    break;
  }
}

void print_cfg(FILE* fd, cfg* c){
  if(!c) return;
  print_node(fd, c->id, c->node);
  print_cfg(fd, c->next);
}

void print_cfg_prog(FILE* fd, cfg_prog* p){
  if(!p){
    fprintf(fd, "NULL cfgprog\n");
    return;
  }
  fprintf(fd, "digraph %s {\n", p->fname);
  fprintf(fd, "nentry [label=\"%s(", p->fname);
  list* l = p->args;
  while(l){
    fprintf(fd, "%s", (char*)l->elt);
    l = l->next;
    if(l)
      fprintf(fd, ", ");
  }
  fprintf(fd, ")\", shape=house]\n");
  fprintf(fd, "nentry -> n%d\n", p->entry);
  print_cfg(fd, p->graph);
  fprintf(fd, "}\n");
}
