#include "../headers/toStringHeader.h"

void toStringHeader(header_t* header, char** codeString, int* indexSize)
{
    toStringMagicHeader(header, codeString, indexSize);
    toStringChampionName(header, codeString, indexSize);
    toStringNull(codeString, indexSize);
    toStringExecCodeSize(header, codeString, indexSize);
    toStringChampionComment(header, codeString, indexSize);
    toStringNull(codeString, indexSize);
}

void hexToString(char** string, int hex, int* index, int offset)
{
    int tempInt = hex;
    int length = 0;
    while (tempInt != 0)
    {
        tempInt /= (16 * 16);
        length += 1;
    }
    int temp = *index;
    length += offset + temp;
    *index += offset;
    tempInt = hex;
    int tempHex = 0;
    while ((length - temp) != 0)
    {
        tempHex = tempInt % (16 * 16);
        (*string)[length - 1] = (char)tempHex;
        tempInt /= (16 * 16);
        length -= 1;
        *index += 1;
    }
    *index -= 1;
}

void toStringMagicHeader(header_t* header, char** codeString, int* indexSize)
{
    int offset = 1;
    hexToString(codeString, header->magic, indexSize, offset);
}

void toStringChampionName(header_t* header, char** codeString, int* indexSize)
{
    for (int i = 0; i < PROG_NAME_LENGTH; i++, (*indexSize)++)
    {
        (*codeString)[*indexSize] = header->prog_name[i];
    }
}

void toStringNull(char** codeString, int* indexSize)
{
    for (int i = 0; i < 4; i++, (*indexSize)++)
    {
        (*codeString)[*indexSize] = '\0';
    }
}

void toStringExecCodeSize(header_t* header, char** codeString, int* indexSize)
{
    int temp[4] = {0};
    int tempInt = header->prog_size;
    int length = 0;
    while (tempInt != 0)
    {
        tempInt /= (16 * 16);
        length += 1;
    }
    tempInt = header->prog_size;
    for (int i = 0; i < length; i++)
    {
        temp[3 - i] = tempInt % (16 * 16);
        tempInt /= (16 * 16);
    }
    for (int i = 0; i < 4; i++, (*indexSize)++)
    {
        (*codeString)[*indexSize] = temp[i];
    }
}

void toStringChampionComment(header_t* header, char** codeString,
                             int* indexSize)
{
    for (int i = 0; i < COMMENT_LENGTH; i++, (*indexSize)++)
    {
        (*codeString)[*indexSize] = header->comment[i];
    }
}