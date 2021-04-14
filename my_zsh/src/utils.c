#include <utils.h>

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

bool isInt(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    else
        return false;
}

char** my_strtok(char* string, char delim)
{
    int count = 0;
    for (int i = 0; string[i] != '\0'; i++)
        if (string[i] == delim) count += 1;
    unsigned int stringSize = INIT_SIZE;
    char** output = (char**)malloc(sizeof(char*) * (count + 2));
    output[0] = getString(stringSize);
    int j = 0;
    int k = 0;
    for (int i = 5; string[i] != '\0'; i++)
    {
        if (string[i] == delim)
        {
            output[j] = realloc(output[j], sizeof(char) * (k + 1));
            output[j][k] = '\0';
            j += 1;
            k = 0;
            i += 1;
            output[j] = getString(stringSize);
        }
        output[j][k] = string[i];
        k += 1;
    }
    output[j + 1] = NULL;
    return output;
}

char** copyEnvi(char*** env)
{
    int numArgs = 0;
    for (; (*env)[numArgs] != NULL; numArgs++)
        ;
    char** copy = (char**)malloc((numArgs + 1) * sizeof(char*));
    int i = 0;
    for (; i < numArgs; i++)
    {
        copy[i] = (char*)malloc(strlen((*env)[i]) + 1);
        strcpy(copy[i], (*env)[i]);
    }
    copy[i] = NULL;
    return copy;
}