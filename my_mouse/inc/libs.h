#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <binaryHeap.h>
#include <queue.h>
#include <hash.h>
#include <commonNode.h>
#include <utils.h>

typedef struct inOutLocs
{
    int x;
    int y;
} inOutLocs;

typedef struct maze
{
    int rows;
    int collumns;
    char** map;
    char obstacle;
    char emptySpace;
    char path;
    char entrance;
    char exit;
    bool entranceExist;
    struct inOutLocs* inOutLocs;
    int numExits;
} maze;

#endif