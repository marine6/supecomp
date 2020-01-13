#ifndef CFG_GEN_H
#define CFG_GEN_H

#include "elang.h"
#include "cfg.h"

node_t* new_cfg_node();
void free_node(node_t* n);
cfg_prog* cfg_of_e_prog(struct eprog*);
void free_cfg(cfg_prog*);
cfg* clean_cfg(cfg* c, int entry);
#endif
