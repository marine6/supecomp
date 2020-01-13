#ifndef RTL_GEN_H
#define RTL_GEN_H

#include "rtl.h"
#include "cfg.h"

rtl_prog* rtl_of_cfg_prog(cfg_prog*);
void free_rtl(rtl_prog*);
void free_rtl_ops(list* l);
#endif
