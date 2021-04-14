#include "../headers/toStringCodeHeader.h"
#include <string.h>

void toStringCodeHeader(codeStruct** codeHeader, char** codeString,
                        int* indexSize)
{
    codeStruct* codeHeaderLoop = *codeHeader;
    while (codeHeaderLoop != NULL)
    {
        int code = codeHeaderLoop->code;
        (*codeString)[*indexSize] = (char)code;
        *indexSize += 1;
        if (codeHeaderLoop->codeType != 0)
        {
            (*codeString)[*indexSize] = (char)codeHeaderLoop->codeType;
            *indexSize += 1;
        }
        int args[3] = {codeHeaderLoop->argSize1, codeHeaderLoop->argSize2,
                       codeHeaderLoop->argSize3};
        int argVals[3] = {codeHeaderLoop->arg1, codeHeaderLoop->arg2,
                          codeHeaderLoop->arg3};
        for (int i = 0; i < 3; i++)
        {
            if (args[i] != 0)
            {
                if (args[i] == 1)
                {
                    (*codeString)[*indexSize] = (char)argVals[i];
                    *indexSize += 1;
                }
                if (args[i] == 2)
                {
                    int arg = argVals[i];
                    char c1 = (char)arg;
                    char c2 = (char)(arg >> 8);
                    (*codeString)[*indexSize] = c2;
                    *indexSize += 1;
                    (*codeString)[*indexSize] = c1;
                    *indexSize += 1;
                }
                if (args[i] == 4)
                {
                    unsigned int arg = argVals[i];
                    char c1 = (char)arg;
                    char c2 = (char)(arg >> 8);
                    char c3 = (char)(arg >> 16);
                    char c4 = (char)(arg >> 24);
                    (*codeString)[*indexSize] = c4;
                    *indexSize += 1;
                    (*codeString)[*indexSize] = c3;
                    *indexSize += 1;
                    (*codeString)[*indexSize] = c2;
                    *indexSize += 1;
                    (*codeString)[*indexSize] = c1;
                    *indexSize += 1;
                }
            }
        }
        codeHeaderLoop = codeHeaderLoop->next;
    }
}
