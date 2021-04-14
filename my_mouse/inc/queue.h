#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <commonNode.h>
/*
struct xy
{
    int x;
    int y;
};*/

struct queue
{
    struct node *head;
    struct node *cursor;
    size_t members;

    void (*const destroy)(struct queue *self);
    void (*const put)(struct queue *self, struct point location);
    bool (*const isEmpty)(struct queue *self);
    struct point (*const front)(struct queue *self);
    void (*const pop)(struct queue *self);
    size_t (*const size)(struct queue *self);
};

extern const struct queueClass
{
    struct queue (*new)();
} queue;

#endif