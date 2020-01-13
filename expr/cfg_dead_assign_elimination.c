#include "datatypes.h"
#include "elang.h"
#include "elang_print.h"
#include "cfg.h"
#include "cfg_liveness.h"
#include "cfg_gen.h"
#include "globals.h"

int num_changed = 0;
int roundnr = 0;

void dead_assign_elimination_graph(list* live, cfg* c){
}

cfg_prog* dead_assign_elimination_prog(cfg_prog* c){
  return c;
}
