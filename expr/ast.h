#ifndef AST_H
#define AST_H


enum ast_tag {
              AST_STRING,
              AST_NODE_FUNDEF,
              AST_NODE_FUNARGS,
              AST_NODE_FUNBODY,
              AST_INT,
              AST_EADD,
              AST_ESUB,
              AST_EMOD,
              AST_EMUL,
              AST_EDIV,
              AST_ENEG,
              AST_CLT,
              AST_CLE,
              AST_CGT,
              AST_CGE,
              AST_CEQ,
              AST_CNEQ,

              AST_IASSIGN,
              AST_IBLOCK,
              AST_IIFTHENELSE,
              AST_IWHILE,
              AST_IRETURN,
              AST_IPRINT,

              AST_EQS,
              AST_CMPS,
              AST_TERMS,
              AST_FACTORS
};

struct ast_node {
  enum ast_tag tag;
  union {
    struct list* children;
    char* string;
    int integer;
  };
};

struct ast_node* make_node(enum ast_tag, struct list*);
struct ast_node* make_string_leaf(char*);
struct ast_node* make_int_leaf(int);


char* string_of_string_leaf(struct ast_node* ast);
int int_of_int_leaf(struct ast_node* ast);

void free_ast(struct ast_node*);

#endif
