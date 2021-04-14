#include "utils.h"

int isNum(char c)
{
    return (c >= '0' && c <= '9') ? 1 : 0;
}

int isOp(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') ? 1 : 0;
}

int isBr(char c)
{
    return (c == '(' || c == ')') ? 1 : 0;
}

int strLen(char *str)
{
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}

void initString(char **string, unsigned int from, unsigned int to)
{
    for (unsigned int i = from; i < to; i++)
    {
        (*string)[i] = '\0';
    }
}

char *getString(unsigned int size)
{
    char *string = (char *)malloc(size + 1);
    initString(&string, 0, size + 1);
    return string;
}

char *readLine(char *string)
{
    int length = 0;
    for (length = 0; string[length] != '\n'; length++)
    {
        if (string[length] == '\0') return NULL;
    }
    char *outputString = getString(length);
    for (int i = 0; string[i] != '\n'; i++)
    {
        outputString[i] = string[i];
    }
    return outputString;
}

int myAtoi(char *str)
{
    int res = 0, sign = 1, i = 0;
    if (str[0] == '-')
    {
        sign = -1;
        i++;
    }
    for (; str[i] != '\0'; ++i) res = res * 10 + str[i] - '0';
    return sign * res;
}