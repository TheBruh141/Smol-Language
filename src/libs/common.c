#include "common.h"
#include "errors.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void *sml_malloc(size_t size) {

  // write a secure malloc
  void *new_mem = malloc(size);
  if (new_mem == NULL) {
    throw_error(MEMORY_ALLOCATION_ERROR, "failed to allocate memory", true);
  }
  return new_mem;
}

void *sml_calloc(size_t new_mem, size_t size) {

  void *void_pointer = calloc(new_mem, size);
  if (void_pointer == NULL) {
    throw_error(MEMORY_ALLOCATION_ERROR,
                "memory allocation failed in sml_calloc", true);
  }
  return void_pointer;
}

void *sml_realloc(void *p, unsigned long new_mem) {
  void *new_ptr = realloc(p, new_mem);

  if (new_ptr == NULL ) {
    throw_error(MEMORY_ALLOCATION_ERROR, "realloc failed", true);
    exit(EXIT_FAILURE); // You can handle the error differently if needed
  }

  return new_ptr;
}

void *sml_alloc(size_t new_mem, size_t size) {
  if (new_mem * size > LONG_MAX) {
    throw_error(INTERNAL_ERROR,
                "too big of a size of sml_alloc all sizes must be smaller "
                "than size_t_max or LONG_MAX",
                true);
  } else {
    void *ret = sml_malloc(new_mem * size);
    return ret;
  }
  return (void *)0xDEAD; 
}

char *read_file(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    throw_error(IO_ERROR, "File not found", true);
    return NULL;
  }

  fseek(fp, 0, SEEK_END);
  size_t size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *buffer = calloc(size + 1, sizeof(char));
  if (buffer == NULL) {
    throw_error(IO_ERROR, "Memory allocation failed", true);
    fclose(fp);  // Close the file before returning
    return NULL;
  }

  fread(buffer, sizeof(char), size, fp);
  buffer[size] = '\0';

  fclose(fp);
  return buffer;
}
