#include <libs.h>

bool readFile(int fd, char* av, maze* maze);
bool readContent(int fd, maze* maze);
bool getRow(int fd, maze* maze);
bool getCollumn(int fd, maze* maze);
bool getSymbols(int fd, maze* maze);
void setupMaze(maze* maze);
bool getMaze(int fd, maze* maze);