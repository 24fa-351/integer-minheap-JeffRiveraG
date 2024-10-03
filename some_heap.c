#include <stdio.h>
#include <stdlib.h>
#include "some_heap.h"

#define KEY_NOT_PRESENT -1

extern FILE *output_file;

heap_t *heap_create(int capacity) {
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    if (heap == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    heap->data = (heap_node_t *)malloc(capacity * sizeof(heap_node_t));
    if (heap->data == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        free(heap);
        exit(1);
    }

    heap->capacity = capacity;
    heap->size = 0;

    return heap;
}

void heap_free(heap_t *heap) {
    free(heap->data);
    free(heap);
}

unsigned int heap_size(heap_t *heap) {
    return heap->size;
}

unsigned int heap_parent(unsigned int index) {
    return (index - 1) / 2;
}

unsigned int heap_left_child(unsigned int index) {
    return (index * 2) + 1;
}

unsigned int heap_right_child(unsigned int index) {
    return (index * 2) + 2;
}

unsigned int heap_level(unsigned int index) {
    int level = 0;
    while (index > 0) {
        index = heap_parent(index);
        level++;
    }
    return level;
}

void heap_print(heap_t *heap) {
    for (int ix = 0; ix < heap_size(heap); ix++) {
        fprintf(output_file, "%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix, heap->data[ix].key);
    }
    fprintf(output_file, "\n");
}

void heap_swap(heap_t *heap, int index1, int index2) {
    heap_node_t temp = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = temp;
}

void heap_bubble_up(heap_t *heap, int index) {
    while (index > 0 && heap->data[heap_parent(index)].key > heap->data[index].key) {
        heap_swap(heap, index, heap_parent(index));
        index = heap_parent(index);
    }
}

void heap_bubble_down(heap_t *heap, int index) {
    while (heap_left_child(index) < heap->size) {
        int smallest = heap_left_child(index);
        if (heap_right_child(index) < heap->size && heap->data[heap_right_child(index)].key < heap->data[smallest].key) {
            smallest = heap_right_child(index);
        }
        if (heap->data[index].key <= heap->data[smallest].key) {
            break;
        }
        heap_swap(heap, index, smallest);
        index = smallest;
    }
}

void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data) {
    if (heap_size(heap) == heap->capacity) {
        return;
    }

    heap->data[heap_size(heap)].key = key;
    heap->data[heap_size(heap)].value = data;
    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);
}

heap_value_t heap_remove_min(heap_t *heap) {
    if (heap_size(heap) == 0) {
        return (heap_value_t){.as_int = KEY_NOT_PRESENT};
    }

    heap_value_t min = heap->data[0].value;

    heap->size--;
    heap->data[0] = heap->data[heap_size(heap)];

    heap_bubble_down(heap, 0);

    return min;
}
