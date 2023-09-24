#include "libs/common.h"
#include "libs/parser.h"
#include "libs/str.h"
#include "libs/tokenizer.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

int main (int argc, char** argv) {

    printf ("argc = %d\n", argc);

    if (argc != 2) {
        fprintf (stderr, "Usage: %s <file>\n", argv[0]);
        exit (1);
    }

    str file_contents = new_str (read_file (argv[1]));
    LTA array         = tokenize (file_contents);
    print_lexical_token_array (&array);
    AST_node AST = parse (&array, &file_contents);
    // free_AST_tree (&AST);
    // printf("done");
    // free(array.items);
    free (array.items);
    free (file_contents.contents);

    // return 0;
}
