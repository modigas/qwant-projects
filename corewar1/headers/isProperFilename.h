#include "libs.h"
#include "structs.h"

bool isProperFilename(int* ac, char*** av, char** name, int* fd);
bool checkInput(int* ac, char*** av);
void initString(char** string, unsigned int from, unsigned int to);
char* getString(unsigned int size);
char* getName(int* ac, char*** av);
bool isExistFile(int* fd, int* ac, char*** av);