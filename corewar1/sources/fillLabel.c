#include "../headers/fillLabel.h"

bool fillLabel(codeStruct** codeHeader, labelStruct** head)
{
    labelStruct* labelTemp = NULL;
    codeStruct* codeTemp = *codeHeader;
    while (codeTemp != NULL)
    {
        bool isLabel1 = false;
        bool isLabel2 = false;
        bool isLabel3 = false;
        labelTemp = *head;
        if (strlen(codeTemp->label1) != 0) isLabel1 = true;
        if (strlen(codeTemp->label2) != 0) isLabel2 = true;
        if (strlen(codeTemp->label3) != 0) isLabel3 = true;
        if ((!isLabel1) && (!isLabel2) && (!isLabel3))
        {
            codeTemp = codeTemp->next;
            continue;
        }
        while (labelTemp != NULL)
        {
            if (strcmp(labelTemp->name, codeTemp->label1) == 0)
            {
                getLabelAddress(&labelTemp->totalMemory, &codeTemp->arg1,
                                &codeTemp->thisCodeSize,
                                &codeTemp->codeTotalSize);
                isLabel1 = false;
            }
            if (strcmp(labelTemp->name, codeTemp->label2) == 0)
            {
                getLabelAddress(&labelTemp->totalMemory, &codeTemp->arg2,
                                &codeTemp->thisCodeSize,
                                &codeTemp->codeTotalSize);
                isLabel2 = false;
            }
            if (strcmp(labelTemp->name, codeTemp->label3) == 0)
            {
                getLabelAddress(&labelTemp->totalMemory, &codeTemp->arg3,
                                &codeTemp->thisCodeSize,
                                &codeTemp->codeTotalSize);
                isLabel3 = false;
            }
            labelTemp = labelTemp->next;
        }
        if (!isInLabelList(isLabel1, isLabel2, isLabel3, codeTemp))
        {
            return false;
        }
        codeTemp = codeTemp->next;
    }
    return true;
}

bool isInLabelList(bool isLabel1, bool isLabel2, bool isLabel3,
                   codeStruct* codeTemp)
{
    if (isLabel1)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], the label does not exist.\n", RED,
                RESET, YELLOW, codeTemp->arg1, RESET);
        return false;
    }
    if (isLabel2)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], the label does not exist.\n", RED,
                RESET, YELLOW, codeTemp->arg2, RESET);
        return false;
    }
    if (isLabel3)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], the label does not exist.\n", RED,
                RESET, YELLOW, codeTemp->arg3, RESET);
        return false;
    }
    return true;
}

void getLabelAddress(int* labelTotalMemory, int* codeArg, int* thisCodeSize,
                     int* codeTotalSize)
{
    *codeArg = *labelTotalMemory - (*codeTotalSize - *thisCodeSize);
}