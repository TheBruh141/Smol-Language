#include "str.h"
#include "common.h"
#include "errors.h"
#include <stdio.h>
#include <string.h>

str new_str (char* contents) {
    str new = { .contents = contents, .capacity = strlen (contents), .last_pos = strlen (contents) };
    return new;
}

str_array new_str_array () {

    str_array new = {
        .strings  = sml_alloc (1, sizeof (str)),
        .last_pos = 1,
        .capacity = 1,
    };
    new.strings[0] = new_str ("UNINITIALIZED_ARRAY");
    return new;
}

void free_string_array (str_array* array) {
    for (size_t i = 0; i < array->last_pos; i++) {
        free (array->strings[i].contents);
    }
}

void append_str_array (str_array* array, str to_append) {

    if (array->last_pos == array->capacity) {
        array->capacity *= 2;
        array->strings =
        (str*)sml_realloc (array->strings, array->capacity * sizeof (str));
    }

    array->strings[array->last_pos++] = to_append;
}

void double_str_capacity (str* str) {
    str->capacity += 2;
    str->contents = (char*)realloc (str->contents, str->capacity * sizeof (char));
}

// this function frees char* contents
void append_to_str (str* source, char* contents, size_t char_size) {
    if (source->capacity < source->capacity + char_size) {
        double_str_capacity (source);
    }

    strcat (source->contents, contents);
    free (contents);
}
void debug_print_str (const str* s) {
    printf ("String Contents: %s\n", s->contents);
    printf ("Capacity: %zu\n", s->capacity);
    printf ("Last Position: %zu\n", s->last_pos);
}

char* get_portion_of_string (const char* input, int start, int length) {
    if (input == NULL || start < 0 || length < 0) {
        throw_error (SEMANTIC_ERROR, "you cannot invalid request of substring", true);
    }

    int inputLength = strlen (input);

    if (start >= inputLength || start + length > inputLength) {
        throw_error (SEMANTIC_ERROR, "you cannot invalid request of substring", true);
        // Handle start index beyond the string's length
    }

    char* result = (char*)sml_alloc (length + 1, sizeof (char)); // +1 for the null terminator


    strncpy (result, input + start, length);
    result[length] = '\0'; // Null-terminate the result string

    return result;
}
