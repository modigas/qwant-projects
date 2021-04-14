#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

static void destroy(struct stack *self)
{
    for (struct node *cur = self->head; cur != NULL;)
    {
        struct node *next = cur->next;
        free(cur);
        cur = next;
    }
    self->head = self->cursor = NULL;
    self->members = 0;
}

static void push(struct stack *self, int data)
{
    struct node *newNode = (struct node *)calloc(1, sizeof(struct node));
    assert(newNode);

    newNode->next = self->head;
    newNode->data = data;

    self->head = newNode;
    if (!self->cursor)
    {
        self->cursor = newNode;
    }
    self->members += 1;
}

static bool empty(struct stack *self)
{
    if (self->head == NULL) return true;
    for (struct node *cur = self->head; cur != NULL; cur = cur->next)
    {
        if (cur == NULL) return true;
    }
    return false;
}

static int top(struct stack *self)
{
    if (self->head == NULL)
    {
        fprintf(stderr, "Error: the stack is empty.\n");
        exit(1);
    }
    else
    {
        return self->head->data;
    }
}

static size_t size(struct stack *self)
{
    return self->members;
}

static void pop(struct stack *self)
{
    if (self->head == NULL)
    {
        fprintf(stderr, "Error: the stack is empty.\n");
        exit(1);
    }
    else
    {
        struct node *cur = self->head;
        struct node *next = cur->next;
        free(cur);
        self->head = self->cursor = next;
        self->members -= 1;
    }
}

static struct stack new ()
{
    return (struct stack){.head = NULL,
                          .cursor = NULL,
                          .members = 0,
                          .destroy = (void *)&destroy,
                          .push = (void *)&push,
                          .empty = (void *)&empty,
                          .top = (void *)&top,
                          .size = (void *)&size,
                          .pop = (void *)&pop};
}

const struct stackClass stack = {
    .new = &new,
};