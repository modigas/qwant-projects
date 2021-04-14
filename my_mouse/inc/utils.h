#ifndef UTILS_H
#define UTILS_H

#include <libs.h>

void incStringMemory(char** string, int* currentMemory, int* futureMemory);
void initString(char** string, unsigned int from, unsigned int to);
char* getString(unsigned int size);
bool isInt(char c);

#endif