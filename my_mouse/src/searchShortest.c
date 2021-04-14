#include <searchShortest.h>

bool searchShortest(maze* maze)
{
    struct hash closedList = hash.new();
    struct queue frontier = queue.new();
    struct point goal;
    bool breakLoop = false;
    struct point start = {maze->inOutLocs[0].x, maze->inOutLocs[0].y};
    frontier.put(&frontier, start);
    closedList.insert(&closedList, start, start);
    while (!frontier.isEmpty(&frontier))
    {
        struct point current = frontier.front(&frontier);
        frontier.pop(&frontier);
        if (isGoal(maze, &goal, &current, &breakLoop)) break;
        parseNeighbors(maze, &closedList, &frontier, &current);
    }
    if (!breakLoop)
    {
        fprintf(stderr, "Error: the goal is unreachable\n");
        freeAll(maze, &closedList, &frontier);
        return false;
    }
    int count = 0;
    getPath(maze, &closedList, &goal, &start, &count);
    printPath(maze, count);
    freeAll(maze, &closedList, &frontier);
    return true;
}

bool isValid(maze* maze, int row, int col)
{
    return ((row >= 0) && (row < maze->rows) && (col >= 0) &&
            (col < maze->collumns));
}

bool isGoal(maze* maze, struct point* goal, struct point* current,
            bool* breakLoop)
{
    for (int i = 1; i <= maze->numExits; i++)
    {
        if (current->x == maze->inOutLocs[i].x &&
            current->y == maze->inOutLocs[i].y)
        {
            (*goal) = (*current);
            (*breakLoop) = true;
            return true;
        }
    }
    return false;
}

void parseNeighbors(maze* maze, struct hash* closedList, struct queue* frontier,
                    struct point* current)
{
    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};
    for (int i = 0; i < 4; i++)
    {
        int row = current->y + rowNum[i];
        int col = current->x + colNum[i];
        struct point toFind = {.x = col, .y = row};
        struct point temp = closedList->find(closedList, toFind);
        struct point end = closedList->end();
        if (isValid(maze, row, col) &&
            (maze->map[row][col] == maze->emptySpace ||
             maze->map[row][col] == maze->exit) &&
            (temp.x == end.x) && (temp.y == end.y))
        {
            frontier->put(frontier, toFind);
            closedList->insert(closedList, toFind, (*current));
        }
    }
}

void getPath(maze* maze, struct hash* closedList, struct point* goal,
             struct point* start, int* count)
{
    bool first = true;
    while ((goal->x != start->x) || (goal->y != start->y))
    {
        if (first)
        {
            first = false;
            (*goal) = closedList->find(closedList, (*goal));
            continue;
        }
        (*count) += 1;
        maze->map[goal->y][goal->x] = maze->path;
        (*goal) = closedList->find(closedList, (*goal));
    }
}

void printPath(maze* maze, int count)
{
    for (int i = 0; i < maze->rows; i++)
    {
        for (int j = 0; j < maze->collumns; j++)
        {
            printf("%c", maze->map[i][j]);
        }
        printf("\n");
    }
    printf("%d STEPS!\n", count);
}

void freeAll(maze* maze, struct hash* closedList, struct queue* frontier)
{
    closedList->destroy(closedList);
    frontier->destroy(frontier);
    for (int i = 0; i < maze->rows; i++)
    {
        free(maze->map[i]);
    }
    free(maze->map);
    free(maze->inOutLocs);
}