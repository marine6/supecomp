#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elang.h"
#include "cfg.h"


void print_mapping(FILE* f, list* map){
  while(map){
    pair* elt = map->elt;
    fprintf(f, "n%d: ", (int)(unsigned long)elt->fst);
    print_string_list(f, (list*)elt->snd);
    fprintf(f, "\n");
    map = map->next;
  }
}

list* expr_used_vars(struct expression* e){
    switch (e->etype) {
        case EINT:
            return NULL;
        case EVAR:
            return cons(e->var.s, NULL);
        case EUNOP:
            return expr_used_vars(e->unop.e);
        case EBINOP:
            if (expr_used_vars(e->binop.e1) == NULL) {
                return expr_used_vars(e->binop.e2);
            }
            struct list *l2 = expr_used_vars(e->binop.e1);
            while (l2->next != NULL) {
                l2 = l2->next;
            }
            l2->next = expr_used_vars(e->binop.e2);
            return expr_used_vars(e->binop.e1);
    }
    return NULL;
}


list* live_after(node_t* n, list* map){
  list* live_aft = NULL;
  list *l = live_aft;
  list *succs = succs_node(n);
  while (succs != NULL) {
    list *vars = assoc_get(map, succs->elt);
    while (vars != NULL) {
        l->elt = vars->elt;
        l = l->next;
        vars = vars->next;
    }
  }
  return live_aft;
}

list* live_before(list* live_aft, node_t* n){
  return NULL;
}

int new_changes;

list* liveness_graph(list* map, cfg* c){
  return map;
}

list* liveness_prog(cfg_prog* p){
  list* map = NULL;
  return map;
}
