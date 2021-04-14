#include <utils.h>

void incStringMemory(char** string, int* currentMemory, int* futureMemory)
{
    while (*futureMemory >= *currentMemory)
    {
        *currentMemory += *currentMemory;
        *string = (char*)realloc(*string, *currentMemory);
        for (int i = *futureMemory; i < *currentMemory; i++)
            (*string)[i] = '\0';
        //(*string)[*currentMemory - 1] = '\0';
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

bool isInt(char c)
{
    if (c >= '0' && c <= '9') return true;
    else return false;
}

char* my_strstr(char *haystack, char *needle)
{
    if (strlen(haystack) == 0 || strlen(needle) == 0 || (strlen(haystack) < strlen(needle)))
        return NULL;
    size_t hi = 0;
    size_t nj = 0;
    while (nj + 1 != strlen(needle))
    {
        if (hi + 1 == strlen(haystack))
            return NULL;
        if (haystack[hi] == needle[nj])
            nj += 1;
        else
            nj = 0;
        hi += 1;
    }
    return &(haystack[hi - nj]);
}

char* my_strchr(char *haystack, char needle)
{
    if (strlen(haystack) == 0)
        return NULL;
    for (size_t i = 0; i < strlen(haystack); i++)
        if (haystack[i] == needle)
            return &(haystack[i]);
    return NULL;
}