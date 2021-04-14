#include <builtIn.h>

char** splitVars(char* str, char sep)
{
    int cond = 0, k = 0;
    char** strArr = (char**)malloc(strlen(str) * 3);
    char* buff = NULL;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != sep || cond)
        {
            buff = (char*)realloc(buff, k + 2);
            buff[k++] = str[i];
        }
        if (str[i] == sep && !cond)
        {
            buff[k] = '\0';
            strArr[0] = (char*)malloc(k + 1);
            strcpy(strArr[0], buff);
            k = 0;
            cond = 1;
        }
    }
    buff[k] = '\0';
    strArr[1] = (char*)malloc(k + 1);
    strcpy(strArr[1], buff);
    free(buff);
    return strArr;
}

void freeVarArgs(char** arr, int size)
{
    for (int j = 0; j < size; j++) free(arr[j]);
    free(arr);
}

int numOfArgs(char*** args)
{
    int num = 0;
    for (; (*args)[num] != NULL; num++)
        ;
    return num;
}

char* composeVar(char** name, char** value)
{
    char* output = (char*)malloc(strlen(*name) + strlen(*value) + 2);
    int i = 0, j = 0;
    while ((*name)[i] != '\0')
    {
        output[i] = (*name)[i];
        i++;
    }
    output[i] = '=';
    i++;
    while ((*value)[j] != '\0')
    {
        output[i + j] = (*value)[j];
        j++;
    }
    output[i + j] = '\0';
    return output;
}

void my_setenv(char*** env, char* name, char* value)
{
    int i = 0, cond = 0;
    for (; (*env)[i] != NULL; i++)
    {
        char** tempArr = splitVars((*env)[i], '=');
        if (strcmp(tempArr[0], name) == 0)
        {
            char* newVar = composeVar(&name, &value);
            free((*env)[i]);
            (*env)[i] = (char*)malloc(strlen(newVar) + 2);
            strcpy((*env)[i], newVar);
            free(newVar);
            cond = 1;
        }
        freeVarArgs(tempArr, 2);
    }
    if (!cond)
    {
        char* newVar = composeVar(&name, &value);
        *env = (char**)realloc(*env, (i + 2) * sizeof(char*));
        (*env)[i] = (char*)malloc(strlen(newVar) + 2);
        strcpy((*env)[i], newVar);
        free(newVar);
        (*env)[i + 1] = NULL;
    }
}

void builtInCd(char*** args)
{
    int numOpts = numOfArgs(args) - 1;
    if (numOpts == 0)
    {
        char homeDir[128] = "/home/";
        strcat(homeDir, getpwuid(getuid())->pw_name);
        if (chdir(homeDir)) printf("%s\n", strerror(errno));
    }
    else if (numOpts == 1)
    {
        if (chdir((*args)[1]))
        {
            printf("%s\n", strerror(errno));
        }
    }
    else
        fprintf(stderr, "Invalid number of arguments\n");
}

void builtInEcho(char*** args, char*** env)
{
    int i = 1;
    int numArgs = numOfArgs(args);
    while ((*args)[i] != NULL)
    {
        if ((*args)[i][0] == '$')
        {
            char* envVar = (*args)[i];
            envVar++;
            for (int j = 0; (*env)[j] != NULL; j++)
            {
                char** tempArr = splitVars((*env)[j], '=');
                if (strcmp(tempArr[0], envVar) == 0)
                {
                    printf("%s", tempArr[1]);
                    if (i != numArgs - 1) printf(" ");
                    freeVarArgs(tempArr, 2);
                    break;
                }
                freeVarArgs(tempArr, 2);
            }
        }
        else
        {
            printf("%s", (*args)[i]);
            if (i != numArgs - 1) printf(" ");
        }
        i++;
    }
    printf("\n");
}

void builtInSetenv(char*** args, char*** env)
{
    if (numOfArgs(args) == 3)
    {
        my_setenv(env, (*args)[1], (*args)[2]);
    }
    else
    {
        fprintf(stderr, "Invalid number of arguments\n");
    }
}

void builtInUnsetenv(char*** args, char*** env)
{
    int numArgs = numOfArgs(args);
    int shift = 0;
    if (numArgs == 2)
    {
        for (int i = 0; (*env)[i] != NULL; i++)
        {
            if (!shift)
            {
                char** tempArr = splitVars((*env)[i], '=');
                if (strcmp(tempArr[0], (*args)[1]) == 0)
                {
                    free((*env)[i]);
                    shift = 1;
                }
                freeVarArgs(tempArr, 2);
            }
            if (shift)
            {
                (*env)[i] = (*env)[i + 1];
            }
        }
    }
    else
    {
        fprintf(stderr, "Invalid number of arguments\n");
    }
}

void builtInEnv(char*** env)
{
    for (int i = 0; (*env)[i] != NULL; i++)
    {
        printf("%s\n", (*env)[i]);
    }
}
