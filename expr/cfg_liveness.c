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
    list *live_before = NULL;
    char *to_exclude = NULL;
    switch (n->type) {
        case NODE_ASSIGN:
            live_before = expr_used_vars(n->assign.e);
            to_exclude = n->assign.var;
            break;
        case NODE_COND:
            live_before = expr_used_vars(n->cond.cond);
            break;
        case NODE_PRINT:
            live_before = expr_used_vars(n->print.e);
            break;
        case NODE_RETURN:
            live_before = expr_used_vars(n->ret.e);
            break;
        case NODE_GOTO:
            live_before = live_aft;
            return live_before;
        default:
            return NULL;

    }
    list *temp_list = live_aft;
    // Adding the elements in live_before excluding the dead ones
    while (temp_list) {
        if ((!list_in_string(live_before, temp_list->elt)) &&
            (temp_list->elt != to_exclude)) {
            live_before = list_append_string(live_before, temp_list->elt);
        }
        temp_list = temp_list->next;
    }
    return live_before;
}

int new_changes;

list* liveness_graph(list* map, cfg* c){
    // Keep bool to see if there are new variables alive
    int new_changes = 0;
    list *l_map = map;

    // Parsing nodes in ascending order
    cfg *l_c = c;
    while (l_c) {
        list **temp_assoc_get = assoc_get(map, (void *) (unsigned long) l_c->id);
        list *l_live_before = NULL;

        if (temp_assoc_get != NULL) {
            l_live_before = *temp_assoc_get;
        }

        list *live_bef2 = live_before(live_after(l_c->node, map), l_c->node);

        new_changes = new_changes || (1 - list_string_incl(live_bef2, l_live_before));

        l_map = assoc_set(l_map, (void *) (unsigned long) l_c->id, live_bef2);
        l_c = l_c->next;
    }
    return l_map;
}

list* liveness_prog(cfg_prog* p){
    list *map = NULL;
    new_changes = 1;
    while (new_changes) {
        map = liveness_graph(map, p->graph);
        print_mapping(stdout,map);
    }
    return map;
}
