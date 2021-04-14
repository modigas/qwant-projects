#include		"../headers/corewar1.h"

typedef struct cursor
{
    // parameters[0]    - unique number;
    // parameters[1]    - carry (0/1);
    // parameters[2]    - current operation;
    // parameters[3]    - last cycle when live was executed;
    // parameters[4]    - cycles remaining for execution;
    // parameters[5]    - current position;
    // parameters[6]    - bytes to jump ;
    // parameters[7:22] - reg[REG_NUMBER];
    int parameters[NUM_PARAMETERS];
    struct cursor* next;
} cursor;

cursor* getNewCursor(int[]);
void pushCursor(cursor**, int[]);
int searchCursor(cursor**, int[]);
void deleteCursor(cursor**, int);
void initCursor(cursor*);
void initCursors(cursor**);
void freeCursors(cursor*);
void printCursors(cursor**);
void free2(cursor*);
