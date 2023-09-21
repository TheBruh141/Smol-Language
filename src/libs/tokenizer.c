#include "tokenizer.h"
#include "common.h"
#include "errors.h"
#include "str.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

lexical_token
new_lexical_token(unsigned char type, size_t pos, size_t line, size_t column) {
    lexical_token new_token = {
        .type = type, .pos = pos, .line = line, .column = column};
    return new_token;
}

lexical_token_array new_lexical_token_array(void) {
    lexical_token_array arr = {
        .capacity = 1,
        .items    = (lexical_token *)sml_alloc(1, sizeof(lexical_token)),
        .last_pos = 0,
    };
    return arr;
}

void double_lexical_token_capacity(lexical_token_array *arr) {
    static int failed_state  = 0;
    arr->capacity           *= 2;
    size_t         size      = arr->capacity * sizeof(lexical_token);
    lexical_token *temp      = arr->items;
    temp = (lexical_token *)realloc((void *)arr->items, size);
    if (NULL == temp) {
        throw_error(MEMORY_ALLOCATION_ERROR, "cannot double array", false);
        failed_state++;
        if (failed_state > 5) {
            throw_error(MEMORY_ALLOCATION_ERROR, "cannot double array", true);
        }
        double_lexical_token_capacity(arr);
    } else {
        arr->items = temp;
    }
}

void append_lexical_token(lexical_token_array *arr, lexical_token *tok) {
    if (arr->last_pos + 1 == arr->capacity) {
        double_lexical_token_capacity(arr);
    }
    arr->items[arr->last_pos++] = *tok;
}

int is_token(const char t) {
    switch (t) {
    case L_TOK_NEWLINE:
        return L_TOK_NEWLINE;
    case L_TOK_HASH:
        return L_TOK_HASH;
    case L_TOK_STAR:
        return L_TOK_STAR;
    case L_TOK_UNDERLINE:
        return L_TOK_UNDERLINE;
    case L_TOK_DOT:
        return L_TOK_DOT;
    case L_TOK_BACKTICK:
        return L_TOK_BACKTICK;
    case L_TOK_SEMICOLON:
        return L_TOK_SEMICOLON;
    case L_TOK_COLON:
        return L_TOK_COLON;
    case L_TOK_BIGGER_THAN:
        return L_TOK_BIGGER_THAN;
    case L_TOK_DASH:
        return L_TOK_DASH;
    case L_TOK_SLASH_F:
        return L_TOK_SLASH_F;
    case L_TOK_SLASH_B:
        return L_TOK_SLASH_B;
    case L_TOK_SQUARE_PARAN_L:
        return L_TOK_SQUARE_PARAN_L;
    case L_TOK_SQUARE_PARAN_R:
        return L_TOK_SQUARE_PARAN_R;
    case L_TOK_CURLY_PARAN_L:
        return L_TOK_CURLY_PARAN_L;
    case L_TOK_CURLY_PARAN_R:
        return L_TOK_CURLY_PARAN_R;
    }
    if (isdigit(t)) {
        return L_TOK_NUM;
    }
    return -1;
}

lexical_token_array tokenize(str file_contents) {
    fprintf(stdout, "start\n");
    debug_print_str(&file_contents);
    LTA    array = new_lexical_token_array();
    size_t col   = 0;
    size_t line  = 0;

    for (size_t i = 0; i < file_contents.last_pos; i++, col++) {
        int t;
        if ((t = is_token(file_contents.contents[i])) != -1) {
            if (t == L_TOK_NEWLINE) {
                col = 0;
                ++line;
            } else {
                lexical_token token =
                    new_lexical_token((unsigned char)t, i, line, col);
                append_lexical_token(&array, &token);
                fprintf(
                    stdout, "%c - %lu \n", (unsigned char)t, (unsigned long)i
                );
            }
        }
    }
    return array;
}

void print_lexical_token(const lexical_token *token) {
    fprintf(
        stdout, "Type: %u, Position: %zu, Line: %zu, Column: %zu\n",
        token->type, token->pos, token->line, token->column
    );
}

void print_lexical_token_array(const lexical_token_array *array) {
    fprintf(
        stdout, "Lexical Token Array (Capacity: %zu, Last Position: %zu):\n",
        array->capacity, array->last_pos
    );

    for (size_t i = 0; i <= array->last_pos; i++) {
        fprintf(stdout, "Token %zu:\n", i);
        print_lexical_token(&(array->items[i]));
        fprintf(stdout, "\n");
    }
}
