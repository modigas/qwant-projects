#include "libs.h"
#include "structs.h"
#include "corewar1.h"
#include "myString.h"

bool openFiles(fileNames* fileName, champStruct* champions);
bool isFileExist(fileNames* fileName, champStruct* champions);
int getMaxPosition(fileNames* fileName);
bool isProperChampion(int fd, fileNames fileName, champStruct* champions);
bool checkExecMagic(int fd);
bool getChampName(int fd, champStruct* champions);
bool getChampCodeSize(int fd, champStruct* champions);
bool getChampComment(int fd, champStruct* champions);
bool getChampCode(int fd, champStruct* champions);