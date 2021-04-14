#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <commonNode.h>

#define TABLE_SIZE 1000000

struct hash
{
    struct node *hashTable[TABLE_SIZE];

    void (*const insert)(struct hash *self, struct point key,
                         struct point location);
    struct point (*const find)(struct hash *self, struct point location);
    void (*const delete)(struct hash *self, struct point location);
    void (*const destroy)(struct hash *self);
    struct point (*const end)();
    void (*const print)(struct hash *self);
};

extern const struct hashClass
{
    struct hash (*new)();
} hash;

#endif