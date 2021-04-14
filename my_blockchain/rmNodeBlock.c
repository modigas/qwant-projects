#include "rmNodeBlock.h"

void removeAllNids(BstNode** root)
{
    if (*root == NULL) return;
    removeAllNids(&(*root)->left);
    removeAllNids(&(*root)->right);
    deleteNid(&(*root), (*root)->nid);
}

void deleteNid(BstNode** root, int nid)
{
    if (*root == NULL)
    {
        fprintf(stderr, "The node %d does not exist\n", nid);
        return;
    }
    else if (nid < (*root)->nid) deleteNid(&(*root)->left, nid);
    else if (nid > (*root)->nid) deleteNid(&(*root)->right, nid);
    else
    {
        if (((*root)->left == NULL) && ((*root)->right == NULL))
        {
            deleteAllBlocks(&(*root)->bid);
            printf("The node %d successfully deleted\n", nid);
            free(*root);
            (*root) = NULL;
        }
        else if ((*root)->left == NULL)
        {
            BstNode* temp = *root;
            *root = (*root)->right;
            deleteAllBlocks(&(temp)->bid);
            printf("The node %d successfully deleted\n", nid);
            free(temp);
        }
        else if ((*root)->right == NULL)
        {
            BstNode* temp = *root;
            *root = (*root)->left;
            deleteAllBlocks(&(temp)->bid);
            printf("The node %d successfully deleted\n", nid);
            free(temp);
        }
        else
        {
            BstNode* temp = findMinNode((*root)->right);
            free((*root)->bid);
            (*root)->bid = NULL;
            (*root)->nid = temp->nid;
            Node* delete = temp->bid;
            while (delete != NULL)
            {
                insertBlock(&(*root)->bid, &delete->string);
                delete = delete->next;
            }
            deleteNid(&(*root)->right, temp->nid);
        }
    }
}

void deleteAllBlocks(Node** root)
{
    if (*root == NULL) return;
    else
    {
        Node* temp = *root;
        while (temp != NULL)
        {
            Node* delete = temp;
            temp = temp->next;
            free(delete->string);
            free(delete);
        }
    }
}

BstNode* findMinNode(BstNode* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

void deleteBlock(BstNode** root, char** string)
{
    if (*root == NULL) return;
    deleteBlock(&(*root)->left, &(*string));
    deleteBlock(&(*root)->right, &(*string));
    deleteSingleBlock(&(*root)->bid, &(*string));
}

void deleteSingleBlock(Node** bid, char** string)
{
    if (*bid == NULL)
    {
        return;
    }
    else
    {
        Node* temp = *bid;
        while (temp != NULL)
        {
            if ((temp->next != NULL) && (strcmp((temp->next)->string, *string) == 0))
            {
                Node* delete = temp->next;
                temp->next = (temp->next)->next;
                free(delete->string);
                free(delete);
                printf("The block %s successfully deleted\n", *string);
                break;
            }
            else if ((temp->next == NULL) && (strcmp(temp->string, *string) == 0))
            {
                *bid = NULL;
                free(temp->string);
                free(temp);
                printf("The block %s successfully deleted\n", *string);
                break;
            }
            else if ((temp->next != NULL) && (strcmp(temp->string, *string) == 0))
            {
                *bid = temp->next;
                free(temp->string);
                free(temp);
                printf("The block %s successfully deleted\n", *string);
                break;
            }
            temp = temp->next;
            if (temp == NULL) fprintf(stderr, "The block %s does not exist\n", *string);
        }
    }
}

void removeAllNidsS(BstNode** root)
{
    if (*root == NULL) return;
    removeAllNidsS(&(*root)->left);
    removeAllNidsS(&(*root)->right);
    deleteNidS(&(*root), (*root)->nid);
}

void deleteNidS(BstNode** root, int nid)
{
    if (*root == NULL)
    {
        return;
    }
    else if (nid < (*root)->nid) deleteNidS(&(*root)->left, nid);
    else if (nid > (*root)->nid) deleteNidS(&(*root)->right, nid);
    else
    {
        if (((*root)->left == NULL) && ((*root)->right == NULL))
        {
            deleteAllBlocks(&(*root)->bid);
            free(*root);
            (*root) = NULL;
        }
        else if ((*root)->left == NULL)
        {
            BstNode* temp = *root;
            *root = (*root)->right;
            deleteAllBlocks(&(temp)->bid);
            free(temp);
        }
        else if ((*root)->right == NULL)
        {
            BstNode* temp = *root;
            *root = (*root)->left;
            deleteAllBlocks(&(temp)->bid);
            free(temp);
        }
        else
        {
            BstNode* temp = findMinNode((*root)->right);
            free((*root)->bid);
            (*root)->bid = NULL;
            (*root)->nid = temp->nid;
            Node* delete = temp->bid;
            while (delete != NULL)
            {
                insertBlockS(&(*root)->bid, &delete->string);
                delete = delete->next;
            }
            deleteNidS(&(*root)->right, temp->nid);
        }
    }
}