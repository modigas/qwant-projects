#include "structs.h"
#include <stdio.h>

void andRows(int fieldSize, bitfield* row1, bitfield* row2)
{
    for (int i = 0; i < fieldSize; i++)
    {
        row1[i] &= row2[i];
    }
}

void shiftAndRows(int fieldSize, bitfield** row)
{
    for (int i = 0; i < (fieldSize - 1); i++)
    {
        (*row)[i] &= ((*row)[i] << 1) | (((*row)[i + 1] >> 63) & 1);
    }
    (*row)[fieldSize - 1] &= (*row)[fieldSize - 1] << 1;
}

bool bitExists(bitfield* row, bitfieldS* map)
{
    bitfield temp = 0;
    int i = 0;
    for (i = 0; ((i < map->fieldSize) && (!temp)); i++)
    {
        temp = row[i];
    }
    for (int j = 0; (temp && j < 64); j++)
    {
        if (temp & (((bitfield)1 << 63) >> j))
        {
            map->x = (i - 1) * 64 + j;
            map->y = map->row;
            return true;
        }
    }
    return false;
}