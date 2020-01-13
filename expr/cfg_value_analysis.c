#include <stdlib.h>
#include <string.h>
#include "elang.h"
#include "elang_run.h"
#include "cfg.h"
#include "cfg_value_analysis.h"


void print_aval(FILE* f, aval* av){
  switch(av->type){
  case TOP: fprintf(f, "top"); break;
  case BOT: fprintf(f, "bot"); break;
  case CST: fprintf(f, "%d", av->cst); break;
  default: fprintf(f, "???"); break;
  }
}

void print_astate(FILE* f, astate* as){
  while(as){
    fprintf(f, "%s: ", as->var);
    print_aval(f, as->av);
    as = as->next;
    if(as) fprintf(f, ", ");
  }
}

void print_value_analysis_result(FILE* f, list* cfg_astate){
  while(cfg_astate){
    pair* p = cfg_astate->elt;
    int nid = (unsigned long)p->fst;
    astate* as = (astate*)p->snd;
    fprintf(f, "n%d: ", nid);
    print_astate(f, as);
    fprintf(f, "\n");
    cfg_astate = cfg_astate->next;
  }
}

aval* mktop(){
  aval* res = malloc(sizeof(aval));
  res->type = TOP;
  return res;
}

aval* mkbot(){
  aval* res = malloc(sizeof(aval));
  res->type = BOT;
  return res;
}

aval* mkcst(int c){
  aval* res = malloc(sizeof(aval));
  res->type = CST;
  res->cst = c;
  return res;
}

aval* aval_copy(aval* a){
  aval* res = malloc(sizeof(aval));
  res->type = a->type;
  res->cst = a->cst;
  return res;
}

aval* aunop(unop_t u, aval* a){
  switch(a->type){
  case BOT: return mkbot();
  case TOP: return mktop();
  case CST: return mkcst(run_unop(u, a->cst));
  }
  return NULL;
}

aval* abinop(binop_t b, aval* a1, aval* a2){
  switch(a1->type){
  case BOT: return mkbot();
  case TOP: return mktop();
  case CST:
    switch(a2->type){
    case BOT: return mkbot();
    case TOP: return mktop();
    case CST: return mkcst(run_binop(b, a1->cst, a2->cst));
    }
  }
  return NULL;
}

aval* astate_lookup(astate* s, char* var){
  if(!s){
    return mkbot();
  }
  if(!strcmp(s->var, var)) return s->av;
  return astate_lookup(s->next, var);
}

aval* aexpr(astate* s, expression* e){
  return NULL;
}

list* preds_aux(cfg* c, int node_id, list* aux){
  if(!c) return aux;
  if(list_in_int(succs_node(c->node), node_id))
    return preds_aux(c->next, node_id, cons_int(c->id, aux));
  return preds_aux(c->next, node_id, aux);
}

list* preds(cfg* c, int node_id){
  return preds_aux(c, node_id, NULL);
}

astate* astate_set(astate* s, char* var, aval* av){
  if(!s){
    astate* as = malloc(sizeof(astate));
    as->next = NULL;
    as->var = var;
    as->av = av;
    return as;
  }
  //  printf("astate_set (*s)->var = '%s'\n", s->var);
  if(!strcmp(s->var, var)){
    s->av = av;
    return s;
  } else {
    s->next = astate_set(s->next, var, av);
    return s;
  }
}

aval* meet_aval(aval* a1, aval* a2){
  return NULL;
}

astate* meet(astate* a1, astate* a2){
  astate* res = NULL;
  return res;
}

astate* astate_before(cfg_prog* p, int node_id, list* cfg_astate){
  astate* res = NULL;
 return res;
}

int more_precise_aval(aval* a1, aval* a2){
  return (a1->type != a2->type);
}

int more_precise(astate* a1, astate* a2){
  if(!a1) return 0;
  aval* av2 = astate_lookup(a2, a1->var);
  if(more_precise_aval(a1->av, av2)) return 1;
  return more_precise(a1->next, a2);
}

int num_changes = 0;

list* acfg(list* cfg_astate, cfg_prog* p){
  return cfg_astate;
}

list* value_analysis_cfg_prog(cfg_prog* p){
  list* cfg_astate = NULL;
  return cfg_astate;
}
