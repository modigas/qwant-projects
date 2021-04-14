#include "libs.h"
#include "structs.h"
#include "corewar1.h"
#include "linkedList.h"
#include "getOpAndArg.h"

bool isLive(char** fileContent, codeStruct** codeHeader, labelStruct** head,
            int* index, int* lineError, int* totalCodeSize, char commandName[],
            bool* isError);
bool isLd(char** fileContent, codeStruct** codeHeader, labelStruct** head,
          int* index, int* lineError, int* totalCodeSize, char commandName[],
          bool* isError);
bool isSt(char** fileContent, codeStruct** codeHeader, labelStruct** head,
          int* index, int* lineError, int* totalCodeSize, char commandName[],
          bool* isError);
bool isAdd(char** fileContent, codeStruct** codeHeader, int* index,
           int* lineError, int* totalCodeSize, char commandName[],
           bool* isError);
bool isSub(char** fileContent, codeStruct** codeHeader, int* index,
           int* lineError, int* totalCodeSize, char commandName[],
           bool* isError);
bool isAnd(char** fileContent, codeStruct** codeHeader, labelStruct** head,
           int* index, int* lineError, int* totalCodeSize, char commandName[],
           bool* isError);
bool isOr(char** fileContent, codeStruct** codeHeader, labelStruct** head,
          int* index, int* lineError, int* totalCodeSize, char commandName[],
          bool* isError);
bool isXor(char** fileContent, codeStruct** codeHeader, labelStruct** head,
           int* index, int* lineError, int* totalCodeSize, char commandName[],
           bool* isError);
void incStringMemory(char** string, int* currentMemory, int* futureMemory);