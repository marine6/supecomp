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
            return  concat(expr_used_vars(e->binop.e1),expr_used_vars(e->binop.e2));
    }
    return NULL;
}


list* live_after(node_t* n, list* map){
    list *live_aft = NULL;
    list *succesors = succs_node(n);
    list *temp_list = map;
    while (temp_list) {
        pair *temp_pair = temp_list->elt;
        if (list_in_int(succesors, (int)(unsigned long)temp_pair->fst)) {
            list *temp_temp_list = temp_pair->snd;
            while (temp_temp_list) {
                if (!list_in_string(live_aft, temp_temp_list->elt)) {
                    live_aft =
                            list_append_string(live_aft, temp_temp_list->elt);
                }
                temp_temp_list = temp_temp_list->next;
            }
        }
        temp_list = temp_list->next;
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

list *liveness_graph(list *map, cfg *c) {
    new_changes = 0;
    list *new_map = map;

    // Parsing nodes in ascending order
    cfg *temp_c = c;
    while (temp_c) {
        // List of alive variables before temp_c->id in_k
        list **temp_assoc_get = assoc_get(map, (void *) (unsigned long) temp_c->id);
        list *live_bef = NULL;

        if (temp_assoc_get != NULL) {
            live_bef = *temp_assoc_get;
        }

        // Next iteration of alive variables
        list *live_bef2 =
                live_before(live_after(temp_c->node, map), temp_c->node);

        // Changes ?
        new_changes = new_changes || (1 - list_string_incl(live_bef2, live_bef));

        // Update map
        new_map = assoc_set(new_map, (void *) (unsigned long) temp_c->id, live_bef2);
        temp_c = temp_c->next;
    }

    return new_map;
}

list *liveness_prog(cfg_prog *p) {
    list *map = NULL;
    new_changes = 1;
    while (new_changes) {
        map = liveness_graph(map, p->graph);
        // print_mapping(stdout,map);
    }
    return map;
}
