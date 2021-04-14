#include "libs.h"
#include "structs.h"
#include "corewar1.h"

bool fillHeader(header_t* header, char** fileContent, int* lineError,
                int* index);
void initHeader(header_t* header);
bool isProperHeader(char** fileContent, int* lineError, header_t* header,
                    int* index);
void skipEmptySpace(char** fileContent, int* index, int* lineError);
bool isHeaderName(char** fileContent, int* index);
bool isHeaderComment(char** fileContent, int* index);
bool getHeaderName(char** fileContent, int* index, int* lineError,
                   header_t* header);
bool getHeaderComment(char** fileContent, int* index, int* lineError,
                      header_t* header);