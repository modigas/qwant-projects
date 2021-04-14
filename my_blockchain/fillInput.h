#include "libs.h"
#include "structs.h"

void readInput(CommandContainer* Inputs, bool* isError);
void initializeString(char** string, int start, int end);
void getNewString(char** string, int start, int end);
void memoryRealloc(char** buff, int* memory, int excessSize);
void fillContainer(char* lineString, CommandContainer** Inputs, bool* isError);
int skipSpace(char* string, int i);
void getActions(CommandContainer** Inputs, char* temp, bool* isError);
void getTypes(CommandContainer** Inputs, char* temp, bool* isError);
void fillNode(CommandContainer** Inputs, char*** temp, int elemNum);
void fillBlock(CommandContainer** Inputs, char*** temp, int elemNum);