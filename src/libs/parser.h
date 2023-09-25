#ifndef PARSER_H_
#define PARSER_H_

#include "str.h"
#include "tokenizer.h"
#include <stdint.h>

#define NO_CONTENT (void*)0  // defined as the garbage value
#define NOT_SET_YET (void*)0 // defined as the garbage value for not set vars

#define EXHAUST_TOKEN(i) (*(i)++)
#define EXHAUST_TOKENS(i, how_many) (*(i) += (how_many))
#define WITHOUT_SPACE 1
#define WITH_SPACE 0

enum Parse_Token {
    ROOT = -1,
    // MARKDOWN
    TEXT = 0,
    MD_TOK_HEADER_1,
    MD_TOK_HEADER_2,
    MD_TOK_HEADER_3,
    MD_TOK_HEADER_4,
    MD_TOK_HEADER_5,
    MD_TOK_HEADER_6,

    MD_TOK_BOLD,
    MD_TOK_ITALIC,
    MD_TOK_BOLD_ITALIC,

    MD_TOK_BLOCK_QUOTE,

    MD_TOK_ORDERED_LIST,
    MD_TOK_UNORDERED_LIST,

    MD_TOK_CODE_SHORT,
    MD_TOK_CODE_LONG,

    MD_TOK_HORIZONTAL_RULE,
    MD_TOK_LINK,
    MD_TOK_IMAGE,

    SML_VISUAL_START,
    SML_VISUAL_END,
    SML_SEMANTIC_START,
    SML_SEMANTIC_END,
    SML_ATTIBUTE_START,
    SML_ATTRIBUTE_END,
    // !MARKDOWN
};

typedef struct AST_node {
    enum Parse_Token type;
    uint_fast64_t id;
    str_array contents;
    struct AST_node* parent;
    struct AST_node* child;
    struct AST_node* next_sibling;
    struct AST_node* prev_sibling;
} AST_node;

void free_all_AST (AST_node* root);
#endif // PARSER_H_
