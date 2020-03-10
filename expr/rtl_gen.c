#include <stdlib.h>
#include <string.h>
#include "elang.h"
#include "cfg.h"
#include "rtl.h"

rtl_op* new_rtl_op_mov(int rd, int rs){
  rtl_op* op = malloc(sizeof(rtl_op));
  op->type = RMOV;
  op->mov.rd = rd;
  op->mov.rs = rs;
  return op;
}

rtl_op* new_rtl_op_label(int label){
  rtl_op* op = malloc(sizeof(rtl_op));
  op->type = RLABEL;
  op->label.lab = label;
  return op;
}

rtl_op* new_rtl_op_print(int rs){
  rtl_op* op = malloc(sizeof(rtl_op));
  op->type = RPRINT;
  op->print.rs = rs;
  return op;
}

rtl_op* new_rtl_op_return(int rs){
  rtl_op* op = malloc(sizeof(rtl_op));
  op->type = RRET;
  op->ret.rs = rs;
  return op;
}

rtl_op* new_rtl_op_goto(int succ){
  rtl_op* op = malloc(sizeof(rtl_op));
  op->type = RGOTO;
  op->rgoto.succ = succ;
  return op;
}

rtl_op* new_rtl_op_branch(int rs, int succtrue, int succfalse){
  rtl_op* op = malloc(sizeof(rtl_op));
  op->type = RBRANCH;
  op->branch.rs = rs;
  op->branch.succtrue = succtrue;
  op->branch.succfalse = succfalse;
  return op;
}

rtl_op* new_rtl_op_binop(binop_t b, int rd, int rs1, int rs2){
  rtl_op* op = malloc(sizeof(rtl_op));
  op->type = RBINOP;
  op->binop.binop = b;
  op->binop.rd = rd;
  op->binop.rs1 = rs1;
  op->binop.rs2 = rs2;
  return op;
}

rtl_op* new_rtl_op_unop(unop_t u, int rd, int rs){
  rtl_op* op = malloc(sizeof(rtl_op));
  op->type = RUNOP;
  op->unop.unop = u;
  op->unop.rd = rd;
  op->unop.rs = rs;
  return op;
}

rtl_op* new_rtl_op_imm(int rd, int imm){
  rtl_op* op = malloc(sizeof(rtl_op));
  op->type = RIMM;
  op->imm.rd = rd;
  op->imm.imm = imm;
  return op;
}

typedef struct symtable {
  struct symtable* next;
  char* var;
  int reg;
} symtable;

void free_symtable(symtable* s){
  if(s){
    free(s->var);
    free_symtable(s->next);
    free(s);
  }
}

symtable* symt = NULL;

int curreg = 0;

int new_reg(){
  return curreg++;
}

int get_reg_for_var(char* v){
    struct symtable* symtable = symt;
    while(symtable){
        if(!strcmp(symtable->var, v)){
            return symtable->reg;
        }
        symtable = symtable->next;
    }
    struct symtable* new_symtable = (struct symtable*) malloc(sizeof(symtable));
    new_symtable->var = v;
    new_symtable->reg = new_reg();
    new_symtable->next = symt;
    symt = new_symtable;
    return symt->reg;
}

typedef struct expr_compiled {
  int r;
  list* ops;
} expr_compiled;

expr_compiled* new_expr_compiled(){
  expr_compiled* ec = (expr_compiled*)malloc(sizeof(expr_compiled));
  ec->ops = NULL;
  ec->r = 0;
  return ec;
}

