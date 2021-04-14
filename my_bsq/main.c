#include "main.h"

int main(int ac, char** av)
{
    int fd = 0;
    char* string = NULL;
    bitfieldS map;

    if (!readFile(fd, ac, av[1], &string, &map))
    {
        if (string != NULL) free(string);
        return 0;
    }
    findBsq(&map);
    printBsq(fd, &string, &map);
    free(string);
    freeMap(&map);
    return 0;
}