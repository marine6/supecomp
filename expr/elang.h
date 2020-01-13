#ifndef ELANG_H
#define ELANG_H

#include <stdio.h>
#include "datatypes.h"
#include "ast.h"

/* Types */

enum type {
           TVOID,
           TUINT64,
           TPTR
};

enum type make_type(unsigned int);

/* Comparaisons */

typedef enum binop_t {
              EADD ,
              ESUB ,
              EMUL ,
              EDIV ,
              EMOD,
              CEQ,
              CNEQ,
              CLT,
              CLE,
              CGT,
              CGE
} binop_t;

typedef enum unop_t {
             ENEG
} unop_t;

/* Expressions */
typedef enum expr_t {
             EINT ,
             EVAR ,
             EUNOP ,
             EBINOP
} expr_t;


struct expression;

struct expr_unop {
  enum unop_t unop;
  struct expression* e;
};

struct expr_int {
  int i;
};

struct expr_binop {
  enum binop_t binop;
  struct expression *e1, *e2;
};

struct expr_var {
  char* s;
};

typedef struct expression {
  enum expr_t etype;
  union {
    struct expr_unop unop;
    struct expr_int eint;
    struct expr_binop binop;
    struct expr_var var;
  };
} expression;

enum instr_t {
              IIFTHENELSE,
              IWHILE,
              IASSIGN,
              IRETURN,
              IPRINT,
              IBLOCK
};

struct instruction;

struct instr_if {
  struct expression* cmp;
  struct instruction *ithen, *ielse;
};

struct instr_while {
  struct expression* cmp;
  struct instruction *i;
};

struct instr_assign {
  char* var;
  struct expression* e;
};

struct instr_return {
  struct expression* e;
};

struct instr_print {
  struct expression* e;
};

struct instr_block {
  list* l;
};

struct instruction {
  enum instr_t type;
  union {
    struct instr_if iif;
    struct instr_while iwhile;
    struct instr_assign iassign;
    struct instr_return ireturn;
    struct instr_print iprint;
    struct instr_block iblock;
  };
};

struct eprog {
  char* fname;
  list* args;
  struct instruction* body;
};

struct eprog* make_eprog(struct ast_node* ast);

void free_eprog(struct eprog*);

#endif
