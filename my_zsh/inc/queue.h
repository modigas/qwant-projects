#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node
{
    char *value;
    struct node *next;
};

struct queue
{
    struct node *head;
    struct node *cursor;
    size_t members;

    void (*const destroy)(struct queue *self);
    void (*const put)(struct queue *self, char *value);
    bool (*const isEmpty)(struct queue *self);
    char *(*const front)(struct queue *self);
    void (*const pop)(struct queue *self);
    size_t (*const size)(struct queue *self);
};

extern const struct queueClass
{
    struct queue (*new)();
} queue;

#endif