#ifndef CFG_LIVENESS_H
#define CFG_LIVENESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elang.h"
#include "cfg.h"

void print_mapping(FILE* f, list* map);

list* expr_used_vars(struct expression* e);
list* live_after(node_t* n, list* map);
list* liveness_graph(list** map, cfg* c);

list* liveness_prog(cfg_prog* p);

#endif
