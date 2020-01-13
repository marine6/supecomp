#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linear.h"


list* setup_labels(list* ops){
  int pc = 0;
  list* labels = NULL;
  while(ops){
    rtl_op* op = ops->elt;
    if(op->type == RLABEL){
      labels = assoc_set(labels, (void*)(unsigned long)op->label.lab, (void*)(unsigned long)pc);
    }
    ops = ops->next;
    pc = pc + 1;
  }
  return labels;
}

int resolve_label(int lab, list* labels){
  int* n = assoc_get(labels, (void*)(unsigned long)lab);
  if(!n) {
    fprintf(stderr, "Unknown label n%d\n", lab);
    exit(1);
  }
  return *n;
}

list* succs(rtl_op* op, int pc, list* labels){
  switch(op->type){
  case RBRANCH:
    return cons_int(resolve_label(op->branch.succtrue, labels),
                    cons_int(resolve_label (op->branch.succfalse, labels),
                             NULL));
  case RGOTO:
    return cons_int(resolve_label(op->rgoto.succ, labels), NULL);
  case RRET:
    return NULL;
  default:
    return cons_int(pc+1, NULL);
    break;
  }
  return NULL;
}

list* live_before_op(list* live_aft, rtl_op* op){
  return NULL;
}



list* live_after_op(int pc, list* ops, list* labels, list* map){
  rtl_op* op = list_nth(ops, pc);
  list* p = succs(op, pc, labels);
  list* live_aft = NULL;
  while(p){
    list** la = assoc_get(map, p->elt);
    if(la){
      live_aft = clear_dup(concat(live_aft, int_list_copy(*la)));
      free(la);
    }
    p = p -> next;
  }
  return live_aft;
}

int new_changes;

list* liveness_linear_ops(list* map, list* ops){
  list* labels = setup_labels(ops);
  int pc = list_length(ops) - 1;
  while(pc >= 0){
    // Live variables after this node = union of map for all its succs
    rtl_op* op = list_nth(ops, pc);
    list* live_aft = live_after_op(pc, ops, labels, map);
    list* live_bef = clear_dup(live_before_op(live_aft, op));
    list** oldp = (list**)assoc_get(map, (void*)(unsigned long)pc);
    list* old = NULL;
    if(oldp) old = *oldp;
    map = assoc_set(map, (void*)(unsigned long)pc, live_bef);
    new_changes += !list_int_incl(live_bef, old);
    pc--;
  }
  return map;
}

/* Computes the set of live variables *before* each instruction. */
list* liveness_linear_prog(linear_prog* p){
  list* map = NULL;
  do {
    new_changes = 0;
    map = liveness_linear_ops(map, p->ops);
  } while (new_changes);
  return map;
}

void free_liveness(list* map){
  if(map){
    pair* elt = map->elt;
    free_list(elt->snd);
    free(elt);
    free_liveness(map->next);
    free(map);
  }
}
