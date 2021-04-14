#include "structs.h"
#include "lib.h"

bool readFile(int fd, int ac, char* av, char** string, bitfieldS* map);
void findBsq(bitfieldS* map);
void printBsq(int fd, char** string, bitfieldS* map);
void freeMap(bitfieldS* map);