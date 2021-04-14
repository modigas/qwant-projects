#include "../headers/readFile.h"

bool readFile(int* fd, char** fileContent)
{
    int readLength = 0;
    int totalReadLength = 0;
    int memory = INIT_MEM;
    char buff[READ_SIZE + 1] = {'\0'};
    *fileContent = getString(memory);
    while (true)
    {
        readLength = read(*fd, buff, READ_SIZE);
        totalReadLength += readLength;
        incStringMemory(fileContent, &memory, &totalReadLength);
        if (readLength != 0) strcat(*fileContent, buff);
        for (int i = 0; i < READ_SIZE + 1; i++) buff[i] = '\0';
        if (readLength == 0) break;
    }
    if (totalReadLength == 0)
    {
        fprintf(stderr, "%sError:%s The file is empty.\n", RED, RESET);
        return false;
    }
    else
    {
        return true;
    }
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
