
#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>

// a min heap

typedef union heap_val {
    unsigned long long as_int;
    void *as_ptr;
} heap_value_t;

typedef unsigned long long heap_key_t;
//typedef void* heap_value_t;
#define HEAP_KEY_FORMAT "%llu"

typedef struct {
    heap_key_t key;
    heap_value_t value;
} heap_node_t;

typedef struct {
    heap_node_t *data;
    int size;
    int capacity;
} heap_t;

extern FILE *output_file;

heap_t *heap_create(int capacity);

void heap_free(heap_t *heap);

unsigned int heap_size(heap_t *heap);

void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data);

heap_value_t heap_remove_min(heap_t *heap);

void heap_print(heap_t *heap);

#endif
