#include <libs.h>

char** splitVars(char* str, char sep);
void freeVarArgs(char** arr, int size);
char* composeVar(char** name, char** value);
void my_setenv(char*** env, char* name, char* value);
int numOfArgs(char*** args);
void builtInCd(char*** args);
void builtInEcho(char*** args, char*** env);
void builtInSetenv(char*** args, char*** env);
void builtInUnsetenv(char*** args, char*** env);
void builtInEnv(char*** env);
void builtInExit();
