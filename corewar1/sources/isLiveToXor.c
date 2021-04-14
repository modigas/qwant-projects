#include "../headers/isLiveToXor.h"

bool isLive(char** fileContent, codeStruct** codeHeader, labelStruct** head,
            int* index, int* lineError, int* totalCodeSize, char commandName[],
            bool* isError)
{
    int indexCode = *index;
    codeStruct* codeHeaderTemp = *codeHeader;
    while (codeHeaderTemp->next != NULL) codeHeaderTemp = codeHeaderTemp->next;
    if (!getAndCheckCommand(fileContent, commandName, &indexCode, lineError))
    {
        return false;
    }
    if (!isDir(fileContent, &codeHeaderTemp->codeTotalSize,
               codeHeaderTemp->label1, &codeHeaderTemp->arg1, head, &indexCode,
               lineError))
    {
        *isError = true;
        return false;
    }
    codeHeaderTemp->code = CODE_LIVE;
    codeHeaderTemp->thisCodeSize = CODE_SIZE + DIR_SIZE_4;
    codeHeaderTemp->codeTotalSize =
        *totalCodeSize + codeHeaderTemp->thisCodeSize;
    *totalCodeSize = codeHeaderTemp->codeTotalSize;
    codeHeaderTemp->argSize1 = DIR_SIZE_4;
    *index = indexCode;
    if (!skipEmptySpaceUntilN(fileContent, index))
    {
        skipEmptySpace(fileContent, index, lineError);
        return true;
    }
    else
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], Only one command per line is "
                "allowed.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
}

