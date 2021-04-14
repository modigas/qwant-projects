#include "libs.h"
#include "structs.h"
#include "corewar1.h"

void codeToString(codeStruct** codeHeader, header_t* header, char** codeString,
                  int* indexSize);
void initString(char** string, unsigned int from, unsigned int to);
char* getString(unsigned int size);
void incStringMemory(char** string, int* currentMemory, int* futureMemory);
void toStringHeader(header_t* header, char** codeString, int* indexSize);
void toStringCodeHeader(codeStruct** codeHeader, char** codeString,
                        int* indexSize);