#ifndef STRUCTS
#define STRUCTS
#include <stdbool.h>

typedef unsigned long bitfield;

typedef struct bitfieldS
{
    bitfield** map;
    int maxSquare;
    int fieldSize;
    int rowSize;
    int collumnSize;
    int row;
    int currRow;
    int nextRow;
    int x;
    int y;
    void (*andRows)(int, bitfield*, bitfield*);
    void (*shiftAndRows)(int, bitfield**);
    bool (*bitExists)(bitfield*, struct bitfieldS*);
} bitfieldS;

void andRows(int fieldSize, bitfield* row1, bitfield* row2);
void shiftAndRows(int fieldSize, bitfield** row);
bool bitExists(bitfield* row, bitfieldS* map);

#endif