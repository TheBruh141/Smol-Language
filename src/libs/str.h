#ifndef STR_H_
#define STR_H_

#include <stddef.h>
// a pretty standard string representation

// if you want to optimize the str library go ahead but because of time
// constraints I cannot right now...

typedef struct {
    char* contents;
    size_t capacity;
    size_t last_pos;
} str;

typedef struct {
    str* strings;
    size_t last_pos;
    size_t capacity;
} str_array;

#pragma region prototypes

str new_str (char* contents);
str_array new_str_array ();
void free_string_array (str_array* array);
// can overwrite existing strings

void str_array_add (str_array* array, str appendee);
void append_str_array (str_array* array, str to_append);
void double_str_capacity (str* str);

void append_to_str (str* source, char* contents, size_t char_size);


char* get_portion_of_string (const char* input, int start, int length);

#pragma endregion prototypes
void debug_print_str (const str* s);

#endif // STR_H_
