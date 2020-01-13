#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>


// maximum number of characters in an identifier
#define MAX_IDENTIFIER_LENGTH 64
// maximum number of characters in an unsigned integer
#define MAX_INTEGER_LENGTH 20

enum symbol_t {
               SYM_EOF, // end of file
               SYM_IDENTIFIER,  // identifier
               SYM_INTEGER,  // integer
               SYM_SEMICOLON,  // ;
               SYM_IF,  // if
               SYM_ELSE,  // else
               SYM_PLUS,  // +
               SYM_MINUS,  // -
               SYM_ASTERISK,  // *
               SYM_DIV, // /
               SYM_EQUALITY, // ==
               SYM_ASSIGN, // =
               SYM_LPARENTHESIS, // (
               SYM_RPARENTHESIS, // )
               SYM_LBRACE, // {
               SYM_RBRACE, // }
               SYM_WHILE, // while
               SYM_RETURN, // return
               SYM_COMMA, // ,
               SYM_LT, // <
               SYM_LEQ, // <=
               SYM_GT, // >
               SYM_GEQ, // >=
               SYM_NOTEQ, // !=
               SYM_MOD, // %
               SYM_PRINT, // print
};

typedef struct symb {
  enum symbol_t tag;
  char* id;
} symb;

typedef struct lexer_state {
  FILE* lexer_fd;
  unsigned long curpos;
  unsigned long line_number;
  symb symbol;
} lexer_state;

lexer_state* init_lexer_state(FILE*);
char get_character(lexer_state*);
void next_character(lexer_state*);


void next_symbol(lexer_state*);
void print_line_number(char* message, int line);
char* string_of_symbol(symb symbol);
char* string_of_token(enum symbol_t symbol);
void lexer_error_message(lexer_state* lex, char* message);

#endif
