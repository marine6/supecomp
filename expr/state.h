#ifndef STATE_H
#define STATE_H

typedef struct string_int_state_t {
  struct string_int_state_t* next;
  char* var;
  int val;
} string_int_state_t;

typedef struct int_int_state_t {
  struct int_int_state_t* next;
  int var;
  int val;
} int_int_state_t;

int string_int_get_val(string_int_state_t*, char* v);
string_int_state_t* string_int_set_val(string_int_state_t* s, char* k, int v);
void print_string_int_state(string_int_state_t*);
void terminate_string_int_state(string_int_state_t*);

int int_int_get_val(int_int_state_t* s, int v);
int_int_state_t* int_int_set_val(int_int_state_t* s, int k, int v);
void print_int_int_state(int_int_state_t* s);
void terminate_int_int_state(int_int_state_t* s);

#endif
