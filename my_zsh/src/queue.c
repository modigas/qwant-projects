#include <queue.h>

static void destroy(struct queue *self)
{
    for (struct node *cur = self->head; cur != NULL;)
    {
        struct node *next = cur->next;
        free(cur->value);
        free(cur);
        cur = next;
    }
    self->head = self->cursor = NULL;
    self->members = 0;
}

static void put(struct queue *self, char *value)
{
    struct node *newNode = (struct node *)calloc(1, sizeof(struct node));
    assert(newNode);

    newNode->next = NULL;
    unsigned int tempLength = strlen(value);
    newNode->value = (char *)malloc(sizeof(char) * (tempLength + 1));
    strcpy(newNode->value, value);

    if (!self->head)
    {
        self->head = newNode;
    }
    else
    {
        self->cursor->next = newNode;
    }
    self->cursor = newNode;
    self->members += 1;
}

static bool isEmpty(struct queue *self)
{
    if (self->head == NULL) return true;
    return false;
}

static char *front(struct queue *self)
{
    if (self->head == NULL)
    {
        fprintf(stderr, "Error: the queue is empty.\n");
        exit(1);
    }
    else
    {
        return self->head->value;
    }
}

static size_t size(struct queue *self)
{
    return self->members;
}

static void pop(struct queue *self)
{
    if (self->head == NULL)
    {
        fprintf(stderr, "Error: the queue is empty.\n");
        exit(1);
    }
    else
    {
        struct node *cur = self->head;
        struct node *next = cur->next;
        free(cur->value);
        free(cur);
        self->head = next;
        self->members -= 1;
    }
}

static struct queue new ()
{
    return (struct queue){.head = NULL,
                          .cursor = NULL,
                          .members = 0,
                          .destroy = (void *)&destroy,
                          .put = (void *)&put,
                          .isEmpty = (void *)&isEmpty,
                          .front = (void *)&front,
                          .size = (void *)&size,
                          .pop = (void *)&pop};
}

const struct queueClass queue = {
    .new = &new,
};