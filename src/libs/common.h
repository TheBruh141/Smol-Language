#ifndef COMMON_H_
#define COMMON_H_

/* This file is just a fancy wrapper around some essencial functions to make
 * them more bulletproof.
 */

#include "str.h"
#include <stdlib.h>
// prototypes

void *sml_malloc(size_t size);
void *sml_calloc(size_t new_mem, size_t size);
void *sml_realloc(void *p, unsigned long new_mem);

char *read_file(char *filename);

// custom memory allocator
void *sml_alloc(size_t new_mem, size_t size);
#endif // COMMON_H_
