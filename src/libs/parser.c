#include "parser.h"
#include "common.h"
#include "errors.h"
#include "tokenizer.h"
#include <stdio.h>
#include <string.h>


Parse_State* parse_state_new (Parse_State* parent) {
    static uint32_t id = 0;
    Parse_State* state = (Parse_State*)malloc (sizeof (Parse_State));
    state->parent      = parent;
    state->id          = id++;
    state->child_count = 0;
    state->childs      = NULL;
    return state;
}

void free_one_node (Parse_State* state) {
    free (state);
}

void free_children (Parse_State* state) {
    for (uint32_t i = 0; i < state->child_count; i++) {
        free_one_node (state->childs[i]);
    }
    free (state->childs);
}
void parse_state_free (Parse_State* state) {
    free (state);
}
