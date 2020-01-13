#include <stdio.h>
#include "ast.h"
void init_ast_tags();
void free_ast_tags();

char* get_tag_name(enum ast_tag i);
void draw_ast(FILE* fd, struct ast_node* ast);
