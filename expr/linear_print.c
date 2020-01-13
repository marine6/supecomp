#include <stdio.h>
#include <stdlib.h>

#include "rtl_print.h"
#include "linear_print.h"
#include "linear_liveness.h"

void print_linear_ops(FILE* fd, int pc, list* ns, list* liveness){
  if (ns){
    print_rtl_op(fd, ns->elt);
    fprintf(fd, " # Live before : ");
    list** live_befp = assoc_get(liveness, (void*)(unsigned long)pc);
    list* live_bef = live_befp ? *live_befp : NULL;
    print_int_list(fd, live_bef);
    fprintf(fd, "\n");
    print_linear_ops(fd, pc+1, ns->next, liveness);
  }
}

void print_linear_prog(FILE* f, linear_prog* lin){
  list* liveness = liveness_linear_prog(lin);
  fprintf(f, "%s(", lin->fname);
  list* l = lin->args;
  while(l){
    fprintf(f, "r%d", (int)(unsigned long)l->elt);
    l = l->next;
    if(l)
      fprintf(f, ", ");
  }
  fprintf(f, "):\n");
  list* ops = lin->ops;
  print_linear_ops(f, 0, ops, liveness);
}
