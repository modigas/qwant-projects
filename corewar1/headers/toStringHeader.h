#include "libs.h"
#include "structs.h"
#include "corewar1.h"

void initString(char** string, unsigned int from, unsigned int to);
char* getString(unsigned int size);
void incStringMemory(char** string, int* currentMemory, int* futureMemory);
void toStringHeader(header_t* header, char** codeString, int* indexSize);
void toStringMagicHeader(header_t* header, char** codeString, int* indexSize);
void toStringChampionName(header_t* header, char** codeString, int* indexSize);
void toStringNull(char** codeString, int* indexSize);
void toStringExecCodeSize(header_t* header, char** codeString, int* indexSize);
void toStringChampionComment(header_t* header, char** codeString,
                             int* indexSize);