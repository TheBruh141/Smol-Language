#include "parser.h"
#include "common.h"
#include "error.h"
#include "str.h"
#include "tokenizer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// step 1 : just do the markdown parsing
// this is like the DOM model
#define DEBUG 1
AST_node new_node(
    enum Parse_Token type, void *contents, struct AST_node *child,
    struct AST_node *next_sibling
) {
    AST_node node = {
        .child        = child,
        .type         = type,
        .contents     = contents,
        .next_sibling = next_sibling};
    return node;
}

void append_child(AST_node *parent, AST_node *child) { parent->child = child; }

void append_sibling(AST_node *parent, AST_node *sibling) {
    parent->next_sibling = sibling;
}

#pragma region print_defs

// Function to print MD_LIST
void printMD_LIST(const MD_LIST *md_list) {
    if (md_list == NULL) {
        printf("MD_LIST is NULL\n");
        return;
    }
    printf("MD_LIST:\n");
    printf("Contents: %s\n", md_list->contents);
    printf("Number: %d\n", md_list->number > 0);
}

// Function to print MD_CODE_LONG
void printMD_CODE_LONG(const MD_CODE_LONG *md_code_long) {
    if (md_code_long == NULL) {
        printf("MD_CODE_LONG is NULL\n");
        return;
    }

    printf("MD_CODE_LONG:\n");
    printf("Contents: %s\n", md_code_long->contents);
    printf("Language Name: %s\n", md_code_long->language_name);
}

// Function to print MD_LINK
void printMD_LINK(const MD_LINK *md_link) {
    if (md_link == NULL) {
        printf("MD_LINK is NULL\n");
        return;
    }

    printf("MD_LINK:\n");
    printf("Text: %s\n", md_link->text);
    printf("Link: %s\n", md_link->link);
}

// Function to print MD_IMAGE
void printMD_IMAGE(const MD_IMAGE *md_image) {
    if (md_image == NULL) {
        printf("MD_IMAGE is NULL\n");
        return;
    }

    printf("MD_IMAGE:\n");
    printf("Text: %s\n", md_image->text);
    printf("Link: %s\n", md_image->link);
}

// Function to print MD_TOK
void printMD_TOK(const MD_TOK *md_tok) {
    if (md_tok == NULL) {
        printf("MD_TOK is NULL\n");
        return;
    }

    printf("MD_TOK:\n");
    printf("Text: %s\n", md_tok->text);
}

// Function to print AST_node
void printAST_node(const AST_node *ast_node) {
    if (ast_node == NULL) {
        printf("AST_node is NULL\n");
        return;
    }

    printf("AST_node:\n");
    printf("Type: %d\n", ast_node->type);

    // Depending on the type, cast and print the contents appropriately
    switch (ast_node->type) {
    case MD_TOK_ORDERED_LIST:
        printMD_LIST((MD_LIST *)ast_node->contents);
        break;
    case MD_TOK_UNORDERED_LIST:
        printMD_LIST((MD_LIST *)ast_node->contents);
        break;
    case MD_TOK_CODE_LONG:
        printMD_CODE_LONG((MD_CODE_LONG *)ast_node->contents);
        break;
    case MD_TOK_LINK:
        printMD_LINK((MD_LINK *)ast_node->contents);
        break;
    case MD_TOK_IMAGE:
        printMD_IMAGE((MD_IMAGE *)ast_node->contents);
        break;
    default:
        printMD_TOK((MD_TOK *)ast_node->contents);
        break;
    }

    // Print child and next sibling if present
    printf("Child:\n");
    printAST_node(ast_node->child);

    printf("Next Sibling:\n");
    printAST_node(ast_node->next_sibling);
}

#pragma endregion print_defs

bool expect_token(
    lexical_token const *source_tok, enum Lexical_Tokens token_type, LTA *array,
    size_t index_of_source_tok, bool without_space
) {

    if (without_space) {
        return (bool)(array->items[index_of_source_tok + 1].type ==
                          token_type &&
                      source_tok->pos + 1 ==
                          array->items[index_of_source_tok + 1].pos);
    } else {

        return (bool)(array->items[source_tok->pos + 1].type == token_type);
    }
}

str walk_until_end_of_line(size_t pos_in_file, const char *contents) {
    char   c;
    size_t tracker = 0;
    while ((c = contents[pos_in_file + tracker++]) != '\n' && c != '\r')
        ;
    return new_str(get_portion_of_string(contents, pos_in_file, tracker));
}
// PARSE THE ENTIRE FILE
AST_node parse(LTA *tokens, str *file_contents) {
#if (DEBUG == 1)
    AST_node  root        = new_node(ROOT, NO_CONTENT, NOT_SET_YET, NO_CONTENT);
    AST_node *parent_node = &root;
#else
    AST_node root = new_node(ROOT, NULL, NULL, NULL);
#endif

    // go throught all the tokens
    lexical_token *this_token = {0};
    AST_node       new_token  = {0};
    for (size_t i = 0; i < tokens->last_pos; ++i) {
        this_token = &tokens->items[i];

        switch (this_token->type) {
        // headers
        case L_TOK_HASH: {
            int_fast16_t hash_level = 1;
            while (hash_level++ < 6 &&
                   expect_token(this_token, L_TOK_HASH, tokens, i, true))
                ;

            MD_TOK tok_contents = {
                .text = walk_until_end_of_line(
                            this_token->pos, file_contents->contents
                )
                            .contents};

            new_token = new_node(
                MD_TOK_HEADER_1 + --hash_level, (void *)&tok_contents,
                NO_CONTENT, NO_CONTENT
            );
            append_sibling(parent_node, &new_token);
            EXHAUST_TOKENS(&i, hash_level);
            break;
        }
        }
    }
    free(this_token);
}
