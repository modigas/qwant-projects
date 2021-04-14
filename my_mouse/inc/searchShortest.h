#include <libs.h>

bool searchShortest(maze* maze);
bool isValid(maze* maze, int row, int col);
bool isGoal(maze* maze, struct point* goal, struct point* current,
            bool* breakLoop);
void parseNeighbors(maze* maze, struct hash* closedList, struct queue* frontier,
                    struct point* current);
void getPath(maze* maze, struct hash* closedList, struct point* goal,
             struct point* start, int* count);
void printPath(maze* maze, int count);
void freeAll(maze* maze, struct hash* closedList, struct queue* frontier);