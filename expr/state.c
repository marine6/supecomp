#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "state.h"

int string_int_get_val(string_int_state_t* ss, char* v){
  while(ss){
    if(!strcmp(ss->var,v)) return ss->val;
    ss = ss->next;
  }
  printf("Could not find value for variable %s\n", v);
  exit(1);
}

string_int_state_t* string_int_set_val(string_int_state_t* s, char* k, int v){
  string_int_state_t *ss = s;
  while(ss){
    if(!strcmp(ss->var,k)) {
      ss->val = v;
      return s;
    }
    ss = ss->next;
  }
  string_int_state_t* n = (string_int_state_t*) malloc(sizeof(string_int_state_t));
  n->next = s;
  n->var = strdup(k);
  n->val = v;
  return n;
}


void print_string_int_state(string_int_state_t* ss){
  while(ss){
    printf("%s: %d, ", ss->var, ss->val);
    ss = ss->next;
  }
}


void terminate_string_int_state(string_int_state_t* s){
  if(s){
    terminate_string_int_state(s->next);
    free(s->var);
    free(s);
  }
}




int int_int_get_val(int_int_state_t* ss, int v){
  while(ss){
    if(ss->var == v) return ss->val;
    ss = ss->next;
  }
  printf("Could not find value for register %d\n", v);
  exit(1);
}

int_int_state_t* int_int_set_val(int_int_state_t* s, int k, int v){
  int_int_state_t *ss = s;
  while(ss){
    if(ss->var == k) {
      ss->val = v;
      return s;
    }
    ss = ss->next;
  }
  int_int_state_t* n = (int_int_state_t*) malloc(sizeof(int_int_state_t));
  n->next = s;
  n->var = k;
  n->val = v;
  return n;
}


void print_int_int_state(int_int_state_t* ss){
  while(ss){
    printf("r%d: %d, ", ss->var, ss->val);
    ss = ss->next;
  }
}


void terminate_int_int_state(int_int_state_t* s){
  if(s) {
    terminate_int_int_state(s->next);
    free(s);
  }
}

