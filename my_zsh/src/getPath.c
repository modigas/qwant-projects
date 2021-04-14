#include <getPath.h>

char** getPath(char** env)
{
    int i = 0;
    char** path = NULL;
    for (i = 0; env[i] != NULL; i++)
    {
        if (isPath(env, i))
        {
            path = my_strtok(env[i], ':');
            return path;
        }
    }
    return NULL;
}

bool isPath(char** string, int i)
{
    if (strlen((string)[i]) > 4 && (string)[i][0] == 'P' &&
        (string)[i][1] == 'A' && (string)[i][2] == 'T' && (string)[i][3] == 'H')
        return true;
    else
        return false;
}