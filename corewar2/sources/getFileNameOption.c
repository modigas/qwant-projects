#include "../headers/getFileNameOption.h"

bool getFileNameOption(int ac, char*** av, fileNames* fileName, options* option)
{
    initOption(option);
    if (!getOption(ac, av, option))
    {
        fprintf(stderr, "%s", OPT_ERROR);
        return false;
    }
    initFileName(fileName);
    if (!getFileName(ac, av, fileName))
    {
        fprintf(stderr, "%s", OPT_ERROR);
        return false;
    }
    return true;
}

void initFileName(fileNames* fileName)
{
    for (int i = 0; i < MAX_PLAYERS_NUMBE; i++)
    {
        fileName[i].name = NULL;
        fileName[i].position = -1;
    }
}

void initOption(options* option)
{
    option->dump = false;
    option->dumpSize = 0;
}

bool getOption(int ac, char*** av, options* option)
{
    for (int i = 1; i < ac; i++)
    {
        if (strcmp((*av)[i], OPTION_D) == 0)
        {
            if (option->dump) return false;
            option->dump = true;
            if ((i + 1) < ac) i += 1;
            else return false;
            if (!isStrInt((*av)[i])) return false;
            strToDec((*av)[i], &option->dumpSize);
        }
    }
    return true;
}

bool getFileName(int ac, char*** av, fileNames* fileName)
{
    int indexFile = 0;
    int positionMap[MAX_PLAYERS_NUMBE + 1] = {0};
    positionMap[0] = 1;
    int maxPlayers = 0;
    int totalPlayers = 0;
    for (int i = 1; i < ac; i++)
    {
        if (indexFile >= MAX_PLAYERS_NUMBE)
            return false;
        if (strcmp((*av)[i], OPTION_N) == 0)
        {
            if ((i + 2) < ac) i += 1;
            else return false;
            if (!isStrInt((*av)[i])) return false;
            int tempNum = 0;
            strToDec((*av)[i], &tempNum);
            for (int j = 0; j <= indexFile; j++)
            {
                if (fileName[j].position == tempNum)
                    return false;
            }
            fileName[indexFile].position = tempNum;
            if (maxPlayers <= tempNum) maxPlayers = tempNum;
            if (!isInRangeChamp(fileName[indexFile].position))
                return false;
            i += 1;
            if (!isProperName(&i, &indexFile, av, fileName))
            {
                return false;
            }
            positionMap[tempNum] += 1;
            indexFile += 1;
            totalPlayers += 1;
        }
        else if (strcmp((*av)[i] + strlen((*av)[i]) - 4, ".cor") == 0)
        {
            indexFile += 1;
        }
    }
    indexFile = 0;
    for (int i = 1; i < ac; i++)
    {
        if ((fileName[indexFile].name == NULL) && (isProperName(&i, &indexFile, av, fileName)))
        {
            if (fileName[indexFile].position == -1)
            {
                for (int j = 1; j <= MAX_PLAYERS_NUMBE + 1; j++)
                {
                    if (positionMap[j] == 0)
                    {
                        positionMap[j] += 1;
                        fileName[indexFile].position = j;
                        if (maxPlayers <= j) maxPlayers = j;
                        break;
                    }
                }
            }
            totalPlayers += 1;
            if (totalPlayers > MAX_PLAYERS_NUMBE) return false;
            indexFile += 1;
        }
        else if (strcmp((*av)[i] + strlen((*av)[i]) - 4, ".cor") == 0)
        {
            indexFile += 1;
        }
    }
    for (int i = 1; i <= maxPlayers; i++)
    {
        if (positionMap[i] == 0) return false;
    }
    return true;
}

bool isProperName(int* index, int* indexFile, char*** av, fileNames* fileName)
{
    int stringLength = strlen((*av)[*index]);
    if (stringLength < 5)
    {
        return false;
    }
    else if (strcmp((*av)[*index] + stringLength - 4, ".cor") == 0)
    {
        getFileNameStr((*av)[*index], &fileName[*indexFile].name);
    }
    else
    {
        return false;
    }
    return true;
}

void getFileNameStr(char* avName, char** name)
{
    int stringLength = strlen(avName);
    *name = getString(stringLength);
    strcpy(*name, avName);
}

bool isInRangeChamp(int number)
{
    if ((number > 0) && (number < MAX_PLAYERS_NUMBE + 1)) return true;
    else return false;
}