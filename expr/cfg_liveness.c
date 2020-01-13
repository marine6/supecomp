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
 return NULL;
}


list* live_after(node_t* n, list* map){
  list* live_aft = NULL;
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
