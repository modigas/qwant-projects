#include "libs.h"
#include "structs.h"
#include "corewar1.h"
#include "myString.h"

bool getFileNameOption(int ac, char*** av, fileNames* fileName,
                       options* option);
void initOption(options* option);
bool getOption(int ac, char*** av, options* option);
bool getFileName(int ac, char*** av, fileNames* fileName);
bool isInRangeChamp(int number);
void getFileNameStr(char* avName, char** name);
bool isProperName(int* index, int* indexFile, char*** av, fileNames* fileName);
void initFileName(fileNames* fileName);