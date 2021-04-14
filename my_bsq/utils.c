#include "utils.h"

void incStringMemory(char** string, int* currentMemory, int* futureMemory)
{
    while (*futureMemory >= *currentMemory)
    {
        *currentMemory += *currentMemory;
        *string = (char*)realloc(*string, *currentMemory);
        (*string)[*currentMemory - 1] = '\0';
    }
}

void initString(char** string, unsigned int from, unsigned int to)
{
    for (unsigned int i = from; i < to; i++)
    {
        (*string)[i] = '\0';
    }
}

char* getString(unsigned int size)
{
    char* string = (char*)malloc(size + 1);
    initString(&string, 0, size);
    return string;
}