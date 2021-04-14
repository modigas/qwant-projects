#include "../headers/cursors.h"
#include "../headers/libs.h"
#include "../headers/structs.h"

cursor* getNewCursor(int params[NUM_PARAMETERS])
{
    cursor* newCursor = (cursor*)malloc(sizeof(cursor));
    for(int i = 0; i < NUM_PARAMETERS; i++)
        newCursor->parameters[i] = params[i];
    newCursor->next = NULL;
    return newCursor;
}

// cursor* pushCursor(cursor* head, int params[NUM_PARAMETERS])
// {
//     if(head == NULL)
//     {
//         head = getNewCursor(params);
//         return head;
//     }
//     cursor* curr = head;
//     while(curr->next != NULL)
//     {
//         curr = curr->next;
//     }
//     curr->next = getNewCursor(params);
//     return curr;
// }

void pushCursor(cursor** head, int params[NUM_PARAMETERS])
{
    if(*head == NULL)
    {
        *head = getNewCursor(params);
        return;
    }
    cursor* curr = *head;
    while(curr -> next != NULL)
    {
        curr = curr -> next;
    }
    curr -> next = getNewCursor(params);
    // while((*head)->next != NULL)
    //     (*head) = (*head)->next;
    // (*head)->next = getNewCursor(params);
}

int searchCursor(cursor** head, int params[NUM_PARAMETERS])
{
    if(*head == NULL) return 0;
    int pos = 0;
    int cond = 0;
    while((*head)->next != NULL)
    {
        for(int i = 0; i < NUM_PARAMETERS; i++)
        {
            if((*head)->parameters[i] != params[i])
            {
                cond = 1;
                break;
            }
            else cond = 0;
                
        }
        if(cond != 1) break;
        (*head) = (*head)->next;
        pos++;

    }
    return pos;
}

void deleteCursor(cursor** head, int pos)
{
    if(*head == NULL) return;
    cursor* curr = *head;
    if(pos == 0)
    {
        *head = curr->next;
        free(curr);
        return;
    }
    int iter = 0;
    for(int i = 0; i < pos-1 && curr != NULL; i++)
        curr = curr->next;
    if(curr == NULL || curr->next == NULL)
        return;
    cursor* next = curr->next->next;
    free(curr->next);
    curr->next = next;
}

void initCursor(cursor* cr)
{
    if(cr == NULL) return;
    for(int i = NUM_PARAMETERS - REG_NUMBER - 1; i < NUM_PARAMETERS; i++)
    {
        cr->parameters[i] = 0;
    }
}

void initCursors(cursor** head)
{
    if(*head == NULL) return;
    while((*head)->next != NULL)
    {
        initCursor(*head);
        (*head) = (*head)->next;
    }
}

void freeCursors(cursor* head)
{
    if(head == NULL) return;
    cursor* curr;
    while(curr != NULL)
    {
        curr = head;
        head = head->next;
        free(curr);
    }
}

void free2(cursor* head)
{
    if(head == NULL) return;
    cursor* next, *to_free;
    next = head;
    while(next != NULL)
    {
        to_free = next;
        next = next -> next;
        free(to_free);
    }
}

void printCursors(cursor** head)
{
    if(*head == NULL) return;
    cursor* curr = *head;
    while(curr != NULL)
    {
        for(int i = 0; i < NUM_PARAMETERS; i++)
            printf("%d ", curr->parameters[i]);
        printf("\n");
        curr = curr -> next;
    }
}

// cursor* srchCursor(cursor* head, int params[NUM_PARAMETERS])
// {
//     if(head == NULL) return head;
//     cursor* curr = head;
//     int cond = 0;
//     while(curr->next != NULL)
//     {
//         for(int i = 0; i < NUM_PARAMETERS; i++)
//         {
//             if(curr->parameters[i] != params[i])
//             {

//                 break;
//             }
//         }
//     }
//     return curr;
// }
