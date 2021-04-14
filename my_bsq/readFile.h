#include "lib.h"
#include "structs.h"
#include "utils.h"

bool readFile(int fd, int ac, char* av, char** string, bitfieldS* map);
bool readContent(int fd, char** string, bitfieldS* map);
int getRowSize(int fd);
bool readFirstLine(int fd, char** buff);
bool readSecondLine(int fd, char** string, int* totalReadLength);
bool readRest(int fd, char** string, int* totalReadLength, bitfieldS* map);
bitfield* fillBitfield(bitfieldS* map, char* string);
void setupBitfield(bitfieldS* map, int totalReadLength, char** string);
void freeMap(bitfieldS* map);