bool isLd(char** fileContent, codeStruct** codeHeader, labelStruct** head,
          int* index, int* lineError, int* totalCodeSize, char commandName[],
          bool* isError)
{
    int indexCode = *index;
    codeStruct* codeHeaderTemp = *codeHeader;
    while (codeHeaderTemp->next != NULL) codeHeaderTemp = codeHeaderTemp->next;
    if (!getAndCheckCommand(fileContent, commandName, &indexCode, lineError))
    {
        return false;
    }
    if ((*fileContent)[indexCode] == DIRECT_CHAR)
    {
        if (!isDir(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label1, &codeHeaderTemp->arg1, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += DIR_SIZE_4;
        codeHeaderTemp->argSize1 = DIR_SIZE_4;
        codeHeaderTemp->codeType |= DIR_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else
    {
        if (!isInd(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label1, &codeHeaderTemp->arg1, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += IND_SIZE_2;
        codeHeaderTemp->argSize1 = IND_SIZE_2;
        codeHeaderTemp->codeType |= IND_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] != SEPARATOR_CHAR)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], missing separator character.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
    indexCode += 1;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if (!isReg(fileContent, &codeHeaderTemp->arg2, &indexCode, lineError))
    {
        *isError = true;
        return false;
    }
    codeHeaderTemp->codeType |= REG_TYPE_CODE;
    codeHeaderTemp->codeType <<= 2 * PADDING;
    codeHeaderTemp->code = CODE_LOAD;
    codeHeaderTemp->thisCodeSize += REG_SIZE_1 + CODE_SIZE + CODE_TYPE_SIZE;
    codeHeaderTemp->codeTotalSize =
        *totalCodeSize + codeHeaderTemp->thisCodeSize;
    *totalCodeSize = codeHeaderTemp->codeTotalSize;
    codeHeaderTemp->argSize2 = REG_SIZE_1;
    *index = indexCode;
    if (!skipEmptySpaceUntilN(fileContent, index))
    {
        skipEmptySpace(fileContent, index, lineError);
        return true;
    }
    else
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], Only one command per line is "
                "allowed.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
}

bool isSt(char** fileContent, codeStruct** codeHeader, labelStruct** head,
          int* index, int* lineError, int* totalCodeSize, char commandName[],
          bool* isError)
{
    int indexCode = *index;
    codeStruct* codeHeaderTemp = *codeHeader;
    while (codeHeaderTemp->next != NULL) codeHeaderTemp = codeHeaderTemp->next;
    if (!getAndCheckCommand(fileContent, commandName, &indexCode, lineError))
    {
        return false;
    }
    if (!isReg(fileContent, &codeHeaderTemp->arg1, &indexCode, lineError))
    {
        *isError = true;
        return false;
    }
    codeHeaderTemp->argSize1 = REG_SIZE_1;
    codeHeaderTemp->thisCodeSize += REG_SIZE_1;
    codeHeaderTemp->codeType |= REG_TYPE_CODE;
    codeHeaderTemp->codeType <<= PADDING;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] != SEPARATOR_CHAR)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], missing separator character.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
    indexCode += 1;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] == REGULAR_CHAR)
    {
        if (!isReg(fileContent, &codeHeaderTemp->arg2, &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += REG_SIZE_1;
        codeHeaderTemp->argSize2 = REG_SIZE_1;
        codeHeaderTemp->codeType |= REG_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else
    {
        if (!isInd(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label2, &codeHeaderTemp->arg2, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += IND_SIZE_2;
        codeHeaderTemp->argSize2 = IND_SIZE_2;
        codeHeaderTemp->codeType |= IND_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    codeHeaderTemp->codeType <<= PADDING;
    codeHeaderTemp->code = CODE_STORE;
    codeHeaderTemp->thisCodeSize += CODE_SIZE + CODE_TYPE_SIZE;
    codeHeaderTemp->codeTotalSize =
        *totalCodeSize + codeHeaderTemp->thisCodeSize;
    *totalCodeSize = codeHeaderTemp->codeTotalSize;
    *index = indexCode;
    if (!skipEmptySpaceUntilN(fileContent, index))
    {
        skipEmptySpace(fileContent, index, lineError);
        return true;
    }
    else
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], Only one command per line is "
                "allowed.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
}

bool isAdd(char** fileContent, codeStruct** codeHeader, int* index,
           int* lineError, int* totalCodeSize, char commandName[],
           bool* isError)
{
    int indexCode = *index;
    codeStruct* codeHeaderTemp = *codeHeader;
    while (codeHeaderTemp->next != NULL) codeHeaderTemp = codeHeaderTemp->next;
    if (!getAndCheckCommand(fileContent, commandName, &indexCode, lineError))
    {
        return false;
    }
    if (!isReg(fileContent, &codeHeaderTemp->arg1, &indexCode, lineError))
    {
        *isError = true;
        return false;
    }
    codeHeaderTemp->argSize1 = REG_SIZE_1;
    codeHeaderTemp->thisCodeSize += REG_SIZE_1;
    codeHeaderTemp->codeType |= REG_TYPE_CODE;
    codeHeaderTemp->codeType <<= PADDING;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] != SEPARATOR_CHAR)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], missing separator character.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
    indexCode += 1;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if (!isReg(fileContent, &codeHeaderTemp->arg2, &indexCode, lineError))
    {
        *isError = true;
        return false;
    }
    codeHeaderTemp->argSize2 = REG_SIZE_1;
    codeHeaderTemp->thisCodeSize += REG_SIZE_1;
    codeHeaderTemp->codeType |= REG_TYPE_CODE;
    codeHeaderTemp->codeType <<= PADDING;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] != SEPARATOR_CHAR)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], missing separator character.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
    indexCode += 1;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if (!isReg(fileContent, &codeHeaderTemp->arg3, &indexCode, lineError))
    {
        *isError = true;
        return false;
    }
    codeHeaderTemp->argSize3 = REG_SIZE_1;
    codeHeaderTemp->thisCodeSize += REG_SIZE_1;
    codeHeaderTemp->codeType |= REG_TYPE_CODE;
    codeHeaderTemp->codeType <<= PADDING;
    codeHeaderTemp->code = CODE_ADD;
    codeHeaderTemp->thisCodeSize += CODE_SIZE + CODE_TYPE_SIZE;
    codeHeaderTemp->codeTotalSize =
        *totalCodeSize + codeHeaderTemp->thisCodeSize;
    *totalCodeSize = codeHeaderTemp->codeTotalSize;
    *index = indexCode;
    if (!skipEmptySpaceUntilN(fileContent, index))
    {
        skipEmptySpace(fileContent, index, lineError);
        return true;
    }
    else
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], Only one command per line is "
                "allowed.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
}

