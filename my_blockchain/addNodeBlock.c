#include "addNodeBlock.h"

bool isInt(char** string)
{
    bool checkInt = false;
    for (int i = 0; (*string)[i] != '\0'; i++)
    {
        if (((*string)[i] >= '0') && ((*string)[i] <= '9')) checkInt = true;
    }
    return checkInt;
}

int strToNum(char* string)
{
    int length = strlen(string);
    int digit = 0;
    int result = 0;
    for (int i = 0; i < length; i++)
    {
        result *= 10;
        digit = string[i] - '0';
        result += digit;
    }
    return result;
}

void insertNid(BstNode** root, int nid)
{
    if (*root == NULL)
    {
        *root = getNewNode(nid);
        printf("The node %d successfully added\n", nid);
    }
    else if ((*root)->nid > nid)
    {
        return insertNid(&(*root)->left, nid);
    }
    else if ((*root)->nid < nid)
    {
        return insertNid(&(*root)->right, nid);
    }
    else
    {
        fprintf(stderr, "The node %d already exist\n", nid);
    }
}

BstNode* getNewNode(int nid)
{
    BstNode* NewNode = (BstNode*) malloc(sizeof(BstNode));
    NewNode->nid = nid;
    NewNode->bid = NULL;
    NewNode->left = NULL;
    NewNode->right = NULL;
    return NewNode;
}

void insertBlockToAllNids(BstNode** root, char** bids)
{
    if (*root == NULL) return;
    insertBlockToAllNids(&(*root)->left, &(*bids));
    insertBlock(&(*root)->bid, &(*bids));
    insertBlockToAllNids(&(*root)->right, &(*bids));
}

void insertBlock(Node** root, char** bids)
{
    if ((*root == NULL) || (strcmp((*root)->string, *bids) > 0))
    {
        printf("The block %s successfully added\n", *bids);
        Node* temp = getNewBlock(bids);
        temp->next = *root;
        *root = temp;
    }
    else
    {
        Node* current = *root;
        while ((current->next != NULL) && (strcmp((current->next)->string, *bids) < 0))
        {
            current = current->next;
        }
        if ((strcmp(current->string, *bids) == 0) ||
           ((current->next != NULL) && (strcmp((current->next)->string, *bids)) == 0))
        {
            fprintf(stderr, "The block %s already exist\n", *bids);
            return;
        }
        printf("The block %s successfully added\n", *bids);
        Node* temp = getNewBlock(bids);
        temp->next = current->next;
        current->next = temp;
    }
}

Node* getNewBlock(char** bid)
{
    Node* NewNode = (Node*) malloc(sizeof(Node));
    getNewString(&NewNode->string, 0, strlen(*bid) + 1);
    for (int i = 0; (*bid)[i] != '\0'; i++)
        NewNode->string[i] = (*bid)[i];
    return NewNode;
}

BstNode* searchNid(BstNode** root, int nid)
{
    if (*root == NULL) return NULL;
    else if ((*root)->nid == nid) return *root;
    else if ((*root)->nid > nid) return searchNid(&(*root)->left, nid);
    else return searchNid(&(*root)->right, nid);
}

void insertBlockS(Node** root, char** bids)
{
    if ((*root == NULL) || (strcmp((*root)->string, *bids) > 0))
    {
        Node* temp = getNewBlock(bids);
        temp->next = *root;
        *root = temp;
    }
    else
    {
        Node* current = *root;
        while ((current->next != NULL) && (strcmp((current->next)->string, *bids) < 0))
        {
            current = current->next;
        }
        if ((strcmp(current->string, *bids) == 0) ||
           ((current->next != NULL) && (strcmp((current->next)->string, *bids)) == 0))
        {
            return;
        }
        Node* temp = getNewBlock(bids);
        temp->next = current->next;
        current->next = temp;
    }
}

void insertNidS(BstNode** root, int nid)
{
    if (*root == NULL)
    {
        *root = getNewNode(nid);
    }
    else if ((*root)->nid > nid)
    {
        return insertNidS(&(*root)->left, nid);
    }
    else if ((*root)->nid < nid)
    {
        return insertNidS(&(*root)->right, nid);
    }
}