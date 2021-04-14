#include "findBsq.h"

void findBsq(bitfieldS* map)
{
    while (map->row + map->maxSquare <= map->rowSize)
    {
        shiftCompare(map);
        shiftCompareNext(map);
        compareTwoRows(map);
        dotExists(map);
    }
}

void shiftCompare(bitfieldS* map)
{
    while (map->currRow < map->maxSquare - 1)
    {
        map->shiftAndRows(map->fieldSize, &(map->map[map->row + map->currRow]));
        map->currRow += 1;
    }
}

void shiftCompareNext(bitfieldS* map)
{
    while (map->nextRow < map->maxSquare - 1)
    {
        map->shiftAndRows(map->fieldSize,
                          &(map->map[map->row + map->maxSquare - 1]));
        map->nextRow += 1;
    }
}

void compareTwoRows(bitfieldS* map)
{
    int temp = 1;
    while (temp < map->maxSquare)
    {
        map->andRows(map->fieldSize, map->map[map->row],
                     map->map[map->row + temp]);
        temp += 1;
    }
}

void dotExists(bitfieldS* map)
{
    if (map->bitExists(map->map[map->row], map))
    {
        map->currRow = 0;
        map->nextRow = 0;
        map->maxSquare += 1;
    }
    else
    {
        int temp = 0;
        map->row += 1;
        while ((map->row + map->maxSquare <= map->rowSize) &&
               (temp < map->maxSquare - 1))
        {
            if (map->row + map->maxSquare <= map->rowSize)
            {
                map->shiftAndRows(map->fieldSize,
                                  &(map->map[map->row + map->maxSquare - 1]));
            }
            temp += 1;
        }
    }
}