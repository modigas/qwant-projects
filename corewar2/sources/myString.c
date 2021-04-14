#include "../headers/myString.h"

bool isInt(char c)
{
    if ((c >= '0') && (c <= '9'))
        return true;
    else
        return false;
}

bool isStrInt(char* string)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (!isInt(string[i]))
        {
            return false;
        }
    }
    return true;
}

void strToDec(char* string, int* number)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        *number += string[i] - '0';
        *number *= 10;
    }
    *number /= 10;
}

void incStringMemory(char** string, int* currentMemory, int* futureMemory)
{
    while (*futureMemory >= *currentMemory)
    {
        *currentMemory += INIT_MEM;
        *string = (char*)realloc(*string, *currentMemory);
        initString(string, *currentMemory - INIT_MEM, *currentMemory);
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