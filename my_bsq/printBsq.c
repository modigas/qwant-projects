#include "findBsq.h"

void printBsq(int fd, char** string, bitfieldS* map)
{
    for (int i = map->y; i < map->y + map->maxSquare - 1; i++)
    {
        for (int j = map->x; j < map->x + map->maxSquare - 1; j++)
        {
            (*string)[(map->collumnSize + 1) * i + j] = 'x';
        }
    }
    write(fd, (*string), map->rowSize * (map->collumnSize + 1));
}