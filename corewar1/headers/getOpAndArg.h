#include "libs.h"
#include "structs.h"
#include "corewar1.h"
#include "linkedList.h"

void skipEmptySpace(char** fileContent, int* index, int* lineError);
bool skipEmptySpaceUntilN(char** fileContent, int* index);
void incStringMemory(char** string, int* currentMemory, int* futureMemory);
bool getCommand(char** fileContent, char** tempOperator, int* indexCode);
bool isCommand(char** tempOperator, char* pattern);
bool isDir(char** fileContent, int* codeTotalSize, char* codeLabel,
           int* codeArg, labelStruct** head, int* indexCode, int* lineError);
bool getLabelForCode(char** fileContent, char** codeLabel, int* indexCode);
bool isLabelChar(char c);
int isExistLabel(char** codeLabel, labelStruct** head);
bool getArg(char** fileContent, int* codeArg, int* indexCode);
bool isInt(char c);
bool getAndCheckCommand(char** fileContent, char commandName[], int* indexCode,
                        int* lineError);
bool isInd(char** fileContent, int* codeTotalSize, char* codeLabel,
           int* codeArg, labelStruct** head, int* indexCode, int* lineError);
bool isReg(char** fileContent, int* codeArg, int* indexCode, int* lineError);