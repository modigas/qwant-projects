#include <parse.h>

bool parse(char*** args, struct queue* tokens, struct queue* options,
           char*** path)
{
    (*args) = (char**)malloc(sizeof(char*) * (tokens->size(tokens) + 1));
    if (!getWhichCommand(args, tokens, options, path))
    {
        fprintf(stderr, "%sError:%s invalid command\n", RED_B, RESET_COLOR);
        if (*path != NULL) freePath(path);
        return false;
    }
    writeOptions(args, tokens, options);
    if (*path != NULL) freePath(path);
    return true;
}

bool getWhichCommand(char*** args, struct queue* tokens, struct queue* options,
                     char*** path)
{
    if (isBuiltIn(args, tokens, options))
        return true;
    else if (isBin(args, tokens, options, path))
        return true;
    else if (isExec(args, tokens, options))
        return true;
    else
    {
        free((*args));
        tokens->destroy(tokens);
        options->destroy(options);
        return false;
    }
}

bool isBuiltIn(char*** args, struct queue* tokens, struct queue* options)
{
    char sign[2] = {'\0'};
    sign[0] = BUILT_IN;
    char* builtins[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit"};
    for (int i = 0; i < (int)(sizeof(builtins) / sizeof(char*)); i++)
    {
        if (strcmp(builtins[i], tokens->front(tokens)) == 0)
        {
            writeToArg(args, tokens, options, sign);
            return true;
        }
    }
    return false;
}

bool isExec(char*** args, struct queue* tokens, struct queue* options)
{
    char sign[2] = {'\0'};
    sign[0] = EXECUTABLE;
    struct stat filestat;
    if (stat(tokens->front(tokens), &filestat) == -1)
    {
        return false;
    }
    writeToArg(args, tokens, options, sign);
    return true;
}

bool isBin(char*** args, struct queue* tokens, struct queue* options,
           char*** path)
{
    char sign[2] = {'\0'};
    sign[0] = OS_COMMAND;
    bool found = false;
    char* fullPath = searchForBin(path, tokens, &found);
    if (found)
    {
        options->put(options, sign);
        tokens->pop(tokens);
        (*args)[0] = getString(strlen(fullPath));
        strcpy((*args)[0], fullPath);
        free(fullPath);
        return true;
    }
    else
        return false;
}

char* searchForBin(char*** path, struct queue* tokens, bool* found)
{
    struct stat filestat;
    if (*path == NULL)
    {
        (*found) = false;
        return NULL;
    }
    for (int i = 0; (*path)[i] != NULL; i++)
    {
        unsigned int stringSize =
            strlen(tokens->front(tokens)) + strlen((*path)[i]) + 1;
        char* fullPath = getString(stringSize);
        strcat(fullPath, (*path)[i]);
        strcat(fullPath, "/");
        strcat(fullPath, tokens->front(tokens));
        if (stat(fullPath, &filestat) == 0)
        {
            (*found) = true;
            return fullPath;
        }
        free(fullPath);
    }
    return NULL;
}

void writeToArg(char*** args, struct queue* tokens, struct queue* options,
                char sign[2])
{
    options->put(options, sign);
    (*args)[0] = getString(strlen(tokens->front(tokens)));
    strcpy((*args)[0], tokens->front(tokens));
    tokens->pop(tokens);
}

void writeOptions(char*** args, struct queue* tokens, struct queue* options)
{
    if (tokens->isEmpty(tokens))
    {
        char sign[2] = {'\0'};
        sign[0] = OPT_NONE;
        options->put(options, sign);
        tokens->destroy(tokens);
        (*args)[1] = NULL;
    }
    else
    {
        int i = 1;
        char sign[2] = {'\0'};
        sign[0] = OPT_EXIST;
        options->put(options, sign);
        while (!tokens->isEmpty(tokens))
        {
            (*args)[i] = getString(strlen(tokens->front(tokens)));
            strcpy((*args)[i], tokens->front(tokens));
            tokens->pop(tokens);
            i += 1;
        }
        (*args)[i] = NULL;
        tokens->destroy(tokens);
    }
}

void freePath(char*** path)
{
    for (int i = 0; (*path)[i] != NULL; i++)
    {
        free((*path)[i]);
    }
    free(*path);
}