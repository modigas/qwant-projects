#include "libs.h"
#include "structs.h"

bool readFile(int* fd, char** fileContent);
void initString(char** string, unsigned int from, unsigned int to);
char* getString(unsigned int size);
void incStringMemory(char** string, int* currentMemory, int* futureMemory);