#include "libs.h"

#define ALLOWED "+-*/%0123456789() "

int isNum(char);
int isOp(char);
int isBr(char);
int strLen(char *);
void initString(char **string, unsigned int from, unsigned int to);
char *getString(unsigned int size);
char *readLine(char *string);
int myAtoi(char *str);