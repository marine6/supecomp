tokens SYM_EOF SYM_IDENTIFIER SYM_INTEGER SYM_SEMICOLON SYM_IF SYM_ELSE SYM_PLUS SYM_MINUS SYM_ASTERISK SYM_DIV SYM_EQUALITY SYM_ASSIGN SYM_LPARENTHESIS SYM_RPARENTHESIS SYM_LBRACE SYM_RBRACE SYM_WHILE SYM_RETURN SYM_COMMA SYM_LT SYM_LEQ SYM_GT SYM_GEQ SYM_NOTEQ SYM_MOD SYM_PRINT
non-terminals<void*> S FUN_ARGS ARG ARGS START_STATEMENTS STATEMENT STATEMENTS ELSE_STATEMENT EQ EQS EXPR TERM TERMS FACTOR FACTORS
rules
S -> SYM_IDENTIFIER SYM_LPARENTHESIS FUN_ARGS SYM_RPARENTHESIS SYM_LBRACE START_STATEMENTS SYM_RBRACE SYM_EOF
{ return make_node(
    AST_NODE_FUNDEF,
    cons(
        make_string_leaf(strdup($1)),
        cons(
		make_node(
            		AST_NODE_FUNARGS,
            		$3
        	),
        	cons(make_node(
             		AST_NODE_FUNBODY,
             		cons($6, NULL)
        	), NULL)
	)
    )
); }

FUN_ARGS -> { return NULL; }
FUN_ARGS -> SYM_IDENTIFIER ARGS { return cons(make_string_leaf(strdup($1)), $2); }
ARGS -> { return NULL; }
ARGS -> SYM_COMMA ARG ARGS { return cons(make_string_leaf(strdup($2)), $3); }
ARG -> SYM_IDENTIFIER { return $1; }

START_STATEMENTS -> STATEMENTS { return make_node(AST_IBLOCK, $1); }
STATEMENTS -> { return NULL; }
STATEMENTS -> STATEMENT STATEMENTS { return cons($1, $2); }

STATEMENT -> SYM_IDENTIFIER SYM_ASSIGN EXPR SYM_SEMICOLON
{ return make_node(AST_IASSIGN, cons(make_string_leaf(strdup($1)),
	cons($3, NULL)));
}
STATEMENT -> SYM_IF SYM_LPARENTHESIS EXPR SYM_RPARENTHESIS SYM_LBRACE START_STATEMENTS SYM_RBRACE ELSE_STATEMENT
{ return make_node(AST_IIFTHENELSE, cons($3, cons($6, cons($8, NULL))));
}
STATEMENT -> SYM_WHILE SYM_LPARENTHESIS EXPR SYM_RPARENTHESIS SYM_LBRACE START_STATEMENTS SYM_RBRACE
{ return make_node(AST_IWHILE, cons($3, cons($6, NULL))); }
STATEMENT -> SYM_PRINT EXPR SYM_SEMICOLON
{ return make_node(AST_IPRINT, cons($2, NULL)); }
STATEMENT -> SYM_RETURN EXPR SYM_SEMICOLON
{ return make_node(AST_IRETURN, cons($2, NULL)); }

ELSE_STATEMENT -> SYM_ELSE SYM_LBRACE START_STATEMENTS SYM_RBRACE { return $3; }
ELSE_STATEMENT -> { return make_node(AST_IBLOCK, NULL); }

EXPR -> EQ EQS { return make_node(AST_EQS, cons($1, $2)); }

EQ -> TERM TERMS { return make_node(AST_TERMS, cons($1, $2)); }
EQS -> SYM_EQUALITY EQ EQS { return cons(make_node(AST_CEQ, NULL), cons($2, $3)); }
EQS -> SYM_LT EQ EQS { return cons(make_node(AST_CLT, NULL), cons($2, $3)); }
EQS -> SYM_LEQ EQ EQS { return cons(make_node(AST_CLE, NULL), cons($2, $3)); }
EQS -> SYM_GT EQ EQS { return cons(make_node(AST_CGT, NULL), cons($2, $3)); }
EQS -> SYM_GEQ EQ EQS { return cons(make_node(AST_CGE, NULL), cons($2, $3)); }
EQS -> SYM_NOTEQ EQ EQS { return cons(make_node(AST_CNEQ, NULL), cons($2, $3)); }
EQS -> { return NULL; }
TERM -> FACTOR FACTORS { return make_node(AST_FACTORS, cons($1, $2)); }
TERMS -> SYM_PLUS TERM TERMS { return cons(make_node(AST_EADD, NULL), cons($2, $3)); }
TERMS -> SYM_MINUS TERM TERMS { return cons(make_node(AST_ESUB, NULL), cons($2, $3)); }
TERMS -> SYM_MOD TERM TERMS { return cons(make_node(AST_EMOD, NULL), cons($2, $3)); }
TERMS -> { return NULL; }
FACTOR -> SYM_LPARENTHESIS EXPR SYM_RPARENTHESIS { return $2; }
FACTOR -> SYM_IDENTIFIER { return make_string_leaf(strdup($1)); }
FACTOR -> SYM_INTEGER { return make_int_leaf(atoi($1)); }
FACTOR -> SYM_MINUS FACTOR { return make_node(AST_ENEG, cons($2, NULL)); }
FACTORS -> SYM_ASTERISK FACTOR FACTORS { return cons(make_node(AST_EMUL, NULL), cons($2, $3)); }
FACTORS -> SYM_DIV FACTOR FACTORS { return cons(make_node(AST_EDIV, NULL), cons($2, $3)); }
FACTORS -> { return NULL; }
