#ifndef STRUCTS_H
#define STRUCTS_H

#define INIT_SIZE 512
#define ARRAY_SIZE 10
#define READ_SIZE 4

// Actions
#define ADD 1
#define RM 2
#define LS 3
#define SYNC 4
#define QUIT 5
#define NONE_ACT 0
// Types
#define NODE 1
#define BLOCK 2
#define L 3
#define NONE 0

typedef struct Node
{
    char* string;
    struct Node* next;
} Node;

typedef struct BstNode
{
    int nid;
    struct Node* bid;
    struct BstNode* left;
    struct BstNode* right;
} BstNode;

typedef struct State
{
    bool sync;
    int size;
} State;

typedef struct CommandContainer
{
    int action;
    int type;
    int count;
    char** nids;
    char** bids;
} CommandContainer;
#endif