#include <readFile.h>

bool readFile(int fd, char* av, maze* maze)
{
    if ((fd = open(av, O_RDONLY)) < 0)
    {
        fprintf(stderr, "Error: the file does not exist\n");
        return false;
    }
    if (!readContent(fd, maze))
    {
        return false;
    }
    return true;
}

bool readContent(int fd, maze* maze)
{
    if (!getRow(fd, maze) || !getCollumn(fd, maze) || !getSymbols(fd, maze))
    {
        return false;
    }
    setupMaze(maze);
    if (!getMaze(fd, maze))
    {
        free(maze->inOutLocs);
        for (int i = 0; i < maze->rows; i++)
        {
            free(maze->map[i]);
        }
        free(maze->map);
        return false;
    }
    return true;
}

bool getRow(int fd, maze* maze)
{
    int readSize = 0;
    maze->rows = 0;
    char buff[2] = {'\0'};
    while (((readSize = read(fd, &buff, 1)) != 0) && (buff[0] != 'x'))
    {
        if (isInt(buff[0]))
        {
            maze->rows *= 10;
            maze->rows += atoi(buff);
        }
        else
        {
            fprintf(stderr, "Error: missing input\n");
            return false;
        }
    }
    if (readSize != 0)
        return true;
    else
    {
        fprintf(stderr, "Error: missing input\n");
        return false;
    }
}

bool getCollumn(int fd, maze* maze)
{
    int readSize = 0;
    maze->collumns = 0;
    char buff[2] = {'\0'};
    while (((readSize = read(fd, buff, 1)) != 0) && (isInt(buff[0])))
    {
        maze->collumns *= 10;
        maze->collumns += atoi(buff);
    }
    if (readSize != 0)
    {
        maze->obstacle = buff[0];
        return true;
    }
    else
    {
        fprintf(stderr, "Error: missing input\n");
        return false;
    }
}

bool getSymbols(int fd, maze* maze)
{
    int readSize = 0;
    char buff;
    int count = 0;
    while (((readSize = read(fd, &buff, 1)) != 0) && (buff != '\n') &&
           (count != 4))
    {
        if (count == 0) maze->emptySpace = buff;
        if (count == 1) maze->path = buff;
        if (count == 2) maze->entrance = buff;
        if (count == 3) maze->exit = buff;
        count += 1;
    }
    if ((readSize == 0) || (buff != '\n') || (count != 4))
    {
        fprintf(stderr, "Error: missing input\n");
        return false;
    }
    else
        return true;
}

void setupMaze(maze* maze)
{
    maze->inOutLocs = (inOutLocs*)malloc(sizeof(inOutLocs));
    maze->entranceExist = false;
    maze->numExits = 0;
    maze->map = (char**)malloc(sizeof(char*) * (maze->rows + 1));
    for (int i = 0; i < maze->rows; i++)
    {
        maze->map[i] = (char*)malloc(sizeof(char) * maze->collumns + 1);
    }
}