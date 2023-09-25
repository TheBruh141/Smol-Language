#include "parser.h"
#include "common.h"
#include "errors.h"
#include "str.h"
#include "tokenizer.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

// typedef struct AST_node {
//     enum Parse_Token type;
//     uint_fast64_t id;
//     str_array contents;AS
//     struct AST_node* parent;
//     struct AST_node* child;
//     struct AST_node* next_sibling;
//     struct AST_node* prev_sibling;
// } AST_node;

// have spent +10 hrs debugging this piece of garbage and at the end I have
// achieved salvation. no memory leaks. frees the AST tree below it
void free_AST_node (AST_node* node) {
    if (node == NULL) {
        return;
    }

    // Recursively free child nodes
    free_AST_node (node->child);

    // Free the contents of the str_array if it exists
    if (node->contents.strings != NULL) {
        free_string_array (&node->contents); // Assuming you have a function to free str_array
    }

    // Recursively free next siblings
    free_AST_node (node->next_sibling);

    // Free the current node
    free (node);
}


AST_node* new_AST_node (enum Parse_Token type) {
    static uint_fast64_t id = 0;

    AST_node* node     = (AST_node*)malloc (sizeof (AST_node));
    node->type         = type;
    node->id           = id++;
    node->parent       = NULL;
    node->child        = NULL;
    node->next_sibling = NULL;
    node->prev_sibling = NULL;
    return node;
}

AST_node* new_AST_node_with_contents (enum Parse_Token type, str_array contents) {
    AST_node* node         = new_AST_node (type);
    node->contents.strings = (str*)malloc (contents.capacity * sizeof (str));

    for (size_t i = 0; i < contents.last_pos; i++) {
        node->contents.strings[i] = contents.strings[i];
    }
    return node;
}


AST_node* parse_file (str file_contents) {
    // to come
}
