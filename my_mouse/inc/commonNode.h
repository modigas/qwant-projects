#ifndef COMMON_NODE_H
#define COMMON_NODE_H

struct point
{
    int x;
    int y;
};

struct node
{
    struct point key;
    struct point location;
    struct node* next;
};

#endif