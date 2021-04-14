#include "structs.h"
#include "lib.h"

void setupBitfield(bitfieldS* map, int totalReadLength, char** string);
bitfield* fillBitfield(bitfieldS* map, char* string);
bitfield* initBitfield(bitfieldS* map);
void freeMap(bitfieldS* map);