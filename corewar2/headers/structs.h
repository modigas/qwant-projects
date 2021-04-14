#ifndef STRUCTS
#define STRUCTS

#include "corewar1.h"
#define OPTION_D "-d"
#define OPTION_N "-n"
#define INIT_MEM 512
#define READ_SIZE 128

#define OPT_ERROR                                                              \
    "Usage: ./corewar [-d <num>] [[-n <num>] <champion.cor> <...>\n    -d    " \
    "<num> : Dump memory (64 octets per line) after <num> cycles and "         \
    "exit\n    -n    <num> : Set <num> of the next player\n"

typedef struct fileNames
{
    char* name;
    int position;
} fileNames;

typedef struct options
{
    bool dump;
    int dumpSize;
} options;

typedef struct champStruct
{
    char name[PROG_NAME_LENGTH + 1];
    int  codeSize;
    char comment[COMMENT_LENGTH + 1];
    char* code;
    int position;
} champStruct;

#endif