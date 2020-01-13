#ifndef CFG_H
#define CFG_H

#include "elang.h"

enum nodetype { NODE_ASSIGN, NODE_PRINT, NODE_RETURN, NODE_COND, NODE_GOTO };

struct node_assign {
  char* var;
  struct expression* e;
  int succ;
};

struct node_print {
  struct expression* e;
  int succ;
};

struct node_return {
  struct expression* e;
};

struct node_cond {
  struct expression* cond;
  int succ1, succ2;
};

typedef struct node_t {
  enum nodetype type;
  union {
    struct node_assign assign;
    struct node_print print;
    struct node_return ret;
    struct node_cond cond;
    int goto_succ;
  };
} node_t;

typedef struct cfg {
  struct cfg* next;
  int id;
  node_t* node;
} cfg;

typedef struct cfg_prog {
  char* fname;
  struct list* args;
  cfg* graph;
  int entry;
} cfg_prog;

node_t* get_cfg_node(cfg*, int);
list* succs_node(node_t*);
#endif
