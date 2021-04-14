#include "../headers/getOpAndArg.h"

bool getAndCheckCommand(char** fileContent, char commandName[], int* indexCode,
                        int* lineError)
{
    char* tempOperator = NULL;
    if (!getCommand(fileContent, &tempOperator, indexCode))
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], the command and arguments must "
                "be on one line.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        free(tempOperator);
        return false;
    }
    if (!isCommand(&tempOperator, commandName))
    {
        free(tempOperator);
        return false;
    }
    if (!skipEmptySpaceUntilN(fileContent, indexCode))
    {
        free(tempOperator);
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], the command and arguments must "
                "be on one line.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        return false;
    }
    free(tempOperator);
    return true;
}

bool getCommand(char** fileContent, char** tempOperator, int* indexCode)
{
    int memory = INIT_MEM;
    int indexTemp = 0;
    *tempOperator = getString(memory);
    while (((*fileContent)[*indexCode] != ' ') &&
           ((*fileContent)[*indexCode] != TAB))
    {
        if (((*fileContent)[*indexCode] == '\n') ||
            ((*fileContent)[*indexCode] == '\0'))
        {
            return false;
        }
        incStringMemory(tempOperator, &memory, &indexTemp);
        (*tempOperator)[indexTemp] = (*fileContent)[*indexCode];
        *indexCode += 1;
        indexTemp += 1;
    }
    return true;
}

bool isCommand(char** tempOperator, char* pattern)
{
    int lengthOperator = strlen(*tempOperator);
    int lengthTemplate = strlen(pattern);
    if (lengthOperator != lengthTemplate) return false;
    for (int i = 0; i < lengthOperator; i++)
    {
        if ((*tempOperator)[i] != pattern[i]) return false;
    }
    return true;
}

bool isDir(char** fileContent, int* codeTotalSize, char* codeLabel,
           int* codeArg, labelStruct** head, int* indexCode, int* lineError)
{
    if ((*fileContent)[*indexCode] != DIRECT_CHAR)
    {
        fprintf(
            stderr,
            "%sError:%s On line [%s%d%s], the argument must be direct type.\n",
            RED, RESET, YELLOW, *lineError, RESET);
        return false;
    }
    *indexCode += 1;
    if ((*fileContent)[*indexCode] == LABEL_CHAR)
    {
        *indexCode += 1;
        if (!getLabelForCode(fileContent, &codeLabel, indexCode))
        {
            fprintf(stderr,
                    "%sError:%s On line [%s%d%s], the label does not exist.\n",
                    RED, RESET, YELLOW, *lineError, RESET);
            return false;
        }
        int totalMemory = 0;
        if ((totalMemory = isExistLabel(&codeLabel, head)) != -1)
        {
            *codeArg = totalMemory - *codeTotalSize;
        }
        else
        {
            *codeArg = *lineError;
        }
    }
    else
    {
        if (!getArg(fileContent, codeArg, indexCode))
        {
            fprintf(stderr,
                    "%sError:%s On line [%s%d%s], the argument must be an "
                    "integer.\n",
                    RED, RESET, YELLOW, *lineError, RESET);
            return false;
        }
    }
    return true;
}

bool isInd(char** fileContent, int* codeTotalSize, char* codeLabel,
           int* codeArg, labelStruct** head, int* indexCode, int* lineError)
{
    if ((*fileContent)[*indexCode] == LABEL_CHAR)
    {
        *indexCode += 1;
        if (!getLabelForCode(fileContent, &codeLabel, indexCode))
        {
            fprintf(stderr,
                    "%sError:%s On line [%s%d%s], the label does not exist.\n",
                    RED, RESET, YELLOW, *lineError, RESET);
            return false;
        }
        int totalMemory = 0;
        if ((totalMemory = isExistLabel(&codeLabel, head)) != -1)
        {
            *codeArg = totalMemory - *codeTotalSize;
        }
        else
        {
            *codeArg = *lineError;
        }
    }
    else if ((isInt((*fileContent)[*indexCode])) ||
             ((*fileContent)[*indexCode] == '-'))
    {
        if (!getArg(fileContent, codeArg, indexCode))
        {
            fprintf(stderr,
                    "%sError:%s On line [%s%d%s], the argument must be an "
                    "integer.\n",
                    RED, RESET, YELLOW, *lineError, RESET);
            return false;
        }
    }
    else
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], the argument must be an integer "
                "or label.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        return false;
    }
    return true;
}

bool isReg(char** fileContent, int* codeArg, int* indexCode, int* lineError)
{
    if ((*fileContent)[*indexCode] != REGULAR_CHAR)
    {
        fprintf(
            stderr,
            "%sError:%s On line [%s%d%s], the argument must be regular type.\n",
            RED, RESET, YELLOW, *lineError, RESET);
        return false;
    }
    *indexCode += 1;
    if (!getArg(fileContent, codeArg, indexCode))
    {
        fprintf(
            stderr,
            "%sError:%s On line [%s%d%s], the argument must be an integer.\n",
            RED, RESET, YELLOW, *lineError, RESET);
        return false;
    }
    return true;
}

bool getArg(char** fileContent, int* codeArg, int* indexCode)
{
    bool negative = false;
    if ((*fileContent)[*indexCode] == '-')
    {
        negative = true;
        *indexCode += 1;
    }
    if (!isInt((*fileContent)[*indexCode])) return false;
    while (isInt((*fileContent)[*indexCode]))
    {
        *codeArg += (*fileContent)[*indexCode] - '0';
        *codeArg *= 10;
        *indexCode += 1;
    }
    *codeArg /= 10;
    if (negative) *codeArg *= -1;
    if (((*fileContent)[*indexCode] != SEPARATOR_CHAR) &&
        ((*fileContent)[*indexCode] != ' ') &&
        ((*fileContent)[*indexCode] != '\n') &&
        ((*fileContent)[*indexCode] != '\0'))
    {
        return false;
    }
    return true;
}

bool isInt(char c)
{
    if ((c >= '0') && (c <= '9'))
        return true;
    else
        return false;
}

bool getLabelForCode(char** fileContent, char** codeLabel, int* indexCode)
{
    int memory = INIT_MEM;
    int indexTemp = 0;
    while (((*fileContent)[*indexCode] != SEPARATOR_CHAR) &&
           ((*fileContent)[*indexCode] != ' ') &&
           ((*fileContent)[*indexCode] != '\n') &&
           ((*fileContent)[*indexCode] != '\0') &&
           ((*fileContent)[*indexCode] != TAB))
    {
        if (!isLabelChar((*fileContent)[*indexCode]))
        {
            return false;
        }
        incStringMemory(codeLabel, &memory, &indexTemp);
        (*codeLabel)[indexTemp] = (*fileContent)[*indexCode];
        *indexCode += 1;
        indexTemp += 1;
    }
    return true;
}

int isExistLabel(char** codeLabel, labelStruct** head)
{
    labelStruct* labelLoop = *head;
    while (labelLoop != NULL)
    {
        if (strcmp(*codeLabel, labelLoop->name) == 0)
            return labelLoop->totalMemory;
        labelLoop = labelLoop->next;
    }
    return -1;
}