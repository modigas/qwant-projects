#include "libs.h"
#include "structs.h"
#include "corewar1.h"

int main(int ac, char** av);
bool getFileNameOption(int ac, char*** av, fileNames* fileName,
                       options* option);
bool openFiles(fileNames* fileName, champStruct* champions);