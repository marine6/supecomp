#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "datatypes.h"
#include "tree_dump.h"

struct ast_node * make_node(enum ast_tag tag, struct list* l){
  struct ast_node * n = (struct ast_node*)malloc(sizeof(struct ast_node));
  n->tag = tag;
  n->children = l;
  return n;
}

struct ast_node* make_string_leaf(char* s){
  struct ast_node * n = (struct ast_node*)malloc(sizeof(struct ast_node));
  n->tag = AST_STRING;
  n->string = s;
  return n;
}

struct ast_node* make_int_leaf(int i){
  struct ast_node * n = (struct ast_node*)malloc(sizeof(struct ast_node));
  n->tag = AST_INT;
  n->integer = i;
  return n;
}

char* string_of_string_leaf(struct ast_node* ast){
  assert(ast->tag == AST_STRING);
  return strdup(ast->string);
}

int int_of_int_leaf(struct ast_node* ast){
  assert(ast->tag == AST_INT);
  return ast->integer;
}

void free_ast(struct ast_node* ast){
  if(ast){
    if(ast->tag == AST_STRING){
      free(ast->string);
    }
    else if(ast->tag != AST_INT ){
      list* n = ast->children;
      while(n){
        free_ast(n->elt);
        n = n->next;
      }
      free_list(ast->children);
    }
    free(ast);
  }
}
