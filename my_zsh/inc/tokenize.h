#include <libs.h>

bool tokenize(char** string, struct queue* tokens);
void handleEmptySpace(char** string, int* i, struct queue* tokens,
                      char** buffer, int* j, bool emptyString, int stringSize);
bool skipSpace(char** string, int* i);
bool isBlank(char c);