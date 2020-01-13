#ifndef CFG_VALUE_ANALYSIS_H
#define CFG_VALUE_ANALYSIS_H

#include "elang.h"
#include "cfg.h"

typedef enum aval_t { BOT, CST, TOP } aval_t;

typedef struct aval {
  aval_t type;
  int cst;
} aval;


aval* mktop();
aval* mkbot();
aval* mkcst(int c);
aval* aval_copy(aval* a);

typedef struct astate {
  struct astate* next;
  char* var;
  aval* av;
} astate;

aval* aexpr(astate* s, expression* e);
astate* astate_before(cfg_prog* p, int node_id, list* cfg_astate);
list* value_analysis_cfg_prog(cfg_prog* p);


void print_aval(FILE* f, aval* av);

void print_astate(FILE* f, astate* as);

void print_value_analysis_result(FILE* f, list* cfg_astate);


#endif
