#include <assert.h>
#include <stdlib.h>
#include "elang.h"
#include "elang_gen.h"
#include "cfg.h"
#include "cfg_gen.h"
#include "cfg_value_analysis.h"


expression* asimpl(astate* as, expression* e){
  return e;
}

void constant_propagation_graph(list* value_analysis, cfg* c, cfg_prog* p){
}

cfg_prog* constant_propagation_cfg_prog(cfg_prog* cfg){

  list* value_analysis = value_analysis_cfg_prog(cfg);

  constant_propagation_graph(value_analysis, cfg->graph, cfg);

  cfg->graph = clean_cfg(cfg->graph, cfg->entry);
  return cfg;
}
