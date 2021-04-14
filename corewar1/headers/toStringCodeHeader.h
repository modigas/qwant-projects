#include "libs.h"
#include "structs.h"
#include "corewar1.h"

void initString(char** string, unsigned int from, unsigned int to);
char* getString(unsigned int size);
void incStringMemory(char** string, int* currentMemory, int* futureMemory);
void toStringCodeHeader(codeStruct** codeHeader, char** codeString,
                        int* indexSize);