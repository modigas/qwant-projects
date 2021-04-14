#include "utils.h"
#include "checkers.h"

int checkAllowed(char **content)
{
    int len = strLen(ALLOWED);
    int count = 0, i = 0;
    while ((*content)[i] != '\0')
    {
        for (int j = 0; j < len; j++)
        {
            if ((*content)[i] == ALLOWED[j]) count++;
        }
        i++;
    }
    return count == i ? 1 : 0;
}