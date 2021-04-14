#include <tokenize.h>

bool tokenize(char** string, struct queue* tokens)
{
    unsigned int stringSize = INIT_SIZE;
    char* buffer = getString(stringSize);
    int j = 0;
    bool emptyString = true;
    for (int i = 0; i < (int)strlen((*string)); i++)
    {
        handleEmptySpace(string, &i, tokens, &buffer, &j, emptyString,
                         stringSize);
        buffer[j++] = (*string)[i];
        if (emptyString && (*string)[i] == '\0') break;
        if (emptyString) emptyString = false;
        if (i + 1 == (int)strlen((*string)) && (*string)[i + 1] == '\0')
        {
            buffer[j] = '\0';
            tokens->put(tokens, buffer);
        }
    }
    free((*string));
    free(buffer);
    if (tokens->isEmpty(tokens))
    {
        tokens->destroy(tokens);
        return false;
    }
    else
        return true;
}

void handleEmptySpace(char** string, int* i, struct queue* tokens,
                      char** buffer, int* j, bool emptyString, int stringSize)
{
    if (skipSpace(string, i))
    {
        if (!emptyString)
        {
            (*buffer)[(*j)] = '\0';
            tokens->put(tokens, (*buffer));
            (*j) = 0;
            initString(buffer, 0, stringSize);
        }
    }
}

bool skipSpace(char** string, int* i)
{
    bool skipped = false;
    while (isBlank((*string)[(*i)]))
    {
        skipped = true;
        (*i)++;
    }
    return skipped;
}

bool isBlank(char c)
{
    for (int j = 0; BLANK[j] != '\0'; j++)
        if (c == BLANK[j]) return true;
    return false;
}