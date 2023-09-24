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

typedef struct {
    char** contents;
    uint32_t size;
} contents_t;

struct Parse_State;

typedef struct {
    struct Parse_State** childs;
    uint32_t child_count;
} childs_t;

typedef struct Parse_State {
    struct Parse_State* parent;
    childs_t childs;
    struct Parse_State* next_sibling;
    struct Parse_State* prev_sibling;
    enum Parse_Token token;
    uint32_t child_count;
    uint16_t sibling_count;
    uint16_t id;
    uint32_t line;
    uint32_t column;
    uint32_t indent_level;
    // contents
    contents_t contents;
} Parse_State;

// returns an empty contents structure
contents_t new_contents ();

// returns an empty parse structure
Parse_State* parse_state_new (Parse_State* parent);
void parse_state_free (Parse_State* state);

// parse the file
Parse_State* parse_file (const char* filename);

#endif // PARSER_H_
