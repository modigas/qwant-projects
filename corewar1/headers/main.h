#include "libs.h"
#include "structs.h"
#include "corewar1.h"

bool isProperFilename(int* ac, char*** av, char** name, int* fd);
bool readFile(int* fd, char** fileContent);
bool fillHeader(header_t* header, char** fileContent, int* lineError,
                int* index);
void deleteComments(char** fileContent);
bool fillCode(codeStruct** codeHeader, labelStruct** head, char** fileContent,
              int* lineError, int* index);
void freeCode(codeStruct** codeHeader);
void freeLabelList(labelStruct** head);
void codeToString(codeStruct** codeHeader, header_t* header, char** codeString,
                  int* indexSize);