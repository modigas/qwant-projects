#include "../headers/isProperFilename.h"

bool isProperFilename(int* ac, char*** av, char** name, int* fd)
{
    if (!checkInput(&(*ac), &(*av))) return false;
    if (!isExistFile(&(*fd), &(*ac), &(*av))) return false;
    *name = getName(&(*ac), &(*av));
    return true;
}

bool checkInput(int* ac, char*** av)
{
    if (*ac > 2)
    {
        fprintf(stderr,
                "%sError:%s myrcc works with ONLY 1 file per execution.\n", RED,
                RESET);
        return false;
    }
    else if (*ac == 1)
    {
        fprintf(stderr, "%sError:%s Please, provide .s file.\n", RED, RESET);
        return false;
    }
    bool formatTrue = false;
    bool singleDotS = true;
    for (int i = 0; (*av)[(*ac) - 1][i] != '\0'; i++)
    {
        if (((*av)[(*ac) - 1][i] == '.') && ((*av)[(*ac) - 1][i + 1] == 's') &&
            ((*av)[(*ac) - 1][i + 2] != '\0'))
        {
            singleDotS = false;
        }
        if (((*av)[(*ac) - 1][i] == '.') && ((*av)[(*ac) - 1][i + 1] == 's') &&
            ((*av)[(*ac) - 1][i + 2] == '\0'))
        {
            formatTrue = true;
        }
    }
    if ((!singleDotS) && (formatTrue))
    {
        fprintf(stderr,
                "%sError:%s Please, avoid using multiple .s in the filename.\n",
                RED, RESET);
        return false;
    }
    if ((!singleDotS) || (!formatTrue))
    {
        fprintf(stderr, "%sError:%s myrcc works with ONLY .s extension.\n", RED,
                RESET);
        return false;
    }
    return true;
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

char* getName(int* ac, char*** av)
{
    unsigned int dotPosition = strlen((*av)[(*ac) - 1]) - 2;
    char* name = getString(dotPosition + 3);
    strncpy(name, (*av)[(*ac) - 1], dotPosition + 1);
    name[dotPosition + 1] = 'c';
    name[dotPosition + 2] = 'o';
    name[dotPosition + 3] = 'r';
    return name;
}

bool isExistFile(int* fd, int* ac, char*** av)
{
    if ((*fd = open((*av)[(*ac) - 1], O_RDONLY, S_IRUSR)) == -1)
    {
        fprintf(stderr, "%sError:%s The file %s does not exist.\n",
                (*av)[(*ac) - 1], RED, RESET);
        return false;
    }
    else
    {
        return true;
    }
}
