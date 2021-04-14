#include "fillInput.h"

void readInput(CommandContainer* Inputs, bool* isError)
{
    bool newLine = false;
    int totalRead = 0;
    int memory = INIT_SIZE;
    char readBuff[READ_SIZE + 1];
    readBuff[READ_SIZE] = '\0';
    char* lineString;
    getNewString(&lineString, 0, memory);

    while (1)
    {
        int currentRead = read(STDIN_FILENO, readBuff, READ_SIZE);
        totalRead += currentRead;
        for (int i = totalRead - currentRead, j = 0; i < totalRead; i++, j++)
            lineString[i] = readBuff[j];
        memoryRealloc(&lineString, &memory, totalRead);
        for (int i = 0; i < currentRead; i++)
        {
            if (readBuff[i] == '\n')
            {
                newLine = true;
                break;
            }
        }
        if (newLine) break;
    }
    fillContainer(lineString, &Inputs, &(*isError));
    free(lineString);
}

void fillContainer(char* lineString, CommandContainer** Inputs, bool* isError)
{
    int i = 0;
    int j = 0;
    int elemNum = 0;
    int format = 0;
    int memory = INIT_SIZE;
    int arrayMemory = ARRAY_SIZE;
    char** temp = (char**)malloc(arrayMemory * sizeof(char*));
    getNewString(&temp[elemNum], 0, memory);
    (*Inputs)->type = NONE;
    (*Inputs)->action = NONE_ACT;
    (*Inputs)->count = 0;
    *isError = false;

    if (lineString[i] == ' ') i = skipSpace(lineString, i);
    while (lineString[i] != '\0')
    {
        if ((lineString[i] != ' ') && (lineString[i] != '\n'))
        {
            memoryRealloc(&temp[elemNum], &memory, i);
            temp[elemNum][j++] = lineString[i++];
        }
        else if (format < 2)
        {
            switch (format++)
            {
                case 0:
                    getActions(&(*Inputs), temp[elemNum], &(*isError));
                    if (*isError) break;
                    initializeString(&temp[elemNum], 0, 6);
                    j = 0;
                    i = skipSpace(lineString, i);
                    break;
                case 1:
                    getTypes(&(*Inputs), temp[elemNum], &(*isError));
                    if (*isError) break;
                    initializeString(&temp[elemNum], 0, 6);
                    j = 0;
                    elemNum++;
                    getNewString(&temp[elemNum], 0, memory);
                    i = skipSpace(lineString, i);
                    break;
                default:
                    break;
            }
        }
        else
        {
            if (((*Inputs)->action == ADD) || ((*Inputs)->action == RM))
            {
                j = 0;
                elemNum++;
                getNewString(&temp[elemNum], 0, memory);
                i = skipSpace(lineString, i);
            }
        }
        if (*isError) break;

        if (elemNum + 1 >= arrayMemory)
        {
            arrayMemory += arrayMemory;
            temp = (char**)realloc(temp, arrayMemory * sizeof(char*));
        }
    }

    if (elemNum - 1 >= 0)
    {
        free(temp[elemNum]);
        if (temp[elemNum - 1][0] == '\0')
        {
            elemNum -= 2;
        }
        else
        {
            elemNum--;
        }
    }

    if ((*Inputs)->type == NODE)
        fillNode(&(*Inputs), &temp, elemNum);
    else if ((*Inputs)->type == BLOCK)
        fillBlock(&(*Inputs), &temp, elemNum);

    if (((*Inputs)->action == LS) || ((*Inputs)->action == SYNC) ||
        ((*Inputs)->action == QUIT))
        (*Inputs)->count = 1;

    free(temp[0]);
    free(temp);
}

void getActions(CommandContainer** Inputs, char* temp, bool* isError)
{
    if (strcmp(temp, "add") == 0)
        (*Inputs)->action = ADD;
    else if (strcmp(temp, "rm") == 0)
        (*Inputs)->action = RM;
    else if (strcmp(temp, "ls") == 0)
        (*Inputs)->action = LS;
    else if (strcmp(temp, "sync") == 0)
        (*Inputs)->action = SYNC;
    else if (strcmp(temp, "quit") == 0)
        (*Inputs)->action = QUIT;
    else
    {
        printf("Command not found\n");
        *isError = true;
    }
}

