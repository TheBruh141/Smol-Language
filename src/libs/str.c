#include "str.h"
#include "common.h"
#include <stdio.h>
#include <string.h>

str new_str(char *contents) {
    str new = {
        .contents = contents,
        .capacity = strlen(contents),
        .last_pos = strlen(contents)};
    return new;
}

void double_str_capacity(str *str) {
    str->capacity += 2;
    str->contents  = (char *)realloc(str->contents, str->capacity);
}

// this function frees char* contents
void append_to_str(str *source, char *contents, size_t char_size) {

    if (source->capacity < source->capacity + char_size) {
        double_str_capacity(source);
    }

    strcat(source->contents, contents);
    free(contents);
}
void debug_print_str(const str *s) {
    printf("String Contents: %s\n", s->contents);
    printf("Capacity: %zu\n", s->capacity);
    printf("Last Position: %zu\n", s->last_pos);
}