expr_compiled* rtl_ops_of_expression(struct expression* e){
    expr_compiled* n_expr_compiled =  new_expr_compiled();
    switch (e->etype) {
        case EINT: {
            int n_reg = new_reg();
            rtl_op* new_op = new_rtl_op_imm(n_reg, e->eint.i);
            n_expr_compiled->r = n_reg;
            n_expr_compiled->ops = cons(new_op,NULL);
            break;
        }
        case EVAR: {
            n_expr_compiled->r =  get_reg_for_var(e->var.s);
            break;
        }
       case EUNOP: {
           expr_compiled* temp_expr_compiled = rtl_ops_of_expression(e->unop.e);
           int n_reg = new_reg();
           rtl_op* new_op = new_rtl_op_unop(e->unop.unop, n_reg, temp_expr_compiled->r);
           n_expr_compiled->r = n_reg;
           n_expr_compiled->ops = list_append(
                   temp_expr_compiled->ops, new_op);
           break;
       }
        case EBINOP:{
            expr_compiled* temp_expr_compiled1 = rtl_ops_of_expression(e->binop.e1);
            expr_compiled* temp_expr_compiled2 = rtl_ops_of_expression(e->binop.e2);
            int n_reg = new_reg();
            rtl_op* new_op = new_rtl_op_binop(e->binop.binop, n_reg, temp_expr_compiled1->r, temp_expr_compiled2->r);
            n_expr_compiled->r = n_reg;
            n_expr_compiled->ops = list_append(concat(temp_expr_compiled1->ops, temp_expr_compiled2->ops), new_op);
           break;
        }
   }

  return n_expr_compiled;
}

list* rtl_ops_of_cfg_node(node_t* c){
    switch (c->type) {
        case NODE_GOTO:
            return cons(new_rtl_op_goto(c->goto_succ), NULL);
        case NODE_ASSIGN: {
            expr_compiled* compiled_assign= rtl_ops_of_expression(c->assign.e);

            return concat(compiled_assign->ops, cons(new_rtl_op_mov(get_reg_for_var(c->assign.var), compiled_assign->r), cons(new_rtl_op_goto(c->assign.succ), NULL)));
        }
        case NODE_COND:{
            expr_compiled* compiled_cond= rtl_ops_of_expression(c->cond.cond);
            return list_append(compiled_cond->ops, new_rtl_op_branch(compiled_cond->r,c->cond.succ1, c->cond.succ2));
        }
        case NODE_PRINT:{
            expr_compiled* compiled_print = rtl_ops_of_expression(c->print.e);

            return concat(compiled_print->ops, cons(new_rtl_op_print(compiled_print->r), cons(new_rtl_op_goto(c->print.succ), NULL)));
        }
        case NODE_RETURN:
            {
            expr_compiled* compiled_ret = rtl_ops_of_expression(c->ret.e);
            return list_append(compiled_ret->ops, new_rtl_op_return(compiled_ret->r));
        }
        default:
            return NULL;
    }
}

rtl* rtl_of_cfg_graph(cfg* c){
    rtl * rtl_graph = malloc(sizeof(rtl));
    rtl_graph->ops = cons(new_rtl_op_label(c->id), rtl_ops_of_cfg_node(c->node));
    rtl_graph->id = c->id;
    if (c->next == NULL) {
        rtl_graph->next = NULL;
    } else {
        rtl_graph->next = rtl_of_cfg_graph(c->next);
        rtl_graph->ops = concat(rtl_graph->ops, cons(new_rtl_op_goto(c->next->id), NULL));
    }
     return rtl_graph;
}

rtl_prog* rtl_of_cfg_prog(cfg_prog* cfg){
  struct rtl_prog* rtl = (struct rtl_prog*)malloc(sizeof(struct rtl_prog));
  rtl->fname = strdup(cfg->fname);
  rtl->args = NULL;
  list* temp_args = cfg->args;
  list* args_rtl = NULL;
  while(temp_args) {
    args_rtl = list_append_int(args_rtl, get_reg_for_var(temp_args->elt));
    temp_args = temp_args->next;
  }
  rtl->args = args_rtl;
  rtl->graph = rtl_of_cfg_graph(cfg->graph);
  rtl->entry = cfg->entry;
  free_symtable(symt);
  return rtl;
}


void free_rtl_op(rtl_op* n){
  if(!n) return;
  free(n);
}

void free_rtl_ops(list* l){
  if(!l) return;
  free_rtl_ops(l->next);
  free_rtl_op(l->elt);
}

void free_rtl_graph(rtl* r){
  if(r){
    free_rtl_graph(r->next);
    free_rtl_ops(r->ops);
    //free_list(r->ops);
    free(r);
  }
}

void free_rtl(rtl_prog* rtl){
  if(rtl){
    free(rtl->fname);
    free_list(rtl->args);
    free_rtl_graph(rtl->graph);
    free(rtl);
  }
}
