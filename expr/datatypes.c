#include "datatypes.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

pair* mkpair(void* a, void* b){
  pair *p = (pair*) malloc(sizeof(pair));
  p->fst = a;
  p->snd = b;
  return p;
}

void* some(void* e){
  uintptr_t* p = malloc(sizeof(char*));
  *p = (uintptr_t)e;
  return (void*)p;
}

void* assoc_get(list* l, void* k){
  while(l){
    pair* p = (pair*) l->elt;
    if(p->fst == k){ return some(p->snd); }
    l = l->next;
  }
  return NULL;
}

void* assoc_set(list* l, void* k, void* v){
  list* lsave = l;
  while(l){
    pair* p = (pair*) l->elt;
    if(p->fst == k){
      p->snd = v;
      return lsave;
    }
    l = l->next;
  }
  return cons(mkpair(k,v),lsave);
}

int list_length(list* l){
  int res = 0;
  while(l){
    res++;
    l = l->next;
  }
  return res;
}

list* list_append(list* l, void* elt){
  list* lsave = l;
  if(l == NULL){
    l = (list*)malloc(sizeof(list));
    l->next = NULL;
    l->elt = elt;
    return l;
  } else {
    while(l->next != NULL){ l = l->next; }
    l->next = (list*)malloc(sizeof(list));
    l->next->next = NULL;
    l->next->elt = elt;
    return lsave;
  }
}

list* concat(list *l1, list* l2){
  if(!l1) return l2;
  list* l = l1;
  while(l->next) l = l->next;
  l->next = l2;
  return l1;
}

list* cons(void* elt, list* l){
  list* node = (list*)malloc(sizeof(list));
  node->elt = elt;
  node->next = l;
  return node;
}

int list_in_int(list* l, int x){
  if(!l) return 0;
  if((unsigned long)l->elt == x) return 1;
  return list_in_int(l->next, x);
}

void* list_nth(list* l, int n){
  assert(list_length(l) > n);
  while(n-- > 0){
    l = l->next;
  }
  return l->elt;
}

list* list_append_int(list* l, int elt){
  return list_append(l, (void*)(unsigned long)elt);
}

list* cons_int(int elt, list* l){
  return cons((void*)(unsigned long)elt, l);
}

int list_nth_int(list* l, int n){
  return (unsigned long)list_nth(l,n);
}

list* list_append_string(list* l, char* elt){
  return list_append(l, (char*)elt);
}

list* cons_string(char* elt, list* l){
  return cons((char*)elt, l);
}

char* list_nth_string(list* l, int n){
  return (char*)list_nth(l,n);
}

void free_list(list* l){
  if(!l) return;
  free_list(l->next);
  free(l);
}


list* int_list_copy(list* l){
  list* n = NULL;
  while(l){
    n = list_append(n, l->elt);
    l = l->next;
  }
  return n;
}


list* string_list_copy(list* l){
  list* n = NULL;
  while(l){
    n = list_append(n, strdup(l->elt));
    l = l->next;
  }
  return n;
}

list* list_remove_int(list* l, int s){
  if(l){
    if((unsigned long)l->elt == s) return list_remove_int(l->next, s);
    return cons(l->elt, list_remove_int(l->next,s));
  }
  return l;
}

list* list_remove_string(list* l, char* s){
  if(l){
    if(!strcmp(l->elt,s)) return list_remove_string(l->next, s);
    return cons(l->elt, list_remove_string(l->next,s));
  }
  return l;
}

int list_in_string(list* l, char* s){
  if(l){
    if(!strcmp(l->elt,s)) return 1;
    return list_in_string(l->next, s);
  }
  return 0;
}

int list_string_incl(list* l1, list* l2){
  if(l1){
    if(list_in_string(l2, l1->elt))
      return list_string_incl(l1->next, l2);
    return 0;
  }
  return 1;
}

int list_int_incl(list* l1, list* l2){
  if(l1){
    if(list_in_int(l2, (unsigned long)l1->elt))
      return list_int_incl(l1->next, l2);
    return 0;
  }
  return 1;
}


void print_int_list(FILE* f, list* l){
  fprintf(f,"[");
  while(l){
    fprintf(f, "%d", (int)(unsigned long)l->elt);
    l = l->next;
    if(l) fprintf(f, ", ");
  }
  fprintf(f,"]");
}


void print_string_list(FILE* f, list* l){
  fprintf(f,"[");
  while(l){
    fprintf(f, "%s", (char*)l->elt);
    l = l->next;
    if(l) fprintf(f, ", ");
  }
  fprintf(f,"]");
}

list* clear_dup(list* l){
  if(!l) return l;
  if(list_in_int(l->next, (unsigned long)l->elt))
    return clear_dup(l->next);
  l->next = clear_dup(l->next);
  return l;
}
