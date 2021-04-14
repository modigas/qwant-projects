#include "../headers/fillHeader.h"

bool fillHeader(header_t* header, char** fileContent, int* lineError,
                int* index)
{
    initHeader(header);
    if (!isProperHeader(fileContent, lineError, header, index))
    {
        return false;
    }
    skipEmptySpace(fileContent, index, lineError);
    return true;
}

void initHeader(header_t* header)
{
    header->magic = COREWAR_EXEC_MAGIC;
    for (int i = 0; i <= PROG_NAME_LENGTH; i++) header->prog_name[i] = '\0';
    for (int i = 0; i <= COMMENT_LENGTH; i++) header->comment[i] = '\0';
    header->prog_size = 0;
}

bool isProperHeader(char** fileContent, int* lineError, header_t* header,
                    int* index)
{
    if ((*fileContent)[*index] != '\0')
    {
        skipEmptySpace(fileContent, index, lineError);
        if (isHeaderName(fileContent, index))
        {
            skipEmptySpace(fileContent, index, lineError);
            if (!getHeaderName(fileContent, index, lineError, header))
                return false;
            skipEmptySpace(fileContent, index, lineError);
            if ((*fileContent)[*index - 1] == '"')
            {
                fprintf(stderr,
                        "%sError%s: On line[%s%d%s], missing quote '\"' at the "
                        "end of the name.\n",
                        RED, RESET, YELLOW, *lineError, RESET);
                return false;
            }
            if (isHeaderComment(fileContent, index))
            {
                skipEmptySpace(fileContent, index, lineError);
                if (!getHeaderComment(fileContent, index, lineError, header))
                    return false;
            }
            else
            {
                fprintf(stderr,
                        "%sError:%s On line[%s%d%s], comment format must be "
                        "\"%s\".\n",
                        RED, RESET, YELLOW, *lineError, RESET,
                        COMMENT_CMD_STRING);
                return false;
            }
        }
        else if (isHeaderComment(fileContent, index))
        {
            skipEmptySpace(fileContent, index, lineError);
            if (!getHeaderComment(fileContent, index, lineError, header))
                return false;
            skipEmptySpace(fileContent, index, lineError);
            if ((*fileContent)[*index - 1] == '"')
            {
                fprintf(stderr,
                        "%sError%s: On line[%s%d%s], missing quote '\"' at the "
                        "end of the comment.\n",
                        RED, RESET, YELLOW, *lineError, RESET);
                return false;
            }
            if (isHeaderName(fileContent, index))
            {
                skipEmptySpace(fileContent, index, lineError);
                if (!getHeaderName(fileContent, index, lineError, header))
                    return false;
            }
            else
            {
                fprintf(
                    stderr,
                    "%sError%s: On line[%s%d%s], name format must be \"%s\".\n",
                    RED, RESET, YELLOW, *lineError, RESET, NAME_CMD_STRING);
                return false;
            }
        }
        else
        {
            fprintf(stderr,
                    "%sError%s: On line[%s%d%s], name/comment format must be "
                    "\"%s\"/\"%s\", respectively.\n",
                    RED, RESET, YELLOW, *lineError, RESET, NAME_CMD_STRING,
                    COMMENT_CMD_STRING);
            return false;
        }
    }
    return true;
}

void skipEmptySpace(char** fileContent, int* index, int* lineError)
{
    while (((*fileContent)[*index] == ' ') ||
           ((*fileContent)[*index] == '\n') || ((*fileContent)[*index] == TAB))
    {
        if ((*fileContent)[*index] == '\n') *lineError += 1;
        *index += 1;
    }
}

bool isHeaderName(char** fileContent, int* index)
{
    const int nameLength = strlen(NAME_CMD_STRING);
    int indexFile = *index;

    for (int indexName = 0; indexName < nameLength; indexName++, indexFile++)
    {
        if (NAME_CMD_STRING[indexName] != (*fileContent)[indexFile])
            return false;
    }
    *index = indexFile;
    return true;
}

bool isHeaderComment(char** fileContent, int* index)
{
    const int commentLength = strlen(COMMENT_CMD_STRING);
    int indexFile = *index;

    for (int indexComment = 0; indexComment < commentLength;
         indexComment++, indexFile++)
    {
        if (COMMENT_CMD_STRING[indexComment] != (*fileContent)[indexFile])
            return false;
    }
    *index = indexFile;
    return true;
}

bool getHeaderName(char** fileContent, int* index, int* lineError,
                   header_t* header)
{
    int indexFile = *index;
    int indexName = 0;

    if ((*fileContent)[indexFile] == '"')
    {
        for (indexFile += 1; (*fileContent)[indexFile] != '"';
             indexFile++, indexName++)
        {
            if ((*fileContent)[indexFile] == '\n')
            {
                indexFile += 1;
                *lineError += 1;
            }
            if ((*fileContent)[indexFile] == '\0')
            {
                fprintf(stderr,
                        "%sError%s: On line[%s%d%s], missing quote '\"' at the "
                        "end of the name.\n",
                        RED, RESET, YELLOW, *lineError, RESET);
                return false;
            }
            if (indexFile >= PROG_NAME_LENGTH)
            {
                fprintf(stderr,
                        "%sError%s: On line[%s%d%s], the name length must be "
                        "lower than %d.\n",
                        RED, RESET, YELLOW, *lineError, RESET,
                        PROG_NAME_LENGTH);
                return false;
            }
            header->prog_name[indexName] = (*fileContent)[indexFile];
        }
    }
    else
    {
        fprintf(stderr,
                "%sError%s: On line[%s%d%s], missing quote '\"' at the start "
                "of the name.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        return false;
    }
    *index = indexFile + 1;
    return true;
}

bool getHeaderComment(char** fileContent, int* index, int* lineError,
                      header_t* header)
{
    int indexFile = *index;
    int indexComment = 0;

    if ((*fileContent)[indexFile] == '"')
    {
        for (indexFile += 1; (*fileContent)[indexFile] != '"';
             indexFile++, indexComment++)
        {
            if ((*fileContent)[indexFile] == '\n')
            {
                indexFile += 1;
                *lineError += 1;
            }
            if ((*fileContent)[indexFile] == '\0')
            {
                fprintf(stderr,
                        "%sError%s: On line[%s%d%s], missing quote '\"' at the "
                        "end of the comment.\n",
                        RED, RESET, YELLOW, *lineError, RESET);
                return false;
            }
            if (indexFile >= COMMENT_LENGTH)
            {
                fprintf(stderr,
                        "%sError%s: On line[%s%d%s], the comment length must "
                        "be lower than %d.\n",
                        RED, RESET, YELLOW, *lineError, RESET, COMMENT_LENGTH);
                return false;
            }
            header->comment[indexComment] = (*fileContent)[indexFile];
        }
    }
    else
    {
        fprintf(stderr,
                "%sError%s: On line[%s%d%s], missing quote '\"' at the start "
                "of the comment.\n",
                RED, RESET, YELLOW, *lineError, RESET);
        return false;
    }
    *index = indexFile + 1;
    return true;
}