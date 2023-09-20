#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include "str.h"
#include <stdbool.h>
#include <stddef.h>

enum Lexical_Tokens {

    L_TOK_NUM = 1,
    L_TOK_NEWLINE        = '\n',
    L_TOK_HASH           = '#',
    L_TOK_STAR           = '*',
    L_TOK_UNDERLINE      = '_',
    L_TOK_DOT            = '.',
    L_TOK_BACKTICK       = '`',
    L_TOK_SEMICOLON      = ';',
    L_TOK_COLON          = ':',
    L_TOK_BIGGER_THAN    = '>',
    L_TOK_DASH           = '-',
    L_TOK_SLASH_F        = '/',
    L_TOK_SLASH_B        = '\\',
    L_TOK_SQUARE_PARAN_L = '[',
    L_TOK_SQUARE_PARAN_R = ']',
    L_TOK_CURLY_PARAN_L  = '{',
    L_TOK_CURLY_PARAN_R  = '}',

};

// can be optimized further for memory
// a token that hols a single character

/*
 * @brief a token that hols a single character
 *
 * @param type
 * @param pos
 * @param line
 * @param column
 */
typedef struct {

    unsigned char type; // enum token Lexical Tokens
    size_t        pos;
    size_t        line;
    size_t        column;

} lexical_token;

typedef struct {
    lexical_token *items;
    size_t         capacity;
    size_t         last_pos;
} lexical_token_array;

// prototypes
// initializing or struct routines

typedef lexical_token_array LTA;

lexical_token
new_lexical_token(unsigned char type, size_t pos, size_t line, size_t column);

LTA  new_empty_lexical_token(void);
void double_lexical_token_capacity(lexical_token_array *arr);
void append_lexical_token(lexical_token_array *arr, lexical_token *tok);

// semantic routines
int  is_token(const char t);
lexical_token_array tokenize(str file_contents);

// printing routines
void print_lexical_token(const lexical_token *token);
void print_lexical_token_array(const lexical_token_array *array);


#endif // TOKENIZER_H_
