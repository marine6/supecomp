#include "cfg.h"
#include "cfg_gen.h"
#include "cfg_liveness.h"
#include "datatypes.h"
#include "elang.h"
#include "elang_print.h"
#include "globals.h"

int num_changed = 0;
int roundnr = 0;

void dead_assign_elimination_graph(list* live, cfg* c) {
    cfg* temp_c = c;

    // going through nodes
    while (temp_c) {
        // Finding assign nodes
        if (temp_c->node->type == NODE_ASSIGN) {
            // Getting alive variables after node
            list* list_temp = live_after(temp_c->node, live);
            // printf("Alive variables after node :");
            // print_string_list(stdout,list_temp);

            // Comparing assigned variables to alive aft variables
            if (!list_in_string(list_temp, temp_c->node->assign.var)) {
                // If the variable is dead, we skip this node (make it a GOTO)
                temp_c->node->type = NODE_GOTO;
                temp_c->node->goto_succ = temp_c->next->id;
                num_changed++;
                // printf("Killing node number %d\n",temp_c->id);
            }
        }
        temp_c = temp_c->next;
    }
}

cfg_prog* dead_assign_elimination_prog(cfg_prog* c) {
    do {
        roundnr++;
        num_changed = 0;
        list *map = liveness_prog(c);
        dead_assign_elimination_graph(map, c->graph);
    } while (num_changed != 0);
    return c;
}