void getTypes(CommandContainer** Inputs, char* temp, bool* isError)
{
    if (strcmp(temp, "node") == 0)
        (*Inputs)->type = NODE;
    else if (strcmp(temp, "block") == 0)
        (*Inputs)->type = BLOCK;
    else if ((strcmp(temp, "-l") == 0) && ((*Inputs)->action == LS))
        (*Inputs)->type = L;
    else if (((*Inputs)->action == SYNC) || ((*Inputs)->action == QUIT) ||
             ((*Inputs)->action == LS))
        (*Inputs)->type = NONE;
    else
    {
        printf("Command not found\n");
        *isError = true;
    }
}

void fillNode(CommandContainer** Inputs, char*** temp, int elemNum)
{
    if (((*Inputs)->action == ADD) || ((*Inputs)->action == RM))
    {
        (*Inputs)->nids = (char**)malloc(elemNum * sizeof(char*));
        for (int i = 1; i <= elemNum; i++)
        {
            int j = 0;
            getNewString(&(*Inputs)->nids[i - 1], 0, strlen((*temp)[i]) + 1);
            while ((*temp)[i][j] != '\0')
            {
                (*Inputs)->nids[i - 1][j] = (*temp)[i][j];
                j++;
            }
            free((*temp)[i]);
        }
    }
    else
    {
        printf("Error\n");
    }
    (*Inputs)->count = elemNum;
}

void fillBlock(CommandContainer** Inputs, char*** temp, int elemNum)
{
    if ((*Inputs)->action == ADD)
    {
        int j = 0;
        (*Inputs)->bids = (char**)malloc(sizeof(char*));
        getNewString(&(*Inputs)->bids[0], 0, strlen((*temp)[1]) + 1);
        if (elemNum > 1)
            (*Inputs)->nids = (char**)malloc((elemNum - 1) * sizeof(char*));
        while ((*temp)[1][j] != '\0')
        {
            (*Inputs)->bids[0][j] = (*temp)[1][j];
            j++;
        }
        free((*temp)[1]);
        for (int i = 2; i <= elemNum; i++)
        {
            j = 0;
            getNewString(&(*Inputs)->nids[i - 2], 0, strlen((*temp)[i]) + 1);
            while ((*temp)[i][j] != '\0')
            {
                (*Inputs)->nids[i - 2][j] = (*temp)[i][j];
                j++;
            }
            free((*temp)[i]);
        }
    }
    else if ((*Inputs)->action == RM)
    {
        (*Inputs)->bids = (char**)malloc(elemNum * sizeof(char*));
        for (int i = 1; i <= elemNum; i++)
        {
            int j = 0;
            getNewString(&(*Inputs)->bids[i - 1], 0, strlen((*temp)[i]) + 1);
            while ((*temp)[i][j] != '\0')
            {
                (*Inputs)->bids[i - 1][j] = (*temp)[i][j];
                j++;
            }
            free((*temp)[i]);
        }
    }
    else
    {
        printf("Error\n");
    }
    (*Inputs)->count = elemNum;
}

void initializeString(char** string, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        (*string)[i] = '\0';
    }
}

void getNewString(char** string, int start, int end)
{
    (*string) = (char*)malloc(end);
    initializeString(&(*string), 0, end);
}

void memoryRealloc(char** buff, int* memory, int excessSize)
{
    int start = 0;
    while (excessSize + 1 >= *memory)
    {
        start = *memory;
        *memory += *memory;
        (*buff) = (char*)realloc((*buff), *memory);
        initializeString(&(*buff), start, *memory);
    }
}

int skipSpace(char* string, int i)
{
    int check = i;
    while (string[i] == ' ') i++;
    if (check == i)
        return i + 1;
    else
        return i;
}