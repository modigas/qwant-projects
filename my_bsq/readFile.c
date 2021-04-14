#include "readFile.h"

bool readFile(int fd, int ac, char* av, char** string, bitfieldS* map)
{
    if (ac != 2)
    {
        fprintf(stderr, "Error: Follow the format ./my_bsq [file]\n");
        return false;
    }
    if ((fd = open(av, O_RDONLY)) < 0)
    {
        fprintf(stderr, "Error: The file does not exist\n");
        return false;
    }
    if (!readContent(fd, string, map))
    {
        return false;
    }
    return true;
}

bool readContent(int fd, char** string, bitfieldS* map)
{
    int totalReadLength = 0;
    if ((map->rowSize = getRowSize(fd)) == -1)
    {
        fprintf(stderr, "Error: Improper Format\n");
        return false;
    }
    if ((!readSecondLine(fd, string, &totalReadLength)) &&
        (totalReadLength > 0))
    {
        fprintf(stderr, "Error: Improper Format\n");
        return false;
    }
    setupBitfield(map, totalReadLength, string);
    if (map->map[0] == NULL)
    {
        fprintf(stderr, "Error: Unknown symbol\n");
        freeMap(map);
        return false;
    }
    if (!readRest(fd, string, &totalReadLength, map))
    {
        fprintf(stderr, "Error: improper format\n");
        freeMap(map);
        return false;
    }
    if (((totalReadLength + 1) != (map->rowSize * (map->collumnSize + 1))) ||
        (totalReadLength == 0))
    {
        fprintf(stderr, "Error: Size mismatch\n");
        freeMap(map);
        return false;
    }
    return true;
}

int getRowSize(int fd)
{
    int rowSize = 0;
    char* buff = getString(21);
    readFirstLine(fd, &buff);
    if ((rowSize = atoi(buff)) > 0)
    {
        free(buff);
        return rowSize;
    }
    else
    {
        free(buff);
        return -1;
    }
}

bool readFirstLine(int fd, char** buff)
{
    int readLength = 0;
    int totalReadLength = 0;
    for (int i = 0;
         ((readLength = read(fd, &((*buff)[i]), 1)) && ((*buff)[i] != '\n'));
         i++)
    {
        if ((*buff)[i] == '\0')
        {
            return false;
        }
        totalReadLength += readLength;
        if (totalReadLength > 20)
        {
            return false;
        }
    }
    return true;
}

bool readSecondLine(int fd, char** string, int* totalReadLength)
{
    int readLength = 0;
    int initMemory = 100;
    (*string) = getString(initMemory);
    for (int i = 0; ((readLength = read(fd, &((*string)[i]), 1)) &&
                     ((*string)[i] != '\n'));
         i++)
    {
        if ((*string)[i] == '\0')
        {
            return false;
        }
        (*totalReadLength) += readLength;
        if (((*totalReadLength) + 1) > initMemory)
        {
            incStringMemory(string, &initMemory, totalReadLength);
        }
    }
    return true;
}

bool readRest(int fd, char** string, int* totalReadLength, bitfieldS* map)
{
    int readLength = 0;
    int j = 1;
    int initReadIndex = (*totalReadLength) + 1;
    int memory = map->rowSize * (map->collumnSize + 1) + 1 + initReadIndex;
    (*string) = (char*)realloc((*string), memory);
    for (int i = initReadIndex;
         ((readLength = read(fd, &((*string)[i]), initReadIndex)) &&
          ((*string)[i + 1] != '\0'));
         i += initReadIndex, j++)
    {
        if (j >= map->rowSize)
        {
            return false;
        }
        if ((map->map[j] = fillBitfield(map, &((*string)[i]))) == NULL)
        {
            return false;
        }
        (*totalReadLength) += readLength;
    }
    return true;
}