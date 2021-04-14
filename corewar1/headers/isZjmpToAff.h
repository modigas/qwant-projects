#include "libs.h"
#include "structs.h"
#include "corewar1.h"
#include "linkedList.h"
#include "getOpAndArg.h"

bool isZjmp(char** fileContent, codeStruct** codeHeader, labelStruct** head,
            int* index, int* lineError, int* totalCodeSize, char commandName[],
            bool* isError);
bool isLdi(char** fileContent, codeStruct** codeHeader, labelStruct** head,
           int* index, int* lineError, int* totalCodeSize, char commandName[],
           bool* isError);
bool isSti(char** fileContent, codeStruct** codeHeader, labelStruct** head,
           int* index, int* lineError, int* totalCodeSize, char commandName[],
           bool* isError);
bool isFork(char** fileContent, codeStruct** codeHeader, labelStruct** head,
            int* index, int* lineError, int* totalCodeSize, char commandName[],
            bool* isError);
bool isLld(char** fileContent, codeStruct** codeHeader, labelStruct** head,
           int* index, int* lineError, int* totalCodeSize, char commandName[],
           bool* isError);
bool isLldi(char** fileContent, codeStruct** codeHeader, labelStruct** head,
            int* index, int* lineError, int* totalCodeSize, char commandName[],
            bool* isError);
bool isLfork(char** fileContent, codeStruct** codeHeader, labelStruct** head,
             int* index, int* lineError, int* totalCodeSize, char commandName[],
             bool* isError);
bool isAff(char** fileContent, codeStruct** codeHeader, int* index,
           int* lineError, int* totalCodeSize, char commandName[],
           bool* isError);
