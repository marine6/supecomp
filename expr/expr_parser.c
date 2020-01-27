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
    void* p1 = parse_FUNCTION(lex);
    eat(lex, SYM_EOF);

     return p1; 
}
  syntax_error_message(lex, "error while parsing S");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_FUNCTION(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    parse_IDENTIFIER(lex);
    parse_LPARENTHESIS(lex);
    void* p3 = parse_ARGUMENTS(lex);
    parse_RPARENTHESIS(lex);
    void* p5 = parse_IBLOCK(lex);

     return make_node(AST_NODE_FUNDEF, cons(make_node(AST_NODE_FUNBODY, p5), p3)); 
}
  syntax_error_message(lex, "error while parsing FUNCTION");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_ARGUMENTS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_COMMA){
    eat(lex, SYM_COMMA);
    void* p2 = parse_ARGUMENT(lex);
    void* p3 = parse_ARGUMENTS(lex);

     return make_node(AST_NODE_FUNARGS, cons(p2, p3)); 
}
  syntax_error_message(lex, "error while parsing ARGUMENTS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_RPARENTHESIS));
  printf(", %s", string_of_token(SYM_COMMA));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_ARGUMENT(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    void* p1 = parse_FACTOR(lex);

     return p1; 
}
  if(lex->symbol.tag ==  SYM_INTEGER){
    void* p1 = parse_FACTOR(lex);

     return p1; 
}
  syntax_error_message(lex, "error while parsing ARGUMENT");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_LPARENTHESIS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_LPARENTHESIS){
    char* p1 = eat(lex, SYM_LPARENTHESIS);

     return p1; 
}
  syntax_error_message(lex, "error while parsing LPARENTHESIS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_LPARENTHESIS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_RPARENTHESIS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){
    char* p1 = eat(lex, SYM_RPARENTHESIS);

     return p1; 
}
  syntax_error_message(lex, "error while parsing RPARENTHESIS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_RPARENTHESIS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_IDENTIFIER(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    char* p1 = eat(lex, SYM_IDENTIFIER);

     return make_string_leaf(strdup(p1)); 
}
  syntax_error_message(lex, "error while parsing IDENTIFIER");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_INTEGER(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_INTEGER){
    char* p1 = eat(lex, SYM_INTEGER);

     return make_int_leaf(atoi(p1)); 
}
  syntax_error_message(lex, "error while parsing INTEGER");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_INTEGER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_EXPR(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    void* p1 = parse_TERM(lex);
    void* p2 = parse_TERMS(lex);
    eat(lex, SYM_SEMICOLON);

     return make_node(AST_TERMS, cons(p1, p2)); 
}
  if(lex->symbol.tag ==  SYM_INTEGER){
    void* p1 = parse_TERM(lex);
    void* p2 = parse_TERMS(lex);
    eat(lex, SYM_SEMICOLON);

     return make_node(AST_TERMS, cons(p1, p2)); 
}
  syntax_error_message(lex, "error while parsing EXPR");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
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
  syntax_error_message(lex, "error while parsing TERM");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
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
  syntax_error_message(lex, "error while parsing TERMS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_SEMICOLON));
  printf(", %s", string_of_token(SYM_PLUS));
  printf(", %s", string_of_token(SYM_MINUS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_INSTRUCTION(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    void* p1 = parse_IASSIGN(lex);

     return p1; 
}
  if(lex->symbol.tag ==  SYM_IF){
    void* p1 = parse_IFTHENELSE(lex);

     return p1; 
}
  if(lex->symbol.tag ==  SYM_LBRACE){
    void* p1 = parse_IBLOCK(lex);

     return p1; 
}
  if(lex->symbol.tag ==  SYM_WHILE){
    void* p1 = parse_IWHILE(lex);

     return p1; 
}
  if(lex->symbol.tag ==  SYM_RETURN){
    void* p1 = parse_IRETURN(lex);

     return p1; 
}
  if(lex->symbol.tag ==  SYM_PRINT){
    void* p1 = parse_IPRINT(lex);

     return p1; 
}
  syntax_error_message(lex, "error while parsing INSTRUCTION");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_IF));
  printf(", %s", string_of_token(SYM_LBRACE));
  printf(", %s", string_of_token(SYM_WHILE));
  printf(", %s", string_of_token(SYM_RETURN));
  printf(", %s", string_of_token(SYM_PRINT));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_INSTRUCTIONS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    void* p1 = parse_INSTRUCTION(lex);
    void* p2 = parse_INSTRUCTIONS(lex);

     return cons(p1, p2); 
}
  if(lex->symbol.tag ==  SYM_IF){
    void* p1 = parse_INSTRUCTION(lex);
    void* p2 = parse_INSTRUCTIONS(lex);

     return cons(p1, p2); 
}
  if(lex->symbol.tag ==  SYM_LBRACE){
    void* p1 = parse_INSTRUCTION(lex);
    void* p2 = parse_INSTRUCTIONS(lex);

     return cons(p1, p2); 
}
  if(lex->symbol.tag ==  SYM_RBRACE){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_WHILE){
    void* p1 = parse_INSTRUCTION(lex);
    void* p2 = parse_INSTRUCTIONS(lex);

     return cons(p1, p2); 
}
  if(lex->symbol.tag ==  SYM_RETURN){
    void* p1 = parse_INSTRUCTION(lex);
    void* p2 = parse_INSTRUCTIONS(lex);

     return cons(p1, p2); 
}
  if(lex->symbol.tag ==  SYM_PRINT){
    void* p1 = parse_INSTRUCTION(lex);
    void* p2 = parse_INSTRUCTIONS(lex);

     return cons(p1, p2); 
}
  syntax_error_message(lex, "error while parsing INSTRUCTIONS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_IF));
  printf(", %s", string_of_token(SYM_LBRACE));
  printf(", %s", string_of_token(SYM_RBRACE));
  printf(", %s", string_of_token(SYM_WHILE));
  printf(", %s", string_of_token(SYM_RETURN));
  printf(", %s", string_of_token(SYM_PRINT));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_CMP(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    void* p1 = parse_FACTOR(lex);

     return p1; 
}
  if(lex->symbol.tag ==  SYM_INTEGER){
    void* p1 = parse_FACTOR(lex);

     return p1; 
}
  if(lex->symbol.tag ==  SYM_EQUALITY){
    eat(lex, SYM_EQUALITY);
    void* p2 = parse_TERM(lex);
    void* p3 = parse_TERM(lex);

     return make_node(AST_CMPS, cons(make_node(AST_CEQ, NULL), cons(p2, p3))); 
}
  if(lex->symbol.tag ==  SYM_LT){
    eat(lex, SYM_LT);
    void* p2 = parse_TERM(lex);
    void* p3 = parse_TERM(lex);

     return make_node(AST_CMPS, cons(make_node(AST_CLT, NULL), cons(p2, p3))); 
}
  if(lex->symbol.tag ==  SYM_LEQ){
    eat(lex, SYM_LEQ);
    void* p2 = parse_TERM(lex);
    void* p3 = parse_TERM(lex);

     return make_node(AST_CMPS, cons(make_node(AST_CLE, NULL), cons(p2, p3))); 
}
  if(lex->symbol.tag ==  SYM_GT){
    eat(lex, SYM_GT);
    void* p2 = parse_TERM(lex);
    void* p3 = parse_TERM(lex);

     return make_node(AST_CMPS, cons(make_node(AST_CGT, NULL), cons(p2, p3))); 
}
  if(lex->symbol.tag ==  SYM_GEQ){
    eat(lex, SYM_GEQ);
    void* p2 = parse_TERM(lex);
    void* p3 = parse_TERM(lex);

     return make_node(AST_CMPS, cons(make_node(AST_CGE, NULL), cons(p2, p3))); 
}
  if(lex->symbol.tag ==  SYM_NOTEQ){
    eat(lex, SYM_NOTEQ);
    void* p2 = parse_TERM(lex);
    void* p3 = parse_TERM(lex);

     return make_node(AST_CMPS, cons(make_node(AST_CNEQ, NULL), cons(p2, p3))); 
}
  syntax_error_message(lex, "error while parsing CMP");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf(", %s", string_of_token(SYM_EQUALITY));
  printf(", %s", string_of_token(SYM_LT));
  printf(", %s", string_of_token(SYM_LEQ));
  printf(", %s", string_of_token(SYM_GT));
  printf(", %s", string_of_token(SYM_GEQ));
  printf(", %s", string_of_token(SYM_NOTEQ));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_IASSIGN(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    void* p1 = parse_IDENTIFIER(lex);
    eat(lex, SYM_EQUALITY);
    void* p3 = parse_EXPR(lex);

     return make_node(AST_IASSIGN, cons(p1, p3)); 
}
  syntax_error_message(lex, "error while parsing IASSIGN");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_IWHILE(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_WHILE){
    eat(lex, SYM_WHILE);
    parse_LPARENTHESIS(lex);
    void* p3 = parse_CMP(lex);
    parse_RPARENTHESIS(lex);
    void* p5 = parse_INSTRUCTION(lex);

     return make_node(AST_IWHILE, cons(p3,p5)); 
}
  syntax_error_message(lex, "error while parsing IWHILE");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_WHILE));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_IFTHEN(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IF){
    eat(lex, SYM_IF);
    parse_LPARENTHESIS(lex);
    void* p3 = parse_CMP(lex);
    parse_RPARENTHESIS(lex);
    void* p5 = parse_INSTRUCTION(lex);

     return cons(p3,p5); 
}
  syntax_error_message(lex, "error while parsing IFTHEN");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IF));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_IFTHENELSE(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IF){
    void* p1 = parse_IFTHEN(lex);
    void* p2 = parse_IELSE(lex);

     return make_node(AST_IIFTHENELSE, cons(p1,p2)); 
}
  syntax_error_message(lex, "error while parsing IFTHENELSE");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IF));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_IELSE(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_IF){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_ELSE){
    eat(lex, SYM_ELSE);
    void* p2 = parse_INSTRUCTION(lex);

     return p2; 
}
  if(lex->symbol.tag ==  SYM_LBRACE){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_RBRACE){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_WHILE){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_RETURN){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_PRINT){

     return NULL; 
}
  syntax_error_message(lex, "error while parsing IELSE");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_IF));
  printf(", %s", string_of_token(SYM_ELSE));
  printf(", %s", string_of_token(SYM_LBRACE));
  printf(", %s", string_of_token(SYM_RBRACE));
  printf(", %s", string_of_token(SYM_WHILE));
  printf(", %s", string_of_token(SYM_RETURN));
  printf(", %s", string_of_token(SYM_PRINT));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_IRETURN(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_RETURN){
    eat(lex, SYM_RETURN);
    void* p2 = parse_EXPR(lex);

     return make_node(AST_IRETURN, p2); 
}
  syntax_error_message(lex, "error while parsing IRETURN");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_RETURN));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_IPRINT(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_PRINT){
    eat(lex, SYM_PRINT);
    void* p2 = parse_EXPR(lex);

     return make_node(AST_IPRINT, p2); 
}
  syntax_error_message(lex, "error while parsing IPRINT");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_PRINT));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_IBLOCK(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_LBRACE){
    eat(lex, SYM_LBRACE);
    void* p2 = parse_INSTRUCTIONS(lex);
    eat(lex, SYM_RBRACE);

     return make_node(AST_IBLOCK, p2); 
}
  syntax_error_message(lex, "error while parsing IBLOCK");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_LBRACE));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_FACTOR(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    void* p1 = parse_IDENTIFIER(lex);

     return p1; 
}
  if(lex->symbol.tag ==  SYM_INTEGER){
    void* p1 = parse_INTEGER(lex);

     return p1; 
}
  syntax_error_message(lex, "error while parsing FACTOR");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
void* parse_FACTORS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_INTEGER){

     return NULL; 
}
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
  if(lex->symbol.tag ==  SYM_MOD){
    eat(lex, SYM_MOD);
    void* p2 = parse_FACTOR(lex);
    void* p3 = parse_FACTORS(lex);

     return cons(make_node(AST_EMOD, NULL), cons(p2, p3)); 
}
  syntax_error_message(lex, "error while parsing FACTORS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf(", %s", string_of_token(SYM_SEMICOLON));
  printf(", %s", string_of_token(SYM_PLUS));
  printf(", %s", string_of_token(SYM_MINUS));
  printf(", %s", string_of_token(SYM_ASTERISK));
  printf(", %s", string_of_token(SYM_DIV));
  printf(", %s", string_of_token(SYM_MOD));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
