#ifndef STRUCTS
#define STRUCTS

#define READ_SIZE 512
#define INIT_MEM 512
#define CODE_LIVE 1
#define CODE_LOAD 2
#define CODE_STORE 3
#define CODE_ADD 4
#define CODE_SUB 5
#define CODE_AND 6
#define CODE_OR 7
#define CODE_XOR 8
#define CODE_ZJUMP 9
#define CODE_LOADI 10
#define CODE_STI 11
#define CODE_FORK 12
#define CODE_LLD 13
#define CODE_LLDI 14
#define CODE_LFORK 15
#define CODE_AFF 16
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"
#define TAB 9

#define DIR_TYPE_CODE 2
#define REG_TYPE_CODE 1
#define IND_TYPE_CODE 3
#define PADDING 2

#define CODE_SIZE 1
#define CODE_TYPE_SIZE 1
#define DIR_SIZE_2 2
#define DIR_SIZE_4 4
#define IND_SIZE_2 2
#define REG_SIZE_1 1

#define REGULAR_CHAR 'r'

typedef struct codeStruct
{
    int code;
    int codeType;
    int arg1;
    int arg2;
    int arg3;
    int argSize1;
    int argSize2;
    int argSize3;
    char* label1;
    char* label2;
    char* label3;
    int codeTotalSize;
    int thisCodeSize;
    struct codeStruct* next;
} codeStruct;

typedef struct labelStruct
{
    int totalMemory;
    char* name;
    struct labelStruct* next;
} labelStruct;

#endif