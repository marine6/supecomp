#include "expr_parser.h"
#include "parser.h"
#include "lexer.h"
#include "datatypes.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void* parse_S(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    char* p1 = eat(lex, SYM_IDENTIFIER);
    eat(lex, SYM_LPARENTHESIS);
    void* p3 = parse_FUN_ARGS(lex);
    eat(lex, SYM_RPARENTHESIS);
    eat(lex, SYM_LBRACE);
    void* p6 = parse_START_STATEMENTS(lex);
    eat(lex, SYM_RBRACE);
    eat(lex, SYM_EOF);

     return make_node(
    AST_NODE_FUNDEF,
    cons(
        make_string_leaf(strdup(p1)),
        cons(
		make_node(
            		AST_NODE_FUNARGS,
            		p3
        	),
        	cons(make_node(
             		AST_NODE_FUNBODY,
             		cons(p6, NULL)
        	), NULL)
	)
    )
); 
}
  syntax_error_message(lex, "error while parsing S");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_FUN_ARGS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    char* p1 = eat(lex, SYM_IDENTIFIER);
    void* p2 = parse_ARGS(lex);

     return cons(make_string_leaf(strdup(p1)), p2); 
}
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){

     return NULL; 
}
  syntax_error_message(lex, "error while parsing FUN_ARGS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_RPARENTHESIS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_ARG(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    char* p1 = eat(lex, SYM_IDENTIFIER);

     return p1; 
}
  syntax_error_message(lex, "error while parsing ARG");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_ARGS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_COMMA){
    eat(lex, SYM_COMMA);
    void* p2 = parse_ARG(lex);
    void* p3 = parse_ARGS(lex);

     return cons(make_string_leaf(strdup(p2)), p3); 
}
  syntax_error_message(lex, "error while parsing ARGS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_RPARENTHESIS));
  printf(", %s", string_of_token(SYM_COMMA));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_START_STATEMENTS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    void* p1 = parse_STATEMENTS(lex);

     return make_node(AST_IBLOCK, p1); 
}
  if(lex->symbol.tag ==  SYM_IF){
    void* p1 = parse_STATEMENTS(lex);

     return make_node(AST_IBLOCK, p1); 
}
  if(lex->symbol.tag ==  SYM_RBRACE){
    void* p1 = parse_STATEMENTS(lex);

     return make_node(AST_IBLOCK, p1); 
}
  if(lex->symbol.tag ==  SYM_WHILE){
    void* p1 = parse_STATEMENTS(lex);

     return make_node(AST_IBLOCK, p1); 
}
  if(lex->symbol.tag ==  SYM_RETURN){
    void* p1 = parse_STATEMENTS(lex);

     return make_node(AST_IBLOCK, p1); 
}
  if(lex->symbol.tag ==  SYM_PRINT){
    void* p1 = parse_STATEMENTS(lex);

     return make_node(AST_IBLOCK, p1); 
}
  syntax_error_message(lex, "error while parsing START_STATEMENTS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_IF));
  printf(", %s", string_of_token(SYM_RBRACE));
  printf(", %s", string_of_token(SYM_WHILE));
  printf(", %s", string_of_token(SYM_RETURN));
  printf(", %s", string_of_token(SYM_PRINT));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_STATEMENT(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    char* p1 = eat(lex, SYM_IDENTIFIER);
    eat(lex, SYM_ASSIGN);
    void* p3 = parse_EXPR(lex);
    eat(lex, SYM_SEMICOLON);

     return make_node(AST_IASSIGN, cons(make_string_leaf(strdup(p1)),
	cons(p3, NULL)));

}
  if(lex->symbol.tag ==  SYM_IF){
    eat(lex, SYM_IF);
    eat(lex, SYM_LPARENTHESIS);
    void* p3 = parse_EXPR(lex);
    eat(lex, SYM_RPARENTHESIS);
    eat(lex, SYM_LBRACE);
    void* p6 = parse_START_STATEMENTS(lex);
    eat(lex, SYM_RBRACE);
    void* p8 = parse_ELSE_STATEMENT(lex);

     return make_node(AST_IIFTHENELSE, cons(p3, cons(p6, cons(p8, NULL))));

}
  if(lex->symbol.tag ==  SYM_WHILE){
    eat(lex, SYM_WHILE);
    eat(lex, SYM_LPARENTHESIS);
    void* p3 = parse_EXPR(lex);
    eat(lex, SYM_RPARENTHESIS);
    eat(lex, SYM_LBRACE);
    void* p6 = parse_START_STATEMENTS(lex);
    eat(lex, SYM_RBRACE);

     return make_node(AST_IWHILE, cons(p3, cons(p6, NULL))); 
}
  if(lex->symbol.tag ==  SYM_RETURN){
    eat(lex, SYM_RETURN);
    void* p2 = parse_EXPR(lex);
    eat(lex, SYM_SEMICOLON);

     return make_node(AST_IRETURN, cons(p2, NULL)); 
}
  if(lex->symbol.tag ==  SYM_PRINT){
    eat(lex, SYM_PRINT);
    void* p2 = parse_EXPR(lex);
    eat(lex, SYM_SEMICOLON);

     return make_node(AST_IPRINT, cons(p2, NULL)); 
}
  syntax_error_message(lex, "error while parsing STATEMENT");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_IF));
  printf(", %s", string_of_token(SYM_WHILE));
  printf(", %s", string_of_token(SYM_RETURN));
  printf(", %s", string_of_token(SYM_PRINT));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_STATEMENTS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    void* p1 = parse_STATEMENT(lex);
    void* p2 = parse_STATEMENTS(lex);

     return cons(p1, p2); 
}
  if(lex->symbol.tag ==  SYM_IF){
    void* p1 = parse_STATEMENT(lex);
    void* p2 = parse_STATEMENTS(lex);

     return cons(p1, p2); 
}
  if(lex->symbol.tag ==  SYM_RBRACE){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_WHILE){
    void* p1 = parse_STATEMENT(lex);
    void* p2 = parse_STATEMENTS(lex);

     return cons(p1, p2); 
}
  if(lex->symbol.tag ==  SYM_RETURN){
    void* p1 = parse_STATEMENT(lex);
    void* p2 = parse_STATEMENTS(lex);

     return cons(p1, p2); 
}
  if(lex->symbol.tag ==  SYM_PRINT){
    void* p1 = parse_STATEMENT(lex);
    void* p2 = parse_STATEMENTS(lex);

     return cons(p1, p2); 
}
  syntax_error_message(lex, "error while parsing STATEMENTS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_IF));
  printf(", %s", string_of_token(SYM_RBRACE));
  printf(", %s", string_of_token(SYM_WHILE));
  printf(", %s", string_of_token(SYM_RETURN));
  printf(", %s", string_of_token(SYM_PRINT));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_ELSE_STATEMENT(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){

     return make_node(AST_IBLOCK, NULL); 
}
  if(lex->symbol.tag ==  SYM_IF){

     return make_node(AST_IBLOCK, NULL); 
}
  if(lex->symbol.tag ==  SYM_ELSE){
    eat(lex, SYM_ELSE);
    eat(lex, SYM_LBRACE);
    void* p3 = parse_START_STATEMENTS(lex);
    eat(lex, SYM_RBRACE);

     return p3; 
}
  if(lex->symbol.tag ==  SYM_RBRACE){

     return make_node(AST_IBLOCK, NULL); 
}
  if(lex->symbol.tag ==  SYM_WHILE){

     return make_node(AST_IBLOCK, NULL); 
}
  if(lex->symbol.tag ==  SYM_RETURN){

     return make_node(AST_IBLOCK, NULL); 
}
  if(lex->symbol.tag ==  SYM_PRINT){

     return make_node(AST_IBLOCK, NULL); 
}
  syntax_error_message(lex, "error while parsing ELSE_STATEMENT");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_IF));
  printf(", %s", string_of_token(SYM_ELSE));
  printf(", %s", string_of_token(SYM_RBRACE));
  printf(", %s", string_of_token(SYM_WHILE));
  printf(", %s", string_of_token(SYM_RETURN));
  printf(", %s", string_of_token(SYM_PRINT));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_EQ(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    void* p1 = parse_TERM(lex);
    void* p2 = parse_TERMS(lex);

     return make_node(AST_TERMS, cons(p1, p2)); 
}
  if(lex->symbol.tag ==  SYM_INTEGER){
    void* p1 = parse_TERM(lex);
    void* p2 = parse_TERMS(lex);

     return make_node(AST_TERMS, cons(p1, p2)); 
}
  if(lex->symbol.tag ==  SYM_MINUS){
    void* p1 = parse_TERM(lex);
    void* p2 = parse_TERMS(lex);

     return make_node(AST_TERMS, cons(p1, p2)); 
}
  if(lex->symbol.tag ==  SYM_LPARENTHESIS){
    void* p1 = parse_TERM(lex);
    void* p2 = parse_TERMS(lex);

     return make_node(AST_TERMS, cons(p1, p2)); 
}
  syntax_error_message(lex, "error while parsing EQ");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf(", %s", string_of_token(SYM_MINUS));
  printf(", %s", string_of_token(SYM_LPARENTHESIS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_EQS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_SEMICOLON){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_EQUALITY){
    eat(lex, SYM_EQUALITY);
    void* p2 = parse_EQ(lex);
    void* p3 = parse_EQS(lex);

     return cons(make_node(AST_CEQ, NULL), cons(p2, p3)); 
}
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_LT){
    eat(lex, SYM_LT);
    void* p2 = parse_EQ(lex);
    void* p3 = parse_EQS(lex);

     return cons(make_node(AST_CLT, NULL), cons(p2, p3)); 
}
  if(lex->symbol.tag ==  SYM_LEQ){
    eat(lex, SYM_LEQ);
    void* p2 = parse_EQ(lex);
    void* p3 = parse_EQS(lex);

     return cons(make_node(AST_CLE, NULL), cons(p2, p3)); 
}
  if(lex->symbol.tag ==  SYM_GT){
    eat(lex, SYM_GT);
    void* p2 = parse_EQ(lex);
    void* p3 = parse_EQS(lex);

     return cons(make_node(AST_CGT, NULL), cons(p2, p3)); 
}
  if(lex->symbol.tag ==  SYM_GEQ){
    eat(lex, SYM_GEQ);
    void* p2 = parse_EQ(lex);
    void* p3 = parse_EQS(lex);

     return cons(make_node(AST_CGE, NULL), cons(p2, p3)); 
}
  if(lex->symbol.tag ==  SYM_NOTEQ){
    eat(lex, SYM_NOTEQ);
    void* p2 = parse_EQ(lex);
    void* p3 = parse_EQS(lex);

     return cons(make_node(AST_CNEQ, NULL), cons(p2, p3)); 
}
  syntax_error_message(lex, "error while parsing EQS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_SEMICOLON));
  printf(", %s", string_of_token(SYM_EQUALITY));
  printf(", %s", string_of_token(SYM_RPARENTHESIS));
  printf(", %s", string_of_token(SYM_LT));
  printf(", %s", string_of_token(SYM_LEQ));
  printf(", %s", string_of_token(SYM_GT));
  printf(", %s", string_of_token(SYM_GEQ));
  printf(", %s", string_of_token(SYM_NOTEQ));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_EXPR(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    void* p1 = parse_EQ(lex);
    void* p2 = parse_EQS(lex);

     return make_node(AST_EQS, cons(p1, p2)); 
}
  if(lex->symbol.tag ==  SYM_INTEGER){
    void* p1 = parse_EQ(lex);
    void* p2 = parse_EQS(lex);

     return make_node(AST_EQS, cons(p1, p2)); 
}
  if(lex->symbol.tag ==  SYM_MINUS){
    void* p1 = parse_EQ(lex);
    void* p2 = parse_EQS(lex);

     return make_node(AST_EQS, cons(p1, p2)); 
}
  if(lex->symbol.tag ==  SYM_LPARENTHESIS){
    void* p1 = parse_EQ(lex);
    void* p2 = parse_EQS(lex);

     return make_node(AST_EQS, cons(p1, p2)); 
}
  syntax_error_message(lex, "error while parsing EXPR");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf(", %s", string_of_token(SYM_MINUS));
  printf(", %s", string_of_token(SYM_LPARENTHESIS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_TERM(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    void* p1 = parse_FACTOR(lex);
    void* p2 = parse_FACTORS(lex);

     return make_node(AST_FACTORS, cons(p1, p2)); 
}
  if(lex->symbol.tag ==  SYM_INTEGER){
    void* p1 = parse_FACTOR(lex);
    void* p2 = parse_FACTORS(lex);

     return make_node(AST_FACTORS, cons(p1, p2)); 
}
  if(lex->symbol.tag ==  SYM_MINUS){
    void* p1 = parse_FACTOR(lex);
    void* p2 = parse_FACTORS(lex);

     return make_node(AST_FACTORS, cons(p1, p2)); 
}
  if(lex->symbol.tag ==  SYM_LPARENTHESIS){
    void* p1 = parse_FACTOR(lex);
    void* p2 = parse_FACTORS(lex);

     return make_node(AST_FACTORS, cons(p1, p2)); 
}
  syntax_error_message(lex, "error while parsing TERM");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf(", %s", string_of_token(SYM_MINUS));
  printf(", %s", string_of_token(SYM_LPARENTHESIS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_TERMS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_SEMICOLON){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_PLUS){
    eat(lex, SYM_PLUS);
    void* p2 = parse_TERM(lex);
    void* p3 = parse_TERMS(lex);

     return cons(make_node(AST_EADD, NULL), cons(p2, p3)); 
}
  if(lex->symbol.tag ==  SYM_MINUS){
    eat(lex, SYM_MINUS);
    void* p2 = parse_TERM(lex);
    void* p3 = parse_TERMS(lex);

     return cons(make_node(AST_ESUB, NULL), cons(p2, p3)); 
}
  if(lex->symbol.tag ==  SYM_EQUALITY){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_LT){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_LEQ){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_GT){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_GEQ){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_NOTEQ){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_MOD){
    eat(lex, SYM_MOD);
    void* p2 = parse_TERM(lex);
    void* p3 = parse_TERMS(lex);

     return cons(make_node(AST_EMOD, NULL), cons(p2, p3)); 
}
  syntax_error_message(lex, "error while parsing TERMS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_SEMICOLON));
  printf(", %s", string_of_token(SYM_PLUS));
  printf(", %s", string_of_token(SYM_MINUS));
  printf(", %s", string_of_token(SYM_EQUALITY));
  printf(", %s", string_of_token(SYM_RPARENTHESIS));
  printf(", %s", string_of_token(SYM_LT));
  printf(", %s", string_of_token(SYM_LEQ));
  printf(", %s", string_of_token(SYM_GT));
  printf(", %s", string_of_token(SYM_GEQ));
  printf(", %s", string_of_token(SYM_NOTEQ));
  printf(", %s", string_of_token(SYM_MOD));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_FACTOR(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    char* p1 = eat(lex, SYM_IDENTIFIER);

     return make_string_leaf(strdup(p1)); 
}
  if(lex->symbol.tag ==  SYM_INTEGER){
    char* p1 = eat(lex, SYM_INTEGER);

     return make_int_leaf(atoi(p1)); 
}
  if(lex->symbol.tag ==  SYM_MINUS){
    eat(lex, SYM_MINUS);
    void* p2 = parse_FACTOR(lex);

     return make_node(AST_ENEG, cons(p2, NULL)); 
}
  if(lex->symbol.tag ==  SYM_LPARENTHESIS){
    eat(lex, SYM_LPARENTHESIS);
    void* p2 = parse_EXPR(lex);
    eat(lex, SYM_RPARENTHESIS);

     return p2; 
}
  syntax_error_message(lex, "error while parsing FACTOR");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf(", %s", string_of_token(SYM_MINUS));
  printf(", %s", string_of_token(SYM_LPARENTHESIS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_FACTORS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_SEMICOLON){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_PLUS){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_MINUS){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_ASTERISK){
    eat(lex, SYM_ASTERISK);
    void* p2 = parse_FACTOR(lex);
    void* p3 = parse_FACTORS(lex);

     return cons(make_node(AST_EMUL, NULL), cons(p2, p3)); 
}
  if(lex->symbol.tag ==  SYM_DIV){
    eat(lex, SYM_DIV);
    void* p2 = parse_FACTOR(lex);
    void* p3 = parse_FACTORS(lex);

     return cons(make_node(AST_EDIV, NULL), cons(p2, p3)); 
}
  if(lex->symbol.tag ==  SYM_EQUALITY){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_LT){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_LEQ){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_GT){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_GEQ){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_NOTEQ){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_MOD){

     return NULL; 
}
  syntax_error_message(lex, "error while parsing FACTORS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_SEMICOLON));
  printf(", %s", string_of_token(SYM_PLUS));
  printf(", %s", string_of_token(SYM_MINUS));
  printf(", %s", string_of_token(SYM_ASTERISK));
  printf(", %s", string_of_token(SYM_DIV));
  printf(", %s", string_of_token(SYM_EQUALITY));
  printf(", %s", string_of_token(SYM_RPARENTHESIS));
  printf(", %s", string_of_token(SYM_LT));
  printf(", %s", string_of_token(SYM_LEQ));
  printf(", %s", string_of_token(SYM_GT));
  printf(", %s", string_of_token(SYM_GEQ));
  printf(", %s", string_of_token(SYM_NOTEQ));
  printf(", %s", string_of_token(SYM_MOD));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
