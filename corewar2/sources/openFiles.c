#include "../headers/openFiles.h"
#include <fcntl.h>

bool openFiles(fileNames* fileName, champStruct* champions)
{
    for (int i = 0; i < MAX_PLAYERS_NUMBE; i++)
    {
        champions->code = NULL;
    }
    if (!isFileExist(fileName, champions))
    {
        return false;
    }
    return true;
}

bool isFileExist(fileNames* fileName, champStruct* champions)
{
    int fd = 0;
    int maxPosition = getMaxPosition(fileName);
    for (int i = 0; i < maxPosition; i++)
    {
        if ((fd = open(fileName[i].name, O_RDONLY)) != -1)
        {
            if (!isProperChampion(fd, fileName[i], &champions[i]))
            {
                return false;
            }
        }
        close(fd);
    }
    return true;
}

bool isProperChampion(int fd, fileNames fileName, champStruct* champions)
{
    if ((checkExecMagic(fd)) &&
        (getChampName(fd, champions)) &&
        (getChampCodeSize(fd, champions)) &&
        (getChampComment(fd, champions)) &&
        (getChampCode(fd, champions)))
    {
        champions->position = fileName.position;
        return true;
    }
    else
    {
        fprintf(stderr, "Error: %s is corrupted.\n", fileName.name);
        return false;
    }
}

bool checkExecMagic(int fd)
{
    char magicHeader[5] = {'\0'};
    magicHeader[1] = (char)0xea;
    magicHeader[2] = (char)0x83;
    magicHeader[3] = (char)0xf3;
    char fileMagicHeader[5] = {'\0'};
    read(fd, fileMagicHeader, 4);
    for (int i = 0; i < 4; i++)
    {
        if (magicHeader[i] != fileMagicHeader[i])
        {
            return false;
        }
    }
    return true;
}

bool getChampName(int fd, champStruct* champions)
{
    memset(champions->name, 0, PROG_NAME_LENGTH);
    read(fd, champions->name, PROG_NAME_LENGTH);
    lseek(fd, 4, SEEK_CUR);
    return true;
}

bool getChampCodeSize(int fd, champStruct* champions)
{
    char codeSizeStr[5] = {'\0'};
    champions->codeSize = 0;
    read(fd, codeSizeStr, 4);
    for (int i = 0; i < 4; i++)
    {
        champions->codeSize += (int)codeSizeStr[i];
    }
    if (champions->codeSize > PROCESS_MAX_SIZE)
    {
        return false;
    }
    return true;
}

bool getChampComment(int fd, champStruct* champions)
{
    memset(champions->comment, 0, COMMENT_LENGTH);
    read(fd, champions->comment, COMMENT_LENGTH);
    lseek(fd, 4, SEEK_CUR);
    return true;
}

bool getChampCode(int fd, champStruct* champions)
{
    int memory = INIT_MEM;
    int readSize = 0;
    int totalReadSize = 0;
    int codeIndex = 0;
    char buff[READ_SIZE + 1] = {'\0'};
    champions->code = getString(memory);
    while (1)
    {
        readSize = read(fd, buff, READ_SIZE);
        totalReadSize += readSize;
        // printf("%d\n", totalReadSize);
        incStringMemory(&champions->code, &memory, &totalReadSize);
        // strncpy(champions->code, buff, readSize);
        for (int i = 0; i < readSize; i++, codeIndex++)
        {
            // champions->code[codeIndex] = buff[i];
            // champions->code[codeIndex] = buff[i];
            strncat(champions->code, &buff[i], 1);
        }
        memset(buff, 0, READ_SIZE);
        if (readSize == 0) break;
    }
    // printf("%s\n", champions->code);
    return true;
}

int getMaxPosition(fileNames* fileName)
{
    int maxPosition = 0;
    for (int i = 0; ((i < MAX_PLAYERS_NUMBE) && (fileName[i].name != NULL)); i++)
    {
        if (maxPosition < fileName[i].position)
            maxPosition = fileName[i].position;
    }
    return maxPosition;
}