bool isSub(char** fileContent, codeStruct** codeHeader, int* index,
           int* lineError, int* totalCodeSize, char commandName[],
           bool* isError)
{
    int indexCode = *index;
    codeStruct* codeHeaderTemp = *codeHeader;
    while (codeHeaderTemp->next != NULL) codeHeaderTemp = codeHeaderTemp->next;
    if (!getAndCheckCommand(fileContent, commandName, &indexCode, lineError))
    {
        return false;
    }
    if (!isReg(fileContent, &codeHeaderTemp->arg1, &indexCode, lineError))
    {
        *isError = true;
        return false;
    }
    codeHeaderTemp->argSize1 = REG_SIZE_1;
    codeHeaderTemp->thisCodeSize += REG_SIZE_1;
    codeHeaderTemp->codeType |= REG_TYPE_CODE;
    codeHeaderTemp->codeType <<= PADDING;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] != SEPARATOR_CHAR)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], missing separator character.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
    indexCode += 1;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if (!isReg(fileContent, &codeHeaderTemp->arg2, &indexCode, lineError))
    {
        *isError = true;
        return false;
    }
    codeHeaderTemp->argSize2 = REG_SIZE_1;
    codeHeaderTemp->thisCodeSize += REG_SIZE_1;
    codeHeaderTemp->codeType |= REG_TYPE_CODE;
    codeHeaderTemp->codeType <<= PADDING;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] != SEPARATOR_CHAR)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], missing separator character.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
    indexCode += 1;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if (!isReg(fileContent, &codeHeaderTemp->arg3, &indexCode, lineError))
    {
        *isError = true;
        return false;
    }
    codeHeaderTemp->argSize3 = REG_SIZE_1;
    codeHeaderTemp->thisCodeSize += REG_SIZE_1;
    codeHeaderTemp->codeType |= REG_TYPE_CODE;
    codeHeaderTemp->codeType <<= PADDING;
    codeHeaderTemp->code = CODE_SUB;
    codeHeaderTemp->thisCodeSize += CODE_SIZE + CODE_TYPE_SIZE;
    codeHeaderTemp->codeTotalSize =
        *totalCodeSize + codeHeaderTemp->thisCodeSize;
    *totalCodeSize = codeHeaderTemp->codeTotalSize;
    *index = indexCode;
    if (!skipEmptySpaceUntilN(fileContent, index))
    {
        skipEmptySpace(fileContent, index, lineError);
        return true;
    }
    else
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], Only one command per line is "
                "allowed.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
}

