#include <stdlib.h>
#include "rtl.h"
#include "regalloc.h"
#include "datatypes.h"
#include "linear_liveness.h"
#include "globals.h"

/* Returns a pointer to the location associated with a RTL pseudoregister, if
   any. Return NULL otherwise. */
loc* get_reg_loc(allocation* alloc, int pseudoreg){
  if(alloc){
    if(alloc->pseudoreg == pseudoreg) return &(alloc->loc);
    return get_reg_loc(alloc->next, pseudoreg);
  }
  return NULL;
}

/* Allocates RTL pseudoregister [pseudo] at stack slot [slot], if not already
   associated with something else. */
allocation* allocate_at_stack_slot(allocation* alloc, int slot, int pseudo){
  if(alloc){
    if(alloc->pseudoreg == pseudo) return alloc;
    alloc->next = allocate_at_stack_slot(alloc->next, slot, pseudo);
    return alloc;
  }
  alloc = malloc(sizeof(allocation));
  alloc->next = NULL;
  alloc->pseudoreg = pseudo;
  alloc->loc.type = STACK;
  alloc->loc.stkoffset = slot;
  return alloc;
}

/* Allocates RTL pseudoregister [pseudo] at stack param slot [slot], if not already
   associated with something else. */
allocation* allocate_at_param(allocation* alloc, int slot, int pseudo){
  if(alloc){
    if(alloc->pseudoreg == pseudo) return alloc;
    alloc->next = allocate_at_param(alloc->next, slot, pseudo);
    return alloc;
  }
  alloc = malloc(sizeof(allocation));
  alloc->next = NULL;
  alloc->pseudoreg = pseudo;
  alloc->loc.type = PARAM;
  alloc->loc.paramnum = slot;
  return alloc;
}


/* Allocates RTL pseudoregister [pseudo] at stack slot [slot], if not already
   associated with something else. */
allocation* allocate_at_reg(allocation* alloc, int reg, int pseudo){
  if(alloc){
    if(alloc->pseudoreg == pseudo) return alloc;
    alloc->next = allocate_at_reg(alloc->next, reg, pseudo);
    return alloc;
  }
  alloc = malloc(sizeof(allocation));
  alloc->next = NULL;
  alloc->pseudoreg = pseudo;
  alloc->loc.type = REG;
  alloc->loc.reg = reg;
  return alloc;
}


/* Allocates RTL pseudoregister [pseudo] at next available stack slot.
   [next_stack_slot] is a pointer to the next available stack slot. */
allocation* allocate_at_next_stack_slot(allocation* alloc, int* next_stack_slot, int pseudo){
  if(alloc){
    if(alloc->pseudoreg == pseudo) return alloc;
    alloc->next = allocate_at_next_stack_slot(alloc->next, next_stack_slot, pseudo);
    return alloc;
  }
  alloc = malloc(sizeof(allocation));
  alloc->next = NULL;
  alloc->pseudoreg = pseudo;
  alloc->loc.type = STACK;
  alloc->loc.stkoffset = (*next_stack_slot)++;
  return alloc;
}

/* Allocates all pseudoregisters appearing in RTL operation [n]  */
allocation* regalloc_op(allocation* alloc, int* next_stack_slot, rtl_op* n){
  switch(n->type){
  case RLABEL:
    break;
  case RMOV:
    alloc = allocate_at_next_stack_slot(alloc, next_stack_slot, n->mov.rd);
    alloc = allocate_at_next_stack_slot(alloc, next_stack_slot, n->mov.rs);
    break;
  case RPRINT:
    alloc = allocate_at_next_stack_slot(alloc, next_stack_slot, n->print.rs);
    break;
  case RBINOP:
    alloc = allocate_at_next_stack_slot(alloc, next_stack_slot, n->binop.rd);
    alloc = allocate_at_next_stack_slot(alloc, next_stack_slot, n->binop.rs1);
    alloc = allocate_at_next_stack_slot(alloc, next_stack_slot, n->binop.rs2);
    break;
  case RUNOP:
    alloc = allocate_at_next_stack_slot(alloc, next_stack_slot, n->unop.rd);
    alloc = allocate_at_next_stack_slot(alloc, next_stack_slot, n->unop.rs);
    break;
  case RRET:
    alloc = allocate_at_next_stack_slot(alloc, next_stack_slot, n->ret.rs);
    break;
  case RBRANCH:
    alloc = allocate_at_next_stack_slot(alloc, next_stack_slot, n->branch.rs);
    break;
  case RGOTO:
    break;
  case RIMM:
    alloc = allocate_at_next_stack_slot(alloc, next_stack_slot, n->imm.rd);
    break;
  }
  return alloc;
}

allocation* regalloc_ops(allocation* alloc, int* next_stack_slot, list* ns){
  if(ns){
    alloc = regalloc_op(alloc, next_stack_slot, ns->elt);
    alloc = regalloc_ops(alloc, next_stack_slot, ns->next);
  }
  return alloc;
}

list* regs_of_rtl_op(rtl_op* n){
  switch(n->type){
  case RLABEL: return NULL;
  case RMOV: return cons_int(n->mov.rd, cons_int(n->mov.rs, NULL));
  case RPRINT: return cons_int(n->print.rs, NULL);
  case RBINOP: return cons_int(n->binop.rd,
                               cons_int(n->binop.rs1,
                                        cons_int(n->binop.rs2, NULL)));
  case RUNOP: return cons_int(n->unop.rd, cons_int(n->unop.rs, NULL));
  case RRET: return cons_int(n->ret.rs, NULL);
  case RBRANCH: return cons_int(n->branch.rs, NULL);
  case RGOTO: return NULL;
  case RIMM: return cons_int(n->imm.rd, NULL);
  }
  return NULL;
}

