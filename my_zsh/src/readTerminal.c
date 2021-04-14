#include <readTerminal.h>

char* readTerminal()
{
    size_t readLength = 0;
    size_t buffSize = INIT_SIZE;
    char* buffer = getString(buffSize);
    if ((readLength = getline(&buffer, &buffSize, stdin)) == 1)
    {
        free(buffer);
        return NULL;
    }
    if (strlen(buffer) == 0)
    {
        free(buffer);
        printf("\n");
        exit(EXIT_SUCCESS);
    }
    buffer[strlen(buffer) - 1] = '\0';
    return buffer;
}