bool isAnd(char** fileContent, codeStruct** codeHeader, labelStruct** head,
           int* index, int* lineError, int* totalCodeSize, char commandName[],
           bool* isError)
{
    int indexCode = *index;
    codeStruct* codeHeaderTemp = *codeHeader;
    while (codeHeaderTemp->next != NULL) codeHeaderTemp = codeHeaderTemp->next;
    if (!getAndCheckCommand(fileContent, commandName, &indexCode, lineError))
    {
        return false;
    }
    if ((*fileContent)[indexCode] == REGULAR_CHAR)
    {
        if (!isReg(fileContent, &codeHeaderTemp->arg1, &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += REG_SIZE_1;
        codeHeaderTemp->argSize1 = REG_SIZE_1;
        codeHeaderTemp->codeType |= REG_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else if ((*fileContent)[indexCode] == DIRECT_CHAR)
    {
        if (!isDir(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label1, &codeHeaderTemp->arg1, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += DIR_SIZE_4;
        codeHeaderTemp->argSize1 = DIR_SIZE_4;
        codeHeaderTemp->codeType |= DIR_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else
    {
        if (!isInd(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label1, &codeHeaderTemp->arg1, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += IND_SIZE_2;
        codeHeaderTemp->argSize1 = IND_SIZE_2;
        codeHeaderTemp->codeType |= IND_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] != SEPARATOR_CHAR)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], missing separator character.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
    indexCode += 1;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] == REGULAR_CHAR)
    {
        if (!isReg(fileContent, &codeHeaderTemp->arg2, &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += REG_SIZE_1;
        codeHeaderTemp->argSize2 = REG_SIZE_1;
        codeHeaderTemp->codeType |= REG_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else if ((*fileContent)[indexCode] == DIRECT_CHAR)
    {
        if (!isDir(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label2, &codeHeaderTemp->arg2, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += DIR_SIZE_4;
        codeHeaderTemp->argSize2 = DIR_SIZE_4;
        codeHeaderTemp->codeType |= DIR_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else
    {
        if (!isInd(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label2, &codeHeaderTemp->arg2, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += IND_SIZE_2;
        codeHeaderTemp->argSize2 = IND_SIZE_2;
        codeHeaderTemp->codeType |= IND_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] != SEPARATOR_CHAR)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], missing separator character.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
    indexCode += 1;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if (!isReg(fileContent, &codeHeaderTemp->arg3, &indexCode, lineError))
    {
        *isError = true;
        return false;
    }
    codeHeaderTemp->codeType |= REG_TYPE_CODE;
    codeHeaderTemp->codeType <<= PADDING;
    codeHeaderTemp->argSize3 = REG_SIZE_1;
    codeHeaderTemp->thisCodeSize += REG_SIZE_1;
    codeHeaderTemp->code = CODE_AND;
    codeHeaderTemp->thisCodeSize += CODE_SIZE + CODE_TYPE_SIZE;
    codeHeaderTemp->codeTotalSize =
        *totalCodeSize + codeHeaderTemp->thisCodeSize;
    *totalCodeSize = codeHeaderTemp->codeTotalSize;
    *index = indexCode;
    if (!skipEmptySpaceUntilN(fileContent, index))
    {
        skipEmptySpace(fileContent, index, lineError);
        return true;
    }
    else
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], Only one command per line is "
                "allowed.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
}

bool isOr(char** fileContent, codeStruct** codeHeader, labelStruct** head,
          int* index, int* lineError, int* totalCodeSize, char commandName[],
          bool* isError)
{
    int indexCode = *index;
    codeStruct* codeHeaderTemp = *codeHeader;
    while (codeHeaderTemp->next != NULL) codeHeaderTemp = codeHeaderTemp->next;
    if (!getAndCheckCommand(fileContent, commandName, &indexCode, lineError))
    {
        return false;
    }
    if ((*fileContent)[indexCode] == REGULAR_CHAR)
    {
        if (!isReg(fileContent, &codeHeaderTemp->arg1, &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += REG_SIZE_1;
        codeHeaderTemp->argSize1 = REG_SIZE_1;
        codeHeaderTemp->codeType |= REG_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else if ((*fileContent)[indexCode] == DIRECT_CHAR)
    {
        if (!isDir(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label1, &codeHeaderTemp->arg1, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += DIR_SIZE_4;
        codeHeaderTemp->argSize1 = DIR_SIZE_4;
        codeHeaderTemp->codeType |= DIR_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else
    {
        if (!isInd(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label1, &codeHeaderTemp->arg1, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += IND_SIZE_2;
        codeHeaderTemp->argSize1 = IND_SIZE_2;
        codeHeaderTemp->codeType |= IND_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] != SEPARATOR_CHAR)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], missing separator character.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
    indexCode += 1;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] == REGULAR_CHAR)
    {
        if (!isReg(fileContent, &codeHeaderTemp->arg2, &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += REG_SIZE_1;
        codeHeaderTemp->argSize2 = REG_SIZE_1;
        codeHeaderTemp->codeType |= REG_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else if ((*fileContent)[indexCode] == DIRECT_CHAR)
    {
        if (!isDir(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label2, &codeHeaderTemp->arg2, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += DIR_SIZE_4;
        codeHeaderTemp->argSize2 = DIR_SIZE_4;
        codeHeaderTemp->codeType |= DIR_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else
    {
        if (!isInd(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label2, &codeHeaderTemp->arg2, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += IND_SIZE_2;
        codeHeaderTemp->argSize2 = IND_SIZE_2;
        codeHeaderTemp->codeType |= IND_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] != SEPARATOR_CHAR)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], missing separator character.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
    indexCode += 1;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if (!isReg(fileContent, &codeHeaderTemp->arg3, &indexCode, lineError))
    {
        *isError = true;
        return false;
    }
    codeHeaderTemp->codeType |= REG_TYPE_CODE;
    codeHeaderTemp->codeType <<= PADDING;
    codeHeaderTemp->argSize3 = REG_SIZE_1;
    codeHeaderTemp->thisCodeSize += REG_SIZE_1;
    codeHeaderTemp->code = CODE_OR;
    codeHeaderTemp->thisCodeSize += CODE_SIZE + CODE_TYPE_SIZE;
    codeHeaderTemp->codeTotalSize =
        *totalCodeSize + codeHeaderTemp->thisCodeSize;
    *totalCodeSize = codeHeaderTemp->codeTotalSize;
    *index = indexCode;
    if (!skipEmptySpaceUntilN(fileContent, index))
    {
        skipEmptySpace(fileContent, index, lineError);
        return true;
    }
    else
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], Only one command per line is "
                "allowed.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
}

bool isXor(char** fileContent, codeStruct** codeHeader, labelStruct** head,
           int* index, int* lineError, int* totalCodeSize, char commandName[],
           bool* isError)
{
    int indexCode = *index;
    codeStruct* codeHeaderTemp = *codeHeader;
    while (codeHeaderTemp->next != NULL) codeHeaderTemp = codeHeaderTemp->next;
    if (!getAndCheckCommand(fileContent, commandName, &indexCode, lineError))
    {
        return false;
    }
    if ((*fileContent)[indexCode] == REGULAR_CHAR)
    {
        if (!isReg(fileContent, &codeHeaderTemp->arg1, &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += REG_SIZE_1;
        codeHeaderTemp->argSize1 = REG_SIZE_1;
        codeHeaderTemp->codeType |= REG_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else if ((*fileContent)[indexCode] == DIRECT_CHAR)
    {
        if (!isDir(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label1, &codeHeaderTemp->arg1, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += DIR_SIZE_4;
        codeHeaderTemp->argSize1 = DIR_SIZE_4;
        codeHeaderTemp->codeType |= DIR_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else
    {
        if (!isInd(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label1, &codeHeaderTemp->arg1, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += IND_SIZE_2;
        codeHeaderTemp->argSize1 = IND_SIZE_2;
        codeHeaderTemp->codeType |= IND_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] != SEPARATOR_CHAR)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], missing separator character.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
    indexCode += 1;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] == REGULAR_CHAR)
    {
        if (!isReg(fileContent, &codeHeaderTemp->arg2, &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += REG_SIZE_1;
        codeHeaderTemp->argSize2 = REG_SIZE_1;
        codeHeaderTemp->codeType |= REG_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else if ((*fileContent)[indexCode] == DIRECT_CHAR)
    {
        if (!isDir(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label2, &codeHeaderTemp->arg2, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += DIR_SIZE_4;
        codeHeaderTemp->argSize2 = DIR_SIZE_4;
        codeHeaderTemp->codeType |= DIR_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    else
    {
        if (!isInd(fileContent, &codeHeaderTemp->codeTotalSize,
                   codeHeaderTemp->label2, &codeHeaderTemp->arg2, head,
                   &indexCode, lineError))
        {
            *isError = true;
            return false;
        }
        codeHeaderTemp->thisCodeSize += IND_SIZE_2;
        codeHeaderTemp->argSize2 = IND_SIZE_2;
        codeHeaderTemp->codeType |= IND_TYPE_CODE;
        codeHeaderTemp->codeType <<= PADDING;
    }
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if ((*fileContent)[indexCode] != SEPARATOR_CHAR)
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], missing separator character.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
    indexCode += 1;
    skipEmptySpaceUntilN(fileContent, &indexCode);
    if (!isReg(fileContent, &codeHeaderTemp->arg3, &indexCode, lineError))
    {
        *isError = true;
        return false;
    }
    codeHeaderTemp->codeType |= REG_TYPE_CODE;
    codeHeaderTemp->codeType <<= PADDING;
    codeHeaderTemp->argSize3 = REG_SIZE_1;
    codeHeaderTemp->thisCodeSize += REG_SIZE_1;
    codeHeaderTemp->code = CODE_XOR;
    codeHeaderTemp->thisCodeSize += CODE_SIZE + CODE_TYPE_SIZE;
    codeHeaderTemp->codeTotalSize =
        *totalCodeSize + codeHeaderTemp->thisCodeSize;
    *totalCodeSize = codeHeaderTemp->codeTotalSize;
    *index = indexCode;
    if (!skipEmptySpaceUntilN(fileContent, index))
    {
        skipEmptySpace(fileContent, index, lineError);
        return true;
    }
    else
    {
        fprintf(stderr,
                "%sError:%s On line [%s%d%s], Only one command per line is "
                "allowed.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        *isError = true;
        return false;
    }
}