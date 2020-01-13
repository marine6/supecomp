#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "ast.h"
#include "tree_dump.h"
#include "elang.h"


char* string_of_unop(enum unop_t u){
  switch(u){
  case ENEG: return "-";
  }
  assert(0);
}

char* string_of_binop(enum binop_t b){
  switch(b){
  case EADD: return "+";
  case ESUB: return "-";
  case EMUL: return "*";
  case EDIV: return "/";
  case EMOD: return "%";
  case CEQ: return "==";
  case CNEQ: return "!=";
  case CLT: return "<";
  case CGT: return ">";
  case CLE: return "<=";
  case CGE: return ">=";
  }
  assert(0);
}

void print_expression(FILE* fd, struct expression* e){
  switch(e->etype){
  case EINT:
    fprintf(fd, "%d", e->eint.i);
    break;
  case EVAR:
    fprintf(fd, "%s", e->var.s);
    break;
  case EUNOP:
    fprintf(fd, "(%s", string_of_unop(e->unop.unop));
    print_expression(fd, e->unop.e);
    fprintf(fd, ")");
    break;
  case EBINOP:
    fprintf(fd, "(");
    print_expression(fd, e->binop.e1);
    fprintf(fd, "%s", string_of_binop(e->binop.binop));
    print_expression(fd, e->binop.e2);
    fprintf(fd, ")");
    break;
  }
}

void print_instruction(FILE* fd, struct instruction* i){
  list* n;
  switch(i->type){
  case IIFTHENELSE:
    fprintf(fd, "if(");
    print_expression(fd, i->iif.cmp);
    fprintf(fd, ")");
    print_instruction(fd, i->iif.ithen);
    if(i->iif.ielse){
      fprintf(fd, " else ");
      print_instruction(fd, i->iif.ielse);
    }
    fprintf(fd, "\n");
    break;
  case IWHILE:
    fprintf(fd, "while(");
    print_expression(fd, i->iwhile.cmp);
    fprintf(fd, ")");
    print_instruction(fd, i->iwhile.i);
    fprintf(fd, "\n");
    break;
  case IASSIGN:
    fprintf(fd, "%s = ", i->iassign.var);
    print_expression(fd, i->iassign.e);
    fprintf(fd, ";\n");
    break;
  case IRETURN:
    fprintf(fd, "return ");
    print_expression(fd, i->ireturn.e);
    fprintf(fd, ";\n");
    break;
  case IPRINT:
    fprintf(fd, "print ");
    print_expression(fd, i->iprint.e);
    fprintf(fd, ";\n");
    break;
  case IBLOCK:
    n = i->iblock.l;
    fprintf(fd, "{\n");
    while(n){
      print_instruction(fd, n->elt);
      n = n->next;
    }
    fprintf(fd, "}\n");
    break;
  }
}
void print_eprog(FILE* fd, struct eprog* p){
  if(!p){
    fprintf(fd, "NULL eprog\n");
    return;
  }
  fprintf(fd, "%s(", p->fname);
  list* l = p->args;
  while(l){
    fprintf(fd, "%s", (char*)l->elt);
    l = l->next;
    if(l)
      fprintf(fd, ", ");
  }
  fprintf(fd, ")");

  print_instruction(fd, p->body);
}
