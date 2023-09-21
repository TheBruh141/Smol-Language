#include "common.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

void *sml_malloc(size_t size) {

    void *void_pointer = malloc(size);
    if (void_pointer == NULL) {
        throw_error(
            MEMORY_ALLOCATION_ERROR, "memory allocation failed in sml_malloc",
            true
        );
    }
    return void_pointer;
}

void *sml_calloc(size_t new_mem, size_t size) {

    void *void_pointer = calloc(new_mem, size);
    if (void_pointer == NULL) {
        throw_error(
            MEMORY_ALLOCATION_ERROR, "memory allocation failed in sml_calloc",
            true
        );
    }
    return void_pointer;
}

void *sml_realloc(void *p, unsigned long new_mem) {
    void *new_ptr = realloc(p, new_mem);

    if (new_ptr == NULL && new_mem > 0) {
        throw_error(MEMORY_ALLOCATION_ERROR, "realloc failed", true);
        exit(EXIT_FAILURE); // You can handle the error differently if needed
    }

    return new_ptr;
}

void *sml_alloc(size_t new_mem, size_t size) {
#ifdef DEBUG
    putchar('\n');
    void *ret = sml_calloc(new_mem, size);
#else
    putchar('\n');
    void *ret = sml_malloc(new_mem * size);
#endif
    return ret;
}

char *read_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, file_size, file);
    if (read_size != (size_t)file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0';
    fclose(file);
    return buffer;
}
