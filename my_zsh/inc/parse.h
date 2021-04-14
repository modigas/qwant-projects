#include <libs.h>

bool parse(char*** args, struct queue* tokens, struct queue* options,
           char*** path);
bool getWhichCommand(char*** args, struct queue* tokens, struct queue* options,
                     char*** path);
bool isBuiltIn(char*** args, struct queue* tokens, struct queue* options);
bool isExec(char*** args, struct queue* tokens, struct queue* options);
bool isBin(char*** args, struct queue* tokens, struct queue* options,
           char*** path);
char* searchForBin(char*** path, struct queue* tokens, bool* found);
void writeToArg(char*** args, struct queue* tokens, struct queue* options,
                char sign[2]);
void writeOptions(char*** args, struct queue* tokens, struct queue* options);
void freePath(char*** path);