list* regs_of_rtl_ops(list* n){
  if(n){
    return clear_dup(concat(regs_of_rtl_ops(n->next), regs_of_rtl_op(n->elt)));
  }
  return NULL;
}

list* add_interf(int x, int y, list* rig){
  return rig;
}

list* build_interference_graph(linear_prog* p){
  list* rig = NULL;
  // Initialisation du graphe d'interférence. Chaque registre correspond à un
  // sommet dont la liste des voisins est initialement vide.
  list* regs = regs_of_rtl_ops(p->ops);
  while(regs){
    rig = assoc_set(rig, regs->elt, NULL);
    regs = regs->next;
  }
  list* live = liveness_linear_prog(p);
  // Graphe à construire ci-dessous, grâce aux information de liveness [live].

  free_liveness(live);
  return rig;
}

void print_rig(FILE* f, list* rig, allocation* alloc){
  list* colors = NULL;
  colors = cons("lightblue", colors);
  colors = cons("red", colors);
  colors = cons("yellow", colors);
  colors = cons("purple", colors);
  colors = cons("orange", colors);
  colors = cons("pink", colors);
  fprintf(f, "graph rig {\n");
  while(rig){
    pair* p = rig->elt;
    int r = (unsigned long)p->fst;
    loc* lo = get_reg_loc(alloc, r);
    if(lo && lo->type == REG){
      fprintf(f, "n%d [label=\"r%d\" style=filled fillcolor=\"%s\"]\n", r, r, (char*)list_nth(colors, lo->reg%list_length(colors)));
    } else {
      fprintf(f, "n%d [label=\"r%d\"]\n", r, r);
    }
    list* l = p->snd;
    while(l){
      int r2 = (unsigned long)l->elt;
      if(r <= r2)
        fprintf(f, "n%d -- n%d\n", r, r2);
      l = l->next;
    }
    rig = rig->next;
  }
  fprintf(f, "}\n");
}

list* copy_rig(list* rig){
  list* cop = NULL;
  while(rig){
    pair* p = rig->elt;
    void* r = p->fst;
    list* l = p->snd;
    cop = assoc_set(cop, r, int_list_copy(l));
    rig = rig->next;
  }
  return cop;
}


list* remove_from_rig(list*rig, int x){
  if(!rig) return rig;
  pair* p = rig->elt;
  if((unsigned long)p->fst == x)
    return remove_from_rig(rig->next, x);
  p->snd = list_remove_int(p->snd, x);
  rig->next = remove_from_rig(rig->next, x);
  return rig;
}

int* pick_node_with_fewer_than_n_neighbors(list* rig, int n){
  return NULL;
}

int* pick_spilling_candidate(list* rig){
  int* curnode = NULL;
  return curnode;
}

typedef enum regalloc_decision_t { SPILL, NOSPILL } regalloc_decision_t;

list* make_stack(list* rig, int ncolors){
  list* stack = NULL;
  return stack;
}

void print_stack(FILE* f, list* stack){
  while(stack){
    pair* decision = stack->elt;
    regalloc_decision_t dec = (unsigned long)decision->fst;
    int pseudoreg = (unsigned long)decision->snd;
    switch(dec){
    case SPILL:
      fprintf(f, "spill r%d\n", pseudoreg);
      break;
    case NOSPILL:
      fprintf(f, "nospill r%d\n", pseudoreg);
      break;
    }
    stack = stack->next;
  }
}

allocation* make_allocation(allocation* alloc, list* rig, list* stack, int* next_stack_slot, int ncolors){
  return alloc;
}

/* Initialize allocation with arguments at -2, -3, ... Those are to be
   understood as offsets to the frame pointer (ebp in x86, fp in RISC-V) */
allocation* regalloc_prog(linear_prog* p, int* numslots){
  allocation* alloc = NULL;
  int next_stack_slot = 1;
  list* l = p->args;
  int i = 0;
  while(l){
    alloc = allocate_at_param(alloc, i++, (unsigned long)l->elt);
    l = l->next;
  }

  if(clever_allocation){
    list* rig = build_interference_graph(p);
    l = p->args;
    while(l){
      int argreg = (unsigned long)l->elt;
      rig = remove_from_rig(rig, argreg);
      l = l->next;
    }
    list* rigcopy = copy_rig(rig);
    list* stack = make_stack(rig, ncolors);
    alloc = make_allocation(alloc, rigcopy, stack, &next_stack_slot, ncolors);
  } else {
    alloc = regalloc_ops(alloc, &next_stack_slot, p->ops);
  }
  if(numslots) *numslots = next_stack_slot;
  if(print_allocation_flag) print_allocation(stderr, alloc);
  return alloc;
}

void print_location(FILE* f, loc loc){
  switch(loc.type){
  case STACK:
    fprintf(f, "stk(%d)", loc.stkoffset);
    break;
  case PARAM:
    fprintf(f, "param(%d)", loc.paramnum);
    break;
  case REG:
    fprintf(f, "reg(%d)", loc.reg);
    break;
  }
}

void print_allocation(FILE* f, allocation* alloc){
  if(alloc){
    fprintf(f, "r%d -> ", alloc->pseudoreg);
    print_location(f, alloc->loc);
    fprintf(f, "\n");
    print_allocation(f, alloc->next);
  }
}

void free_allocation(allocation* alloc){
  if(alloc){
    free_allocation(alloc->next);
    free(alloc);
  }
}
