#include "../headers/linkedList.h"

labelStruct* getNewLabel(char** label, int* totalCodeSize)
{
    labelStruct* newLabel = (labelStruct*)malloc(sizeof(labelStruct));
    newLabel->name = getString(strlen(*label) + 1);
    newLabel->totalMemory = *totalCodeSize;
    newLabel->next = NULL;
    for (int i = 0; (*label)[i] != '\0'; i++) newLabel->name[i] = (*label)[i];
    return newLabel;
}

void AppendLabel(labelStruct** head, char** label, int* totalCodeSize)
{
    labelStruct* temp = getNewLabel(label, totalCodeSize);
    if (*head == NULL)
        *head = temp;
    else
    {
        labelStruct* tempLoop = *head;
        while (tempLoop->next != NULL)
        {
            tempLoop = tempLoop->next;
        }
        tempLoop->next = temp;
    }
}

void freeLabelList(labelStruct** head)
{
    labelStruct* tempLoop = *head;
    labelStruct* toDelete = *head;
    while (tempLoop != NULL)
    {
        toDelete = tempLoop;
        tempLoop = tempLoop->next;
        free(toDelete->name);
        free(toDelete);
    }
}

void freeCode(codeStruct** codeHeader)
{
    codeStruct* tempLoop = *codeHeader;
    codeStruct* toDelete = *codeHeader;
    while (tempLoop != NULL)
    {
        toDelete = tempLoop;
        tempLoop = tempLoop->next;
        free(toDelete->label1);
        free(toDelete->label2);
        free(toDelete->label3);
        free(toDelete);
    }
}

void initHeaderCode(codeStruct** codeHeader, int* totalCodeSize)
{
    codeStruct* temp = getNewCode(totalCodeSize);
    if (*codeHeader == NULL)
        *codeHeader = temp;
    else
    {
        codeStruct* tempLoop = *codeHeader;
        while (tempLoop->next != NULL)
        {
            tempLoop = tempLoop->next;
        }
        tempLoop->next = temp;
    }
}

codeStruct* getNewCode(int* totalCodeSize)
{
    codeStruct* newCode = (codeStruct*)malloc(sizeof(codeStruct));
    newCode->label1 = getString(INIT_MEM + 1);
    newCode->label2 = getString(INIT_MEM + 1);
    newCode->label3 = getString(INIT_MEM + 1);
    newCode->code = 0;
    newCode->arg1 = 0;
    newCode->arg2 = 0;
    newCode->arg3 = 0;
    newCode->argSize1 = 0;
    newCode->argSize2 = 0;
    newCode->argSize3 = 0;
    newCode->thisCodeSize = 0;
    newCode->codeType = 0;
    newCode->codeTotalSize = *totalCodeSize;
    newCode->next = NULL;
    return newCode;
}