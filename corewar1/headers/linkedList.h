#include "libs.h"
#include "structs.h"

char* getString(unsigned int size);
void AppendLabel(labelStruct** head, char** label, int* totalCodeSize);
labelStruct* getNewLabel(char** label, int* totalCodeSize);
void freeLabelList(labelStruct** head);
void initHeaderCode(codeStruct** codeHeader, int* totalCodeSize);
codeStruct* getNewCode(int* totalCodeSize);
void freeCode(codeStruct** codeHeader);