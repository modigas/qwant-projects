#include <getMaze.h>

bool getMaze(int fd, maze* maze)
{
    int readSize = 0;
    int i = 0;
    while ((readSize = read(fd, maze->map[i], maze->collumns + 1)) > 0)
    {
        maze->map[i][maze->collumns] = '\0';
        if (i + 1 == maze->rows) readSize += 1;
        if (!checkCollumnSize(readSize, maze->collumns + 1)) return false;
        if (i == 0 || i == maze->rows - 1)
        {
            if (!checkEachCell(maze, i)) return false;
        }
        if (!checkBorders(maze, i)) return false;
        i += 1;
    }
    if (readSize > 0 || !maze->entranceExist || maze->numExits == 0)
    {
        fprintf(stderr, "Error: incomplete maze\n");
        return false;
    }
    else
        return true;
}

bool checkBorders(maze* maze, int row)
{
    if (!checkEntrance(maze, row))
    {
        fprintf(stderr, "Error: more than 1 entrances\n");
        return false;
    }
    if (!checkExit(maze, row))
    {
        fprintf(stderr, "Error: no exits\n");
        return false;
    }
    if (!checkObstacles(maze, row))
    {
        fprintf(stderr, "Error: no obstacles\n");
        return false;
    }
    return true;
}

bool checkEntrance(maze* maze, int row)
{
    if (maze->map[row][0] == maze->entrance &&
        maze->map[row][maze->collumns - 1] == maze->entrance)
    {
        return false;
    }
    else if (maze->map[row][0] == maze->entrance)
    {
        if (!maze->entranceExist)
        {
            maze->inOutLocs[0].x = 0;
            maze->inOutLocs[0].y = row;
            maze->entranceExist = true;
        }
        else
            return false;
    }
    else if (maze->map[row][maze->collumns - 1] == maze->entrance)
    {
        if (!maze->entranceExist)
        {
            maze->inOutLocs[0].x = maze->collumns - 1;
            maze->inOutLocs[0].y = row;
            maze->entranceExist = true;
        }
        else
            return false;
    }
    return true;
}

bool checkExit(maze* maze, int row)
{
    if (maze->map[row][0] == maze->exit)
    {
        maze->numExits += 1;
        maze->inOutLocs = (inOutLocs*)realloc(
            maze->inOutLocs, sizeof(inOutLocs) * (maze->numExits + 1));
        maze->inOutLocs[maze->numExits].x = 0;
        maze->inOutLocs[maze->numExits].y = row;
    }
    if (maze->map[row][maze->collumns - 1] == maze->exit)
    {
        maze->numExits += 1;
        maze->inOutLocs = (inOutLocs*)realloc(
            maze->inOutLocs, sizeof(inOutLocs) * (maze->numExits + 1));
        maze->inOutLocs[maze->numExits].x = maze->collumns - 1;
        maze->inOutLocs[maze->numExits].y = row;
    }
    return true;
}

bool checkObstacles(maze* maze, int row)
{
    if (maze->map[row][0] == maze->obstacle ||
        maze->map[row][maze->collumns - 1] == maze->obstacle)
    {
        return true;
    }
    else
    {
        char signs[2];
        signs[0] = maze->entrance;
        signs[1] = maze->exit;
        bool first = false;
        bool second = false;
        for (int i = 0; i < 2; i++)
        {
            if (maze->map[row][0] == signs[i]) first = true;
            if (maze->map[row][maze->collumns - 1] == signs[i]) second = true;
        }
        if (first || second)
            return true;
        else
            return false;
    }
}

bool checkEachCell(maze* maze, int row)
{
    for (int i = 1; i < maze->collumns - 2; i++)
    {
        if (!isEntrance(maze, row, i) && !isExit(maze, row, i) &&
            !isObstacle(maze, row, i))
        {
            fprintf(stderr, "Error: unknown symbol\n");
            return false;
        }
    }
    return true;
}

bool isEntrance(maze* maze, int row, int collumn)
{
    if (maze->map[row][collumn] == maze->entrance)
    {
        if (!maze->entranceExist)
        {
            maze->inOutLocs[0].x = collumn;
            maze->inOutLocs[0].y = row;
            maze->entranceExist = true;
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool isExit(maze* maze, int row, int collumn)
{
    if (maze->map[row][collumn] == maze->exit)
    {
        maze->numExits += 1;
        maze->inOutLocs = (inOutLocs*)realloc(
            maze->inOutLocs, sizeof(inOutLocs) * (maze->numExits + 1));
        maze->inOutLocs[maze->numExits].x = collumn;
        maze->inOutLocs[maze->numExits].y = row;
        return true;
    }
    return false;
}

bool isObstacle(maze* maze, int row, int collumn)
{
    if (maze->map[row][collumn] == maze->obstacle)
    {
        return true;
    }
    return false;
}

bool checkCollumnSize(int readSize, int collumnSize)
{
    if (readSize != collumnSize)
    {
        fprintf(stderr, "Error: improper collumn size\n");
        return false;
    }
    return true;
}