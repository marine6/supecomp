#ifndef RTL_H
#define RTL_H

#include "elang.h"

enum rtl_op_t { RMOV, RPRINT, RBINOP, RUNOP, RRET, RBRANCH, RGOTO, RIMM, RLABEL};

struct rtl_op_mov {
  int rd, rs;
};

struct rtl_op_print {
  int rs;
};

struct rtl_op_return {
  int rs;
};

struct rtl_op_branch {
  int rs, succtrue, succfalse;
};

struct rtl_op_goto {
  int succ;
};

struct rtl_op_binop {
  enum binop_t binop;
  int rd, rs1, rs2;
};

struct rtl_op_unop {
  enum unop_t unop;
  int rd, rs;
};

struct rtl_op_imm {
  int imm, rd;
};

struct rtl_op_label {
  int lab;
};

typedef struct rtl_op {
  enum rtl_op_t type;
  union {
    struct rtl_op_mov    mov;
    struct rtl_op_return ret;
    struct rtl_op_print  print;
    struct rtl_op_branch branch;
    struct rtl_op_goto   rgoto;
    struct rtl_op_binop  binop;
    struct rtl_op_unop   unop;
    struct rtl_op_imm    imm;
    struct rtl_op_label  label;
  };
} rtl_op;

rtl_op* new_rtl_op_mov(int rd, int rs);
rtl_op* new_rtl_op_label(int label);
rtl_op* new_rtl_op_print(int rs);
rtl_op* new_rtl_op_return(int rs);
rtl_op* new_rtl_op_goto(int succ);
rtl_op* new_rtl_op_branch(int rs, int succtrue, int succfalse);
rtl_op* new_rtl_op_binop(binop_t b, int rd, int rs1, int rs2);
rtl_op* new_rtl_op_unop(unop_t u, int rd, int rs);
rtl_op* new_rtl_op_imm(int rd, int imm);

typedef struct rtl {
  struct rtl* next;
  int id;
  list* ops;
} rtl;

typedef struct rtl_prog {
  char* fname;
  struct list* args;
  rtl* graph;
  int entry;
} rtl_prog;



#endif
