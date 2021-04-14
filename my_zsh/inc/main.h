#include <libs.h>

char* readTerminal();
bool tokenize(char** string, struct queue* tokens);
bool parse(char*** args, struct queue* tokens, struct queue* options,
           char*** path);
char** getPath(char** env);
bool execute(char*** args, struct queue* options, char*** env);
