#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "elang.h"
#include "elang_print.h"
#include "rtl.h"
#include "rtl_print.h"

void print_rtl_op(FILE* fd, rtl_op* n){
  switch(n->type){
  case RLABEL:
    fprintf(fd, ".n%d:", n->label.lab);
    break;
  case RMOV:
    fprintf(fd, "r%d <- r%d", n->mov.rd, n->mov.rs);
    break;
  case RRET:
    fprintf(fd, "return r%d", n->ret.rs);
    break;
  case RPRINT:
    fprintf(fd, "print r%d", n->print.rs);
    break;
  case RGOTO:
    fprintf(fd, "goto n%d", n->rgoto.succ);
    break;
  case RBRANCH:
    fprintf(fd, "r%d ? goto n%d : goto n%d",
            n->branch.rs, n->branch.succtrue, n->branch.succfalse);
    break;
  case RBINOP:
    fprintf(fd, "r%d <- r%d %s r%d", n->binop.rd,
            n->binop.rs1, string_of_binop(n->binop.binop), n->binop.rs2);
    break;
  case RUNOP:
    fprintf(fd, "r%d <- %s r%d", n->unop.rd,
            string_of_unop(n->unop.unop), n->unop.rs);
    break;
  case RIMM:
    fprintf(fd, "r%d <- %d", n->imm.rd, n->imm.imm);
    break;
  }
}

void print_rtl_ops(FILE* fd, list* ns){
  if (ns){
    print_rtl_op(fd, ns->elt);
    fprintf(fd, "\n");
    print_rtl_ops(fd, ns->next);
  }
}

void print_rtl(FILE* fd, rtl* r){
  if(!r) return;
  fprintf(fd, "n%d:\n", r->id);
  print_rtl_ops(fd, r->ops);
  print_rtl(fd, r->next);
}

void print_rtl_prog(FILE* fd, rtl_prog* p){
  if(!p){
    fprintf(fd, "NULL rtlprog\n");
    return;
  }
  fprintf(fd, "%s( ", p->fname);
  list* l = p->args;
  while(l){
    fprintf(fd, "r%d", (int)(unsigned long)l->elt);
    l = l->next;
    if(l)
      fprintf(fd, ", ");
  }
  fprintf(fd, "):\n");
  fprintf(fd, "goto n%d\n", p->entry);
  print_rtl(fd, p->graph);
}
