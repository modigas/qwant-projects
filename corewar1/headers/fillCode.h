#include "libs.h"
#include "structs.h"
#include "corewar1.h"
#include "linkedList.h"
#include "isLiveToXor.h"
#include "isZjmpToAff.h"

bool fillCode(codeStruct** codeHeader, labelStruct** head, char** fileContent,
              int* lineError, int* index);
void skipEmptySpace(char** fileContent, int* index, int* lineError);
bool isLabel(labelStruct** head, char** fileContent, int* index, int* lineError,
             int* totalCodeSize, bool* isError);
bool skipEmptySpaceUntilN(char** fileContent, int* index);
void incStringMemory(char** string, int* currentMemory, int* futureMemory);
bool isLabelChar(char c);
bool fillLabel(codeStruct** codeHeader, labelStruct** head);