#include <hash.h>

static unsigned int hashOperation(struct point location)
{
    /*return (((unsigned int)location.x ^ ((unsigned int)location.y << 4)) %
            TABLE_SIZE);*/
    return ((((location.x + location.y)*(location.x + location.y + 1)) / 2) +
            location.y) % TABLE_SIZE;    
}

static struct point end()
{
    return (struct point){.x = -1, .y = -1};
}

static void print(struct hash *self)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("i[%d]: ", i);
        if (self->hashTable[i] != NULL)
        {
            struct node *temp = self->hashTable[i];
            while (temp != NULL)
            {
                printf("loc[%d][%d] ==> ", temp->location.y, temp->location.x);
                temp = temp->next;
            }
        }
        printf("\n");
    }
}

static void insert(struct hash *self, struct point key, struct point location)
{
    unsigned int index = hashOperation(key);
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->location.x = location.x;
    temp->location.y = location.y;
    temp->key.x = key.x;
    temp->key.y = key.y;
    temp->next = self->hashTable[index];
    self->hashTable[index] = temp;
}

static struct point find(struct hash *self, struct point location)
{
    unsigned int index = hashOperation(location);
    struct node *temp = self->hashTable[index];
    while (temp != NULL && (temp->key.x != location.x ||
           temp->key.y != location.y))
    {
        temp = temp->next;
    }
    if (temp != NULL)
        return temp->location;
    else
        return (struct point){.x = -1, .y = -1};
}

static void delete (struct hash *self, struct point location)
{
    unsigned int index = hashOperation(location);
    struct node *temp = self->hashTable[index];
    struct node *prev = NULL;
    while (temp != NULL && temp->location.x != location.x &&
           temp->location.y != location.y)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        fprintf(stderr, "Error: Member does not exist\n");
        return;
    }
    if (prev == NULL)
    {
        prev = self->hashTable[index];
        self->hashTable[index] = temp->next;
        free(prev);
    }
    else
    {
        prev->next = temp->next;
        free(temp);
    }
}

static void destroy(struct hash *self)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (self->hashTable[i] != NULL)
        {
            struct node *temp = self->hashTable[i];
            struct node *toDelete = NULL;
            while (temp != NULL)
            {
                toDelete = temp;
                temp = temp->next;
                free(toDelete);
            }
        }
    }
}

static struct hash new ()
{
    return (struct hash){.insert = (void *)&insert,
                         .find = (void *)&find,
                         .delete = (void *)&delete,
                         .destroy = (void *)&destroy,
                         .end = (void *)&end,
                         .print = (void *)&print};
}

const struct hashClass hash = {
    .new = &new,
};