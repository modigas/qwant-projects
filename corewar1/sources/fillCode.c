#include "../headers/fillCode.h"
#include "corewar1.c"

bool fillCode(codeStruct** codeHeader, labelStruct** head, char** fileContent,
              int* lineError, int* index)
{
    bool isError = false;
    bool labelTrue = true;
    int totalCodeSize = 0;
    skipEmptySpace(fileContent, index, lineError);
    while ((*fileContent)[*index] != '\0')
    {
        initHeaderCode(codeHeader, &totalCodeSize);
        labelTrue = true;
        while (labelTrue)
        {
            labelTrue = isLabel(head, fileContent, index, lineError,
                                &totalCodeSize, &isError);
        }
        if (isLive(fileContent, codeHeader, head, index, lineError,
                   &totalCodeSize, cw_tab[0].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isLd(fileContent, codeHeader, head, index, lineError,
                 &totalCodeSize, cw_tab[1].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isSt(fileContent, codeHeader, head, index, lineError,
                 &totalCodeSize, cw_tab[2].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isAdd(fileContent, codeHeader, index, lineError, &totalCodeSize,
                  cw_tab[3].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isSub(fileContent, codeHeader, index, lineError, &totalCodeSize,
                  cw_tab[4].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isAnd(fileContent, codeHeader, head, index, lineError,
                  &totalCodeSize, cw_tab[5].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isOr(fileContent, codeHeader, head, index, lineError,
                 &totalCodeSize, cw_tab[6].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isXor(fileContent, codeHeader, head, index, lineError,
                  &totalCodeSize, cw_tab[7].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isZjmp(fileContent, codeHeader, head, index, lineError,
                   &totalCodeSize, cw_tab[8].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isLdi(fileContent, codeHeader, head, index, lineError,
                  &totalCodeSize, cw_tab[9].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isSti(fileContent, codeHeader, head, index, lineError,
                  &totalCodeSize, cw_tab[10].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isFork(fileContent, codeHeader, head, index, lineError,
                   &totalCodeSize, cw_tab[11].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isLld(fileContent, codeHeader, head, index, lineError,
                  &totalCodeSize, cw_tab[12].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isLldi(fileContent, codeHeader, head, index, lineError,
                   &totalCodeSize, cw_tab[13].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isLfork(fileContent, codeHeader, head, index, lineError,
                    &totalCodeSize, cw_tab[14].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if (isAff(fileContent, codeHeader, index, lineError, &totalCodeSize,
                  cw_tab[15].mnemonique, &isError))
            continue;
        else if (isError)
            return false;
        if ((*fileContent)[*index] != '\0')
        {
            fprintf(stderr,
                    "%sError:%s On line [%s%d%s], the unknown command.\n", RED,
                    RESET, YELLOW, *lineError, RESET);
            return false;
        }
    }
    if ((*head) != NULL)
    {
        if (!fillLabel(codeHeader, head))
        {
            return false;
        }
        freeLabelList(head);
    }
    return true;
}

bool isLabel(labelStruct** head, char** fileContent, int* index, int* lineError,
             int* totalCodeSize, bool* isError)
{
    int indexLabel = *index;
    int indexTemp = 0;
    int memory = INIT_MEM;
    char* tempLabel = getString(memory);
    while ((*fileContent)[indexLabel] != LABEL_CHAR)
    {
        if (((*fileContent)[indexLabel] == '\n') ||
            ((*fileContent)[indexLabel] == '\0') ||
            ((*fileContent)[indexLabel] == ' ') ||
            ((*fileContent)[indexLabel] == TAB))
        {
            free(tempLabel);
            return false;
        }
        incStringMemory(&tempLabel, &memory, &indexTemp);
        tempLabel[indexTemp] = (*fileContent)[indexLabel];
        if (!isLabelChar(tempLabel[indexTemp]))
        {
            free(tempLabel);
            fprintf(
                stderr,
                "%sError:%s On line [%s%d%s], the improper label or command.\n",
                RED, RESET, YELLOW, *lineError, RESET);
            *isError = true;
            return false;
        }
        indexLabel += 1;
        indexTemp += 1;
    }
    AppendLabel(head, &tempLabel, totalCodeSize);
    *index = indexLabel + 1;
    skipEmptySpace(fileContent, index, lineError);
    free(tempLabel);
    return true;
}

bool isLabelChar(char c)
{
    for (int i = 0; i < (int)strlen(LABEL_CHARS); i++)
    {
        if (c == LABEL_CHARS[i]) return true;
    }
    return false;
}

bool skipEmptySpaceUntilN(char** fileContent, int* index)
{
    if (((*fileContent)[*index] == '\n') || ((*fileContent)[*index] == '\0'))
        return false;
    while (((*fileContent)[*index] == ' ') || ((*fileContent)[*index] == TAB))
    {
        *index += 1;
        if (((*fileContent)[*index] == '\n') ||
            ((*fileContent)[*index] == '\0'))
            return false;
    }
    return true;
}