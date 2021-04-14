#include "libs.h"
#include "structs.h"
#include "corewar1.h"
#include "linkedList.h"
#include "isLiveToXor.h"

bool fillLabel(codeStruct** codeHeader, labelStruct** head);
bool isInLabelList(bool isLabel1, bool isLabel2, bool isLabel3,
                   codeStruct* codeTemp);
void getLabelAddress(int* labelTotalMemory, int* codeArg, int* thisCodeSize,
                     int* codeTotalSize);