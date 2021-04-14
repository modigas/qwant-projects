#include <libs.h>

bool getMaze(int fd, maze* maze);
bool checkCollumnSize(int readSize, int collumnSize);
bool checkEntrance(maze* maze, int row);
bool checkExit(maze* maze, int row);
bool checkObstacles(maze* maze, int row);
bool checkEachCell(maze* maze, int row);
bool isEntrance(maze* maze, int row, int collumn);
bool isExit(maze* maze, int row, int collumn);
bool isObstacle(maze* maze, int row, int collumn);
bool checkBorders(maze* maze, int row);