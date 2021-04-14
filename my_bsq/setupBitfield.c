#include "setupBitfield.h"
#define setBit(newMap, bitfieldIndex, bitfieldPosition) (newMap[bitfieldIndex] |= (((bitfield)1 << 63) >> bitfieldPosition))

void setupBitfield(bitfieldS* map, int totalReadLength, char** string)
{
    int bitfieldIndexes = totalReadLength / 64;
    int indexReminder = ((totalReadLength % 64) != 0);
    map->fieldSize = bitfieldIndexes + indexReminder;
    map->collumnSize = totalReadLength;
    map->map = (bitfield**)malloc(sizeof(bitfield*) * map->rowSize);
    map->map[0] = fillBitfield(map, *string);
    map->maxSquare = 1;
    map->row = 0;
    map->currRow = 0;
    map->nextRow = 0;
    map->x = 0;
    map->y = 0;
    map->andRows = andRows;
    map->shiftAndRows = shiftAndRows;
    map->bitExists = bitExists;
}

bitfield* fillBitfield(bitfieldS* map, char* string)
{
    bitfield* newMap = initBitfield(map);
    int bitfieldIndex = 0;
    int bitfieldPosition = 0;
    for (int i = 0; i < map->collumnSize; i++)
    {
        if (string[i] != '.' && string[i] != 'o')
        {
            free(newMap);
            return NULL;
        }
        else if (string[i] == '.')
        {
            bitfieldIndex = i / 64;
            bitfieldPosition = i % 64;
            setBit(newMap, bitfieldIndex, bitfieldPosition);
        }
    }
    return newMap;
}

bitfield* initBitfield(bitfieldS* map)
{
    bitfield* newMap = (bitfield*)malloc(sizeof(bitfield) * map->fieldSize);
    for (int i = 0; i < map->fieldSize; i++) newMap[i] = 0;
    return newMap;
}

void freeMap(bitfieldS* map)
{
    for (int i = 0; i < map->rowSize; i++)
    {
        if (map->map[i] != NULL)
        {
            free(map->map[i]);
        }
        else
        {
            break;
        }
    }
    free(map->map);
}