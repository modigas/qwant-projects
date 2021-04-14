#include <main.h>

int main(int ac, char** av)
{
    int fd = 0;
    maze maze;
    if (ac < 2)
    {
        fprintf(stderr, "Error: follow the format ./my_mouse [file]\n");
        return EXIT_FAILURE;
    }
    for (int i = 2; i <= ac; i++)
    {
        if (!readFile(fd, av[i - 1], &maze))
        {
            printf("\n");
            continue;
        }
        if (!searchShortest(&maze))
        {
            printf("\n");
            continue;
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}