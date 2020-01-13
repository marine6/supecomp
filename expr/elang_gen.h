#include "elang.h"
#include "ast.h"
struct expression* make_expr_int(int);
struct eprog* make_eprog(struct ast_node* ast);
struct expression* copy_expression(struct expression*);
void free_expression(struct expression* e);
