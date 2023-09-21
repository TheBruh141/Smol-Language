#include "libs/common.h"
#include "libs/parser.h"
#include "libs/str.h"
#include "libs/tokenizer.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

int main(void) {

    char *file_contents = read_file("/home/bruh-linux-arch/main/coding/"
                                    "Smol_git/Smol-Language/tests/test.smol");

    printf("%s\n", file_contents);

    LTA array = tokenize(new_str(file_contents));
    print_lexical_token_array(&array);
    printf("done");
    free(array.items);

    return 0;
}
