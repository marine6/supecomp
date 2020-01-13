#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdio.h>

typedef struct list {
  void* elt;
  struct list* next;
} list;

list* list_append(list*, void*);
list* cons(void*, list*);
list* concat(list *l1, list* l2);
int list_length(list* l);
void* list_nth(list* l, int n);
list* clear_dup(list* l);

typedef struct pair {
  void* fst;
  void* snd;
} pair;

pair* mkpair(void* a, void* b);

void* some(void* e);

void* assoc_get(list* l, void* k);
void* assoc_set(list* l, void* k, void* v);


list* list_append_int(list* l, int elt);
list* cons_int(int elt, list* l);
int list_nth_int(list* l, int n);
int list_in_int(list* l, int x);
void print_int_list(FILE* f, list* l);
list* int_list_copy(list* l);
list* list_remove_int(list* l, int i);
int list_int_incl(list* l1, list* l2);

list* list_append_string(list* l, char* elt);
list* cons_string(char* elt, list* l);
char* list_nth_string(list* l, int n);
list* list_remove_string(list* l, char* s);
int list_in_string(list* l, char* s);
int list_string_incl(list* l1, list* l2);
void print_string_list(FILE* f, list* l);
list* string_list_copy(list* l);


void free_list(list*);

#endif
