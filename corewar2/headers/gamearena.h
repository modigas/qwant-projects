#include		"../headers/corewar1.h"
#include        "../headers/structs.h"
#include        "../headers/cursors.h"

void initArena(char** arena);
int numPlayers(fileNames*);
void placeChampCode(char**, champStruct*, fileNames*);
void placeInitialCursors(char**, champStruct*, fileNames*, cursor**);
bool iterOneCycle(char**, cursor**);
