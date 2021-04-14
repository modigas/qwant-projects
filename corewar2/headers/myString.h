#include "libs.h"
#include "structs.h"

bool isInt(char c);
bool isStrInt(char* string);
void strToDec(char* string, int* number);
void incStringMemory(char** string, int* currentMemory, int* futureMemory);
void initString(char** string, unsigned int from, unsigned int to);
char* getString(unsigned int size);