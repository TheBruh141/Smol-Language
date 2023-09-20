#include "errors.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

static char *print_error_msg(enum Error_Code code) {
    char *ret = (char *)sml_malloc(30 * sizeof(char));
    switch (code) {

    case NO_ERROR:
        sprintf(ret, "NO_ERROR");
        break;
    case SYNTAX_ERROR:
        sprintf(ret, "SYNTAX_ERROR");
        break;
    case SEMANTIC_ERROR:
        sprintf(ret, "SEMANTIC_ERROR");
        break;
    case UNDECLARED_IDENTIFIER:
        sprintf(ret, "UNDECLARED_IDENTIFIER");
        break;
    case DUPLICATE_IDENTIFIER:
        sprintf(ret, "DUPLICATE_IDENTIFIER");
        break;
    case FILE_NOT_FOUND:
        sprintf(ret, "FILE_NOT_FOUND");
        break;
    case MEMORY_ALLOCATION_ERROR:
        sprintf(ret, "MEMORY_ALLOCATION_ERROR");
        break;
    case IO_ERROR:
        sprintf(ret, "IO_ERROR");
        break;
    case INTERNAL_ERROR:
        sprintf(ret, "INTERNAL_ERROR");
        break;
    default:
        sprintf(ret, "Unknown error type: %d", code);
        exit(2);
        break;
    }
    return ret;
}
void throw_error(enum Error_Code code, const char *message, bool should_abort) {
    /*
    how the error is going to look like

    [Smolc] -> [Err_Message] : Error_Code
        | Error_Message
    */

    printf(
        "[Smolc] -> [%s] : %d |\t aborting = %s\n\t|%s", print_error_msg(code),
        code, (should_abort) ? "yes" : "no", message
    );
}
