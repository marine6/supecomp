tokens SYM_EOF SYM_IDENTIFIER SYM_INTEGER SYM_SEMICOLON SYM_IF SYM_ELSE SYM_PLUS SYM_MINUS SYM_ASTERISK SYM_DIV SYM_EQUALITY SYM_ASSIGN SYM_LPARENTHESIS SYM_RPARENTHESIS SYM_LBRACE  SYM_RBRACE  SYM_WHILE SYM_RETURN  SYM_PRINT SYM_COMMA SYM_LT SYM_LEQ  SYM_GT SYM_GEQ SYM_NOTEQ SYM_MOD
non-terminals<struct ast_node*> S ARGUMENT CMPS CMP EXPR TERM INSTRUCTION IASSIGN IWHILE IFTHENELSE IRETURN IPRINT IBLOCK FACTOR IDENTIFIER INTEGER
non-terminals<struct list*> FUNCTION TERMS FACTORS INSTRUCTIONS ARGUMENTS
rules
S -> FUNCTION SYM_EOF { return make_node(AST_NODE_FUNDEF, $1); }
FUNCTION -> IDENTIFIER SYM_LPARENTHESIS ARGUMENTS SYM_RPARENTHESIS IBLOCK { return cons($1, cons(make_node(AST_NODE_FUNARGS, $3), cons(make_node(AST_NODE_FUNBODY, cons($5, NULL)),NULL))); }
ARGUMENTS -> ARGUMENT ARGUMENTS { return cons($1, $2); }
ARGUMENTS -> SYM_COMMA ARGUMENT ARGUMENTS { return cons($2, cons($3,NULL)); }
ARGUMENTS -> { return NULL; }
ARGUMENT -> FACTOR { return $1; }

IDENTIFIER -> SYM_IDENTIFIER { return make_string_leaf(strdup($1)); }
INTEGER -> SYM_INTEGER { return make_int_leaf(atoi($1)); }
EXPR -> CMP CMPS { return make_node(AST_EQS, cons($1, cons($2, NULL))); }
// TERM TERMS { return make_node(AST_TERMS, cons($1, $2)); }
TERM -> FACTOR FACTORS { return make_node(AST_FACTORS, cons($1, $2)); }
TERMS -> SYM_PLUS TERM TERMS { return cons(make_node(AST_EADD, NULL), cons($2, $3)); }
TERMS -> SYM_MINUS TERM TERMS { return cons(make_node(AST_ESUB, NULL), cons($2, $3)); }
TERMS -> { return NULL; }
TERM -> { return NULL; }
INSTRUCTION -> IASSIGN { return $1; }
INSTRUCTION -> IWHILE { return $1; }
INSTRUCTION -> IFTHENELSE { return $1; }
INSTRUCTION -> IRETURN { return $1; }
INSTRUCTION -> IPRINT { return $1; }
INSTRUCTION -> IBLOCK { return $1; }
INSTRUCTIONS -> INSTRUCTION INSTRUCTIONS { return cons($1, $2); }
INSTRUCTIONS -> { return NULL; }

CMPS -> SYM_LT CMP CMPS { return make_node(AST_CMPS, cons(make_node(AST_CLT, NULL), cons($2, cons($3, NULL)))); }
CMPS -> SYM_LEQ CMP CMPS { return make_node(AST_CMPS, cons(make_node(AST_CLE, NULL), cons($2, cons($3, NULL)))); }
CMPS -> SYM_GT CMP CMPS { return make_node(AST_CMPS, cons(make_node(AST_CGT, NULL), cons($2, cons($3, NULL)))); }
CMPS -> SYM_GEQ CMP CMPS { return make_node(AST_CMPS, cons(make_node(AST_CGE, NULL), cons($2, cons($3, NULL)))); }
CMPS -> SYM_EQUALITY CMP CMPS { return make_node(AST_CMPS, cons(make_node(AST_CEQ, NULL), cons($2, cons($3, NULL)))); }
CMPS -> SYM_NOTEQ CMP CMPS { return make_node(AST_CMPS, cons(make_node(AST_CNEQ, NULL), cons($2, cons($3, NULL)))); }
CMPS -> { return NULL; }
CMP -> TERM TERMS { return $1; }

IASSIGN -> IDENTIFIER SYM_ASSIGN EXPR SYM_SEMICOLON { return make_node(AST_IASSIGN, cons($1, cons($3, NULL))); }
IWHILE -> SYM_WHILE SYM_LPARENTHESIS EXPR SYM_RPARENTHESIS INSTRUCTION { return make_node(AST_IWHILE, cons($3, cons($5, NULL))); }
//IFTHEN ->  { return cons($3, cons($5, NULL)); }
IFTHENELSE -> SYM_IF SYM_LPARENTHESIS EXPR SYM_RPARENTHESIS INSTRUCTION { return make_node(AST_IIFTHENELSE, cons($3, cons($5, NULL))); }
IRETURN -> SYM_RETURN EXPR SYM_SEMICOLON { return make_node(AST_IRETURN, cons($2, NULL)); }
IPRINT -> SYM_PRINT EXPR SYM_SEMICOLON { return make_node(AST_IPRINT, cons($2, NULL)); }
IBLOCK -> SYM_LBRACE INSTRUCTIONS SYM_RBRACE { return make_node(AST_IBLOCK, $2); }
IBLOCK -> SYM_ELSE SYM_LBRACE INSTRUCTIONS SYM_RBRACE { return make_node(AST_IBLOCK, $3); }


FACTOR -> IDENTIFIER { return $1; }
FACTOR -> INTEGER { return $1; }
FACTOR -> SYM_LPARENTHESIS EXPR SYM_RPARENTHESIS { return $2; }
FACTORS -> SYM_ASTERISK FACTOR FACTORS { return cons(make_node(AST_EMUL, NULL), cons($2, $3)); }
FACTORS -> SYM_DIV FACTOR FACTORS { return cons(make_node(AST_EDIV, NULL), cons($2, $3)); }
FACTORS -> SYM_MOD FACTOR FACTORS { return cons(make_node(AST_EMOD, NULL), cons($2, $3)); }
FACTORS -> { return NULL; }

