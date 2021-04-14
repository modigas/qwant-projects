#include "stateAndSync.h"

void printState(int fd, State* CurrentState)
{
    char sync;
    if (CurrentState->sync)
        sync = 's';
    else
        sync = '-';
    printf("[%c%d]>", sync, CurrentState->size);
    fflush(stdout);
}

void insertBlockW(Node** root, char** bids)
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
        while ((current->next != NULL) &&
               (strcmp((current->next)->string, *bids) < 0))
        {
            current = current->next;
        }
        if ((strcmp(current->string, *bids) == 0) ||
            ((current->next != NULL) &&
             (strcmp((current->next)->string, *bids)) == 0))
        {
            return;
        }
        Node* temp = getNewBlock(bids);
        temp->next = current->next;
        current->next = temp;
    }
}

void copyBlocks(Node** destBids, Node** bids)
{
    Node* tempBids = *bids;
    while (tempBids != NULL)
    {
        insertBlockW(&(*destBids), &tempBids->string);
        tempBids = tempBids->next;
    }
}

void collectBids(BstNode** root, Node** tempList)
{
    if (*root == NULL) return;
    copyBlocks(&(*tempList), &(*root)->bid);
    collectBids(&(*root)->left, &(*tempList));
    collectBids(&(*root)->right, &(*tempList));
}

void syncBids(BstNode** root, Node** tempList)
{
    if (*root == NULL) return;
    copyBlocks(&(*root)->bid, &(*tempList));
    syncBids(&(*root)->left, &(*tempList));
    syncBids(&(*root)->right, &(*tempList));
}

void printTree(BstNode** root, int type)
{
    if (*root == NULL) return;
    printTree(&(*root)->left, type);
    printf("Node: %d \n", (*root)->nid);
    if (type == L) printLinkedList(&(*root)->bid);
    printTree(&(*root)->right, type);
}

void printLinkedList(Node** bid)
{
    Node* temp = *bid;
    printf("    Blocks: ");
    while (temp != NULL)
    {
        printf("%s ", temp->string);
        temp = temp->next;
    }
    printf("\n");
}

void syncCheck(BstNode** root, Node** bid, State* CurrentState, bool* isTrueSync)
{
    if (*root == NULL) return;
    CurrentState->sync = compareBlock(&(*root)->bid, &(*bid));
    if (!CurrentState->sync) *isTrueSync = false;
    CurrentState->size++;
    syncCheck(&(*root)->left, &(*root)->bid, &(*CurrentState), &(*isTrueSync));
    syncCheck(&(*root)->right, &(*root)->bid, &(*CurrentState), &(*isTrueSync));
    if (!(*isTrueSync)) CurrentState->sync = *isTrueSync;
}

bool compareBlock(Node** next, Node** current)
{
    Node* temp1 = *next;
    Node* temp2 = *current;
    while ((temp1 != NULL) && (temp2 != NULL))
    {
        if (strcmp(temp1->string, temp2->string) != 0) return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
        if ((temp1 == NULL) && (temp2 == NULL)) return true;
        else if ((temp1 == NULL) && (temp2 != NULL)) return false;
        else if ((temp2 == NULL) && (temp1 != NULL)) return false;
    }
    return false;
}