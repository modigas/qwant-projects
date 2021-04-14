#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdbool.h>

struct node
{
    int data;
    struct node *next;
};

struct stack
{
    struct node *head;
    struct node *cursor;
    size_t members;

    void (*const destroy)(struct stack *self);
    void (*const push)(struct stack *self, int data);
    bool (*const empty)(struct stack *self);
    int (*const top)(struct stack *self);
    size_t (*const size)(struct stack *self);
    void (*const pop)(struct stack *self);
};

extern const struct stackClass
{
    struct stack (*new)();
} stack;

#endif