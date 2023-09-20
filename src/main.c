#include "libs/str.h"
#include "libs/tokenizer.h"
#include "libs/parser.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

int main(void) {

    LTA array = tokenize(
        new_str("#, * , _, . , `, ; \n, > , -, / , [, ], : , =, {,}, \", ',  |")
    );
    print_lexical_token_array(&array);
    free(array.items);
    MD_CODE_LONG temp = {.contents = "asd", .language_name = "Smol"};

    AST_node node = {
        .child = NULL,
        .type = MD_TOK_CODE_LONG,
        .contents = &temp,
        .next_sibling = NULL,
    };
    printAST_node(&node);

    return 0;
}
