tokens SYM_EOF SYM_IDENTIFIER SYM_INTEGER SYM_SEMICOLON SYM_IF SYM_ELSE SYM_PLUS SYM_MINUS SYM_ASTERISK SYM_DIV SYM_EQUALITY SYM_ASSIGN SYM_LPARENTHESIS SYM_RPARENTHESIS SYM_LBRACE  SYM_RBRACE  SYM_WHILE SYM_RETURN  SYM_PRINT SYM_COMMA SYM_LT SYM_LEQ  SYM_GT SYM_GEQ SYM_NOTEQ SYM_MOD
non-terminals<void*> S FUNCTION ARGUMENTS ARGUMENT LPARENTHESIS RPARENTHESIS IDENTIFIER INTEGER EXPR TERM TERMS INSTRUCTION INSTRUCTIONS CMP IASSIGN IWHILE IFTHEN IFTHENELSE IELSE IRETURN IPRINT IBLOCK FACTOR FACTORS
rules
S -> FUNCTION SYM_EOF { return $1; }
FUNCTION -> IDENTIFIER LPARENTHESIS ARGUMENTS RPARENTHESIS IBLOCK { return make_node(AST_NODE_FUNDEF, cons(make_node(AST_NODE_FUNBODY, $5), $3)); }
ARGUMENTS -> SYM_COMMA ARGUMENT ARGUMENTS { return make_node(AST_NODE_FUNARGS, cons($2, $3)); }
ARGUMENTS -> { return NULL; }
ARGUMENT -> FACTOR { return $1; }

LPARENTHESIS -> SYM_LPARENTHESIS { return $1; }
RPARENTHESIS -> SYM_RPARENTHESIS { return $1; }
IDENTIFIER -> SYM_IDENTIFIER { return make_string_leaf(strdup($1)); }
INTEGER -> SYM_INTEGER { return make_int_leaf(atoi($1)); }
EXPR -> TERM TERMS SYM_SEMICOLON { return make_node(AST_TERMS, cons($1, $2)); }
TERM -> FACTOR FACTORS { return make_node(AST_FACTORS, cons($1, $2)); }
TERMS -> SYM_PLUS TERM TERMS { return cons(make_node(AST_EADD, NULL), cons($2, $3)); }
TERMS -> SYM_MINUS TERM TERMS { return cons(make_node(AST_ESUB, NULL), cons($2, $3)); }
TERMS -> { return NULL; }
INSTRUCTION -> IASSIGN { return $1; }
INSTRUCTION -> IWHILE { return $1; }
INSTRUCTION -> IFTHENELSE { return $1; }
INSTRUCTION -> IRETURN { return $1; }
INSTRUCTION -> IPRINT { return $1; }
INSTRUCTION -> IBLOCK { return $1; }
INSTRUCTIONS -> INSTRUCTION INSTRUCTIONS { return cons($1, $2); }
INSTRUCTIONS -> { return NULL; }

CMP -> SYM_LT TERM TERM { return make_node(AST_CMPS, cons(make_node(AST_CLT, NULL), cons($2, $3))); }
CMP -> SYM_LEQ TERM TERM { return make_node(AST_CMPS, cons(make_node(AST_CLE, NULL), cons($2, $3))); }
CMP -> SYM_GT TERM TERM { return make_node(AST_CMPS, cons(make_node(AST_CGT, NULL), cons($2, $3))); }
CMP -> SYM_GEQ TERM TERM { return make_node(AST_CMPS, cons(make_node(AST_CGE, NULL), cons($2, $3))); }
CMP -> SYM_EQUALITY TERM TERM { return make_node(AST_CMPS, cons(make_node(AST_CEQ, NULL), cons($2, $3))); }
CMP -> SYM_NOTEQ TERM TERM { return make_node(AST_CMPS, cons(make_node(AST_CNEQ, NULL), cons($2, $3))); }
CMP -> FACTOR { return $1; }

IASSIGN -> IDENTIFIER SYM_EQUALITY EXPR { return make_node(AST_IASSIGN, cons($1, $3)); }
IWHILE -> SYM_WHILE LPARENTHESIS CMP RPARENTHESIS INSTRUCTION { return make_node(AST_IWHILE, cons($3,$5)); }
IFTHEN -> SYM_IF LPARENTHESIS CMP RPARENTHESIS INSTRUCTION { return cons($3,$5); }
IFTHENELSE -> IFTHEN IELSE { return make_node(AST_IIFTHENELSE, cons($1,$2)); }
IELSE -> SYM_ELSE INSTRUCTION { return $2; }
IELSE -> { return NULL; }
IRETURN -> SYM_RETURN EXPR { return make_node(AST_IRETURN, $2); }
IPRINT -> SYM_PRINT EXPR { return make_node(AST_IPRINT, $2); }
IBLOCK -> SYM_LBRACE INSTRUCTIONS SYM_RBRACE { return make_node(AST_IBLOCK, $2); }


FACTOR -> IDENTIFIER { return $1; }
FACTOR -> INTEGER { return $1; }
FACTORS -> SYM_ASTERISK FACTOR FACTORS { return cons(make_node(AST_EMUL, NULL), cons($2, $3)); }
FACTORS -> SYM_DIV FACTOR FACTORS { return cons(make_node(AST_EDIV, NULL), cons($2, $3)); }
FACTORS -> SYM_MOD FACTOR FACTORS { return cons(make_node(AST_EMOD, NULL), cons($2, $3)); }
FACTORS -> { return NULL; }

