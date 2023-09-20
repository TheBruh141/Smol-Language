#ifndef ERRORS_H_
#define ERRORS_H_

#include <stdbool.h>

#define CHECK_DEBUG(x) /*Assert Replacement*/                                  \
    if (!(x)) {                                                                \
        printf(                                                                \
            "My check debug failed: (%s), function %s, file %s, line "         \
            "%d.\n",                                                           \
            STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__                    \
        );                                                                     \
        abort();                                                               \
    }

enum Error_Code {
    NO_ERROR = 0,            // No error
    SYNTAX_ERROR,            // Syntax error in the source code
    SEMANTIC_ERROR,          // Semantic error (e.g., type mismatch)
    UNDECLARED_IDENTIFIER,   // Use of undeclared identifier
    DUPLICATE_IDENTIFIER,    // Duplicate variable or function declaration
    FILE_NOT_FOUND,          // Source file not found
    MEMORY_ALLOCATION_ERROR, // Memory allocation error
    IO_ERROR,                // Input/output error
    INTERNAL_ERROR,          // Internal compiler error
};

// prototypes

static char *print_error_msg(enum Error_Code code);
void throw_error(enum Error_Code code, const char *message, bool should_abort);

#endif // ERRORS_H_
