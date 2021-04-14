#include "../headers/codeToString.h"

void codeToString(codeStruct** codeHeader, header_t* header, char** codeString,
                  int* indexSize)
{
    int memory = INIT_MEM * 5;
    *codeString = getString(memory);
    codeStruct* codeHeaderLoop = *codeHeader;
    while (codeHeaderLoop->next != NULL)
    {
        codeHeaderLoop = codeHeaderLoop->next;
    }
    header->prog_size = codeHeaderLoop->codeTotalSize;
    toStringHeader(header, codeString, indexSize);
    toStringCodeHeader(codeHeader, codeString, indexSize);
}