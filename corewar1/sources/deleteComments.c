#include "../headers/deleteComments.h"

void deleteComments(char** fileContent)
{
    for (int i = 0; (*fileContent)[i] != '\0'; i++)
    {
        if ((*fileContent)[i] == COMMENT_CHAR)
        {
            while ((*fileContent)[i] != '\n')
            {
                (*fileContent)[i] = ' ';
                i += 1;
            }
        }
    }
}