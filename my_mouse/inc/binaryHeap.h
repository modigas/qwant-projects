#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXHEAP 100

struct heap
{
    int value;
    int size;
    int* array;
    int maxSize;

    void (*const insert)(struct heap* self, int value);
    int (*const pop)(struct heap* self);
    int (*const peek)(struct heap* self);
    bool (*const isEmpty)(struct heap* self);
};

extern const struct heapClass
{
    struct heap (*new)();
} heap;

#endif