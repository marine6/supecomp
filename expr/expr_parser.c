#include "expr_parser.h"
#include "parser.h"
#include "lexer.h"
#include "datatypes.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct list* parse_LPARAMS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    struct ast_node* p1 = parse_IDENTIFIER(lex);
    struct list* p2 = parse_REST_PARAMS(lex);

    return cons(p1, p2);
}
  syntax_error_message(lex, "error while parsing LPARAMS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_RPARENTHESIS));
  printf(", %s", string_of_token(SYM_IDENTIFIER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct list* parse_REST_PARAMS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_COMMA){
    eat(lex, SYM_COMMA);
    struct ast_node* p2 = parse_IDENTIFIER(lex);
    struct list* p3 = parse_REST_PARAMS(lex);

    return cons(p2, p3);
}
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){

     return NULL; 
}
  syntax_error_message(lex, "error while parsing REST_PARAMS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_COMMA));
  printf(", %s", string_of_token(SYM_RPARENTHESIS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct list* parse_INSTRS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_PRINT){
    struct ast_node* p1 = parse_INSTR(lex);
    struct list* p2 = parse_INSTRS(lex);

    return cons(p1, p2);
}
  if(lex->symbol.tag ==  SYM_RETURN){
    struct ast_node* p1 = parse_INSTR(lex);
    struct list* p2 = parse_INSTRS(lex);

    return cons(p1, p2);
}
  if(lex->symbol.tag ==  SYM_IF){
    struct ast_node* p1 = parse_INSTR(lex);
    struct list* p2 = parse_INSTRS(lex);

    return cons(p1, p2);
}
  if(lex->symbol.tag ==  SYM_WHILE){
    struct ast_node* p1 = parse_INSTR(lex);
    struct list* p2 = parse_INSTRS(lex);

    return cons(p1, p2);
}
  if(lex->symbol.tag ==  SYM_LBRACE){
    struct ast_node* p1 = parse_INSTR(lex);
    struct list* p2 = parse_INSTRS(lex);

    return cons(p1, p2);
}
  if(lex->symbol.tag ==  SYM_RBRACE){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    struct ast_node* p1 = parse_INSTR(lex);
    struct list* p2 = parse_INSTRS(lex);

    return cons(p1, p2);
}
  syntax_error_message(lex, "error while parsing INSTRS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_PRINT));
  printf(", %s", string_of_token(SYM_RETURN));
  printf(", %s", string_of_token(SYM_IF));
  printf(", %s", string_of_token(SYM_WHILE));
  printf(", %s", string_of_token(SYM_LBRACE));
  printf(", %s", string_of_token(SYM_RBRACE));
  printf(", %s", string_of_token(SYM_IDENTIFIER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct list* parse_FACTORS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_EQUALITY){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_NOTEQ){

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
  if(lex->symbol.tag ==  SYM_SEMICOLON){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){

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
    struct ast_node* p2 = parse_FACTOR(lex);
    struct list* p3 = parse_FACTORS(lex);

     return cons(make_node(AST_EMUL,NULL), cons(p2, p3)); 
}
  if(lex->symbol.tag ==  SYM_DIV){
    eat(lex, SYM_DIV);
    struct ast_node* p2 = parse_FACTOR(lex);
    struct list* p3 = parse_FACTORS(lex);

     return cons(make_node(AST_EDIV, NULL), cons(p2, p3)); 
}
  if(lex->symbol.tag ==  SYM_MOD){
    eat(lex, SYM_MOD);
    struct ast_node* p2 = parse_FACTOR(lex);
    struct list* p3 = parse_FACTORS(lex);

     return cons(make_node(AST_EMOD,NULL), cons(p2, p3)); 
}
  syntax_error_message(lex, "error while parsing FACTORS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_EQUALITY));
  printf(", %s", string_of_token(SYM_NOTEQ));
  printf(", %s", string_of_token(SYM_LT));
  printf(", %s", string_of_token(SYM_LEQ));
  printf(", %s", string_of_token(SYM_GT));
  printf(", %s", string_of_token(SYM_GEQ));
  printf(", %s", string_of_token(SYM_SEMICOLON));
  printf(", %s", string_of_token(SYM_RPARENTHESIS));
  printf(", %s", string_of_token(SYM_PLUS));
  printf(", %s", string_of_token(SYM_MINUS));
  printf(", %s", string_of_token(SYM_ASTERISK));
  printf(", %s", string_of_token(SYM_DIV));
  printf(", %s", string_of_token(SYM_MOD));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct list* parse_TERMS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_EQUALITY){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_NOTEQ){

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
  if(lex->symbol.tag ==  SYM_SEMICOLON){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){

     return NULL; 
}
  if(lex->symbol.tag ==  SYM_PLUS){
    eat(lex, SYM_PLUS);
    struct ast_node* p2 = parse_TERM(lex);
    struct list* p3 = parse_TERMS(lex);

     return cons(make_node(AST_EADD, NULL), cons(p2, p3)); 
}
  if(lex->symbol.tag ==  SYM_MINUS){
    eat(lex, SYM_MINUS);
    struct ast_node* p2 = parse_TERM(lex);
    struct list* p3 = parse_TERMS(lex);

     return cons(make_node(AST_ESUB, NULL), cons(p2, p3)); 
}
  syntax_error_message(lex, "error while parsing TERMS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_EQUALITY));
  printf(", %s", string_of_token(SYM_NOTEQ));
  printf(", %s", string_of_token(SYM_LT));
  printf(", %s", string_of_token(SYM_LEQ));
  printf(", %s", string_of_token(SYM_GT));
  printf(", %s", string_of_token(SYM_GEQ));
  printf(", %s", string_of_token(SYM_SEMICOLON));
  printf(", %s", string_of_token(SYM_RPARENTHESIS));
  printf(", %s", string_of_token(SYM_PLUS));
  printf(", %s", string_of_token(SYM_MINUS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct list* parse_CMPS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_EQUALITY){

    return NULL;
}
  if(lex->symbol.tag ==  SYM_NOTEQ){

    return NULL;
}
  if(lex->symbol.tag ==  SYM_LT){
    eat(lex, SYM_LT);
    struct ast_node* p2 = parse_CMP(lex);
    struct list* p3 = parse_CMPS(lex);

     return cons(make_node(AST_CLT, NULL), cons(p2,p3)); 
}
  if(lex->symbol.tag ==  SYM_LEQ){
    eat(lex, SYM_LEQ);
    struct ast_node* p2 = parse_CMP(lex);
    struct list* p3 = parse_CMPS(lex);

     return cons(make_node(AST_CLE, NULL), cons(p2,p3)); 
}
  if(lex->symbol.tag ==  SYM_GT){
    eat(lex, SYM_GT);
    struct ast_node* p2 = parse_CMP(lex);
    struct list* p3 = parse_CMPS(lex);

     return cons(make_node(AST_CGT, NULL), cons(p2,p3)); 
}
  if(lex->symbol.tag ==  SYM_GEQ){
    eat(lex, SYM_GEQ);
    struct ast_node* p2 = parse_CMP(lex);
    struct list* p3 = parse_CMPS(lex);

     return cons(make_node(AST_CGE, NULL), cons(p2,p3)); 
}
  if(lex->symbol.tag ==  SYM_SEMICOLON){

    return NULL;
}
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){

    return NULL;
}
  syntax_error_message(lex, "error while parsing CMPS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_EQUALITY));
  printf(", %s", string_of_token(SYM_NOTEQ));
  printf(", %s", string_of_token(SYM_LT));
  printf(", %s", string_of_token(SYM_LEQ));
  printf(", %s", string_of_token(SYM_GT));
  printf(", %s", string_of_token(SYM_GEQ));
  printf(", %s", string_of_token(SYM_SEMICOLON));
  printf(", %s", string_of_token(SYM_RPARENTHESIS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct list* parse_EQS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_EQUALITY){
    eat(lex, SYM_EQUALITY);
    struct ast_node* p2 = parse_EQ(lex);
    struct list* p3 = parse_EQS(lex);

     return cons(make_node(AST_CEQ, NULL), cons(p2,p3)); 
}
  if(lex->symbol.tag ==  SYM_NOTEQ){
    eat(lex, SYM_NOTEQ);
    struct ast_node* p2 = parse_EQ(lex);
    struct list* p3 = parse_EQS(lex);

     return cons(make_node(AST_CNEQ, NULL), cons(p2,p3)); 
}
  if(lex->symbol.tag ==  SYM_SEMICOLON){

    return NULL;
}
  if(lex->symbol.tag ==  SYM_RPARENTHESIS){

    return NULL;
}
  syntax_error_message(lex, "error while parsing EQS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_EQUALITY));
  printf(", %s", string_of_token(SYM_NOTEQ));
  printf(", %s", string_of_token(SYM_SEMICOLON));
  printf(", %s", string_of_token(SYM_RPARENTHESIS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct ast_node* parse_IDENTIFIER(lexer_state* lex){
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
struct ast_node* parse_INTEGER(lexer_state* lex){
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
struct ast_node* parse_EXPR(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_LPARENTHESIS){
    struct ast_node* p1 = parse_EQ(lex);
    struct list* p2 = parse_EQS(lex);

     return make_node(AST_EQS, cons(p1,p2)); 
}
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    struct ast_node* p1 = parse_EQ(lex);
    struct list* p2 = parse_EQS(lex);

     return make_node(AST_EQS, cons(p1,p2)); 
}
  if(lex->symbol.tag ==  SYM_INTEGER){
    struct ast_node* p1 = parse_EQ(lex);
    struct list* p2 = parse_EQS(lex);

     return make_node(AST_EQS, cons(p1,p2)); 
}
  if(lex->symbol.tag ==  SYM_MINUS){
    struct ast_node* p1 = parse_EQ(lex);
    struct list* p2 = parse_EQS(lex);

     return make_node(AST_EQS, cons(p1,p2)); 
}
  syntax_error_message(lex, "error while parsing EXPR");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_LPARENTHESIS));
  printf(", %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf(", %s", string_of_token(SYM_MINUS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct ast_node* parse_TERM(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_LPARENTHESIS){
    struct ast_node* p1 = parse_FACTOR(lex);
    struct list* p2 = parse_FACTORS(lex);

     return make_node(AST_FACTORS,cons(p1,p2)); 
}
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    struct ast_node* p1 = parse_FACTOR(lex);
    struct list* p2 = parse_FACTORS(lex);

     return make_node(AST_FACTORS,cons(p1,p2)); 
}
  if(lex->symbol.tag ==  SYM_INTEGER){
    struct ast_node* p1 = parse_FACTOR(lex);
    struct list* p2 = parse_FACTORS(lex);

     return make_node(AST_FACTORS,cons(p1,p2)); 
}
  if(lex->symbol.tag ==  SYM_MINUS){
    struct ast_node* p1 = parse_FACTOR(lex);
    struct list* p2 = parse_FACTORS(lex);

     return make_node(AST_FACTORS,cons(p1,p2)); 
}
  syntax_error_message(lex, "error while parsing TERM");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_LPARENTHESIS));
  printf(", %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf(", %s", string_of_token(SYM_MINUS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct ast_node* parse_FACTOR(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_LPARENTHESIS){
    eat(lex, SYM_LPARENTHESIS);
    struct ast_node* p2 = parse_EXPR(lex);
    eat(lex, SYM_RPARENTHESIS);

     return p2; 
}
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    struct ast_node* p1 = parse_IDENTIFIER(lex);

    
return p1;

}
  if(lex->symbol.tag ==  SYM_INTEGER){
    struct ast_node* p1 = parse_INTEGER(lex);

     return p1; 
}
  if(lex->symbol.tag ==  SYM_MINUS){
    eat(lex, SYM_MINUS);
    struct ast_node* p2 = parse_FACTOR(lex);

     return make_node(AST_ENEG,cons(p2,NULL)); 
}
  syntax_error_message(lex, "error while parsing FACTOR");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_LPARENTHESIS));
  printf(", %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf(", %s", string_of_token(SYM_MINUS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct ast_node* parse_CMP(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_LPARENTHESIS){
    struct ast_node* p1 = parse_TERM(lex);
    struct list* p2 = parse_TERMS(lex);

     return make_node(AST_TERMS,cons(p1,p2)); 
}
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    struct ast_node* p1 = parse_TERM(lex);
    struct list* p2 = parse_TERMS(lex);

     return make_node(AST_TERMS,cons(p1,p2)); 
}
  if(lex->symbol.tag ==  SYM_INTEGER){
    struct ast_node* p1 = parse_TERM(lex);
    struct list* p2 = parse_TERMS(lex);

     return make_node(AST_TERMS,cons(p1,p2)); 
}
  if(lex->symbol.tag ==  SYM_MINUS){
    struct ast_node* p1 = parse_TERM(lex);
    struct list* p2 = parse_TERMS(lex);

     return make_node(AST_TERMS,cons(p1,p2)); 
}
  syntax_error_message(lex, "error while parsing CMP");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_LPARENTHESIS));
  printf(", %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf(", %s", string_of_token(SYM_MINUS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct ast_node* parse_EQ(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_LPARENTHESIS){
    struct ast_node* p1 = parse_CMP(lex);
    struct list* p2 = parse_CMPS(lex);

     return make_node(AST_CMPS, cons(p1,p2)); 
}
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    struct ast_node* p1 = parse_CMP(lex);
    struct list* p2 = parse_CMPS(lex);

     return make_node(AST_CMPS, cons(p1,p2)); 
}
  if(lex->symbol.tag ==  SYM_INTEGER){
    struct ast_node* p1 = parse_CMP(lex);
    struct list* p2 = parse_CMPS(lex);

     return make_node(AST_CMPS, cons(p1,p2)); 
}
  if(lex->symbol.tag ==  SYM_MINUS){
    struct ast_node* p1 = parse_CMP(lex);
    struct list* p2 = parse_CMPS(lex);

     return make_node(AST_CMPS, cons(p1,p2)); 
}
  syntax_error_message(lex, "error while parsing EQ");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_LPARENTHESIS));
  printf(", %s", string_of_token(SYM_IDENTIFIER));
  printf(", %s", string_of_token(SYM_INTEGER));
  printf(", %s", string_of_token(SYM_MINUS));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct ast_node* parse_INSTR(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_PRINT){
    eat(lex, SYM_PRINT);
    struct ast_node* p2 = parse_EXPR(lex);
    eat(lex, SYM_SEMICOLON);

    
    return make_node(AST_IPRINT, cons(p2, NULL));

}
  if(lex->symbol.tag ==  SYM_RETURN){
    eat(lex, SYM_RETURN);
    struct ast_node* p2 = parse_EXPR(lex);
    eat(lex, SYM_SEMICOLON);

    
    return make_node(AST_IRETURN, cons(p2, NULL));

}
  if(lex->symbol.tag ==  SYM_IF){
    eat(lex, SYM_IF);
    eat(lex, SYM_LPARENTHESIS);
    struct ast_node* p3 = parse_EXPR(lex);
    eat(lex, SYM_RPARENTHESIS);
    struct ast_node* p5 = parse_LINSTRS(lex);
    struct ast_node* p6 = parse_ELSE(lex);

    
    return make_node(AST_IIFTHENELSE, cons(p3, cons(p5, cons(p6, NULL))));

}
  if(lex->symbol.tag ==  SYM_WHILE){
    eat(lex, SYM_WHILE);
    eat(lex, SYM_LPARENTHESIS);
    struct ast_node* p3 = parse_EXPR(lex);
    eat(lex, SYM_RPARENTHESIS);
    struct ast_node* p5 = parse_INSTR(lex);

    
    return make_node(AST_IWHILE, cons(p3, cons(p5, NULL)));

}
  if(lex->symbol.tag ==  SYM_LBRACE){
    struct ast_node* p1 = parse_LINSTRS(lex);

     return p1 ; 
}
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    struct ast_node* p1 = parse_IDENTIFIER(lex);
    eat(lex, SYM_ASSIGN);
    struct ast_node* p3 = parse_EXPR(lex);
    eat(lex, SYM_SEMICOLON);

    
    return make_node(AST_IASSIGN, cons(p1, cons(p3, NULL)));

}
  syntax_error_message(lex, "error while parsing INSTR");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_PRINT));
  printf(", %s", string_of_token(SYM_RETURN));
  printf(", %s", string_of_token(SYM_IF));
  printf(", %s", string_of_token(SYM_WHILE));
  printf(", %s", string_of_token(SYM_LBRACE));
  printf(", %s", string_of_token(SYM_IDENTIFIER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct ast_node* parse_LINSTRS(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_LBRACE){
    eat(lex, SYM_LBRACE);
    struct list* p2 = parse_INSTRS(lex);
    eat(lex, SYM_RBRACE);

     return make_node(AST_IBLOCK, p2); 
}
  syntax_error_message(lex, "error while parsing LINSTRS");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_LBRACE));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct ast_node* parse_ELSE(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_PRINT){

     return make_node(AST_IBLOCK, NULL); 
}
  if(lex->symbol.tag ==  SYM_RETURN){

     return make_node(AST_IBLOCK, NULL); 
}
  if(lex->symbol.tag ==  SYM_IF){

     return make_node(AST_IBLOCK, NULL); 
}
  if(lex->symbol.tag ==  SYM_WHILE){

     return make_node(AST_IBLOCK, NULL); 
}
  if(lex->symbol.tag ==  SYM_ELSE){
    eat(lex, SYM_ELSE);
    struct ast_node* p2 = parse_LINSTRS(lex);

     return p2; 
}
  if(lex->symbol.tag ==  SYM_LBRACE){

     return make_node(AST_IBLOCK, NULL); 
}
  if(lex->symbol.tag ==  SYM_RBRACE){

     return make_node(AST_IBLOCK, NULL); 
}
  if(lex->symbol.tag ==  SYM_EOF){

     return make_node(AST_IBLOCK, NULL); 
}
  if(lex->symbol.tag ==  SYM_IDENTIFIER){

     return make_node(AST_IBLOCK, NULL); 
}
  syntax_error_message(lex, "error while parsing ELSE");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_PRINT));
  printf(", %s", string_of_token(SYM_RETURN));
  printf(", %s", string_of_token(SYM_IF));
  printf(", %s", string_of_token(SYM_WHILE));
  printf(", %s", string_of_token(SYM_ELSE));
  printf(", %s", string_of_token(SYM_LBRACE));
  printf(", %s", string_of_token(SYM_RBRACE));
  printf(", %s", string_of_token(SYM_EOF));
  printf(", %s", string_of_token(SYM_IDENTIFIER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
struct ast_node* parse_S(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    struct ast_node* p1 = parse_FUNC_DEF(lex);
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
struct ast_node* parse_FUNC_DEF(lexer_state* lex){
  if(lex->symbol.tag ==  SYM_IDENTIFIER){
    struct ast_node* p1 = parse_IDENTIFIER(lex);
    eat(lex, SYM_LPARENTHESIS);
    struct list* p3 = parse_LPARAMS(lex);
    eat(lex, SYM_RPARENTHESIS);
    struct ast_node* p5 = parse_INSTR(lex);

    
    return make_node(AST_NODE_FUNDEF,
                     cons(p1,
                          cons(make_node(AST_NODE_FUNARGS, p3),
                               cons(make_node(AST_NODE_FUNBODY, cons(p5,NULL)), NULL))));

}
  syntax_error_message(lex, "error while parsing FUNC_DEF");
  printf("Expected one of ");
  printf("{ %s", string_of_token(SYM_IDENTIFIER));
  printf("}");
  printf(" but got '%s' instead.\n", string_of_symbol(lex->symbol));
  exit(1);
}
