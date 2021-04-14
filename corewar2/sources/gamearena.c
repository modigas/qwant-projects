#include "../headers/libs.h"
#include "../headers/myString.h"
#include "../headers/gamearena.h"

extern int cycles;
int players[MAX_PLAYERS_NUMBE] = {0,0,0,0};

void initArena(char** arena)
{
    initString(arena, 0, MEM_SIZE);
}

int numPlayers(fileNames* fileName)
{
    int count = 0;
    for(int i = 0; i < MAX_PLAYERS_NUMBE; i++)
        if( fileName[i].name != NULL) count++;
    return count;
}

void placeChampCode(char** arena, champStruct* champs, fileNames* fileName)
{
    int np = numPlayers(fileName);
    int offset = MEM_SIZE/np;
    for(int i = 0; i < np; i++)
    {
        int codeSize = (int)strlen(champs[i].code);
        int pos = i * offset;
        int l = 0;
        for(int j = pos; j < codeSize + pos; j++)
        {
            (*arena)[j] = champs[i].code[l];
            l++;
        }
    }
}

int getCycles(int command)
{
    switch (command) {
        case 1:
        // alive
            return 10;
        case 2:
        // load
            return 5;
        case 3:
        // store
            return 5;
        case 4:
        // addition
            return 10;
        case 5:
        // subtraction
            return 10;
        case 6:
        // bitwise AND
            return 6;
        case 7:
        // bitwise OR
            return 6;
        case 8:
        // bitwise XOR
            return 6;
        case 9:
        // jump is non-zero
            return 20;
        case 10:
        // load index
            return 25;
        case 11:
        // store index
            return 25;
        case 12:
        // fork
            return 800;
        case 13:
        // long load
            return 10;
        case 14:
        // long load index
            return 50;
        case 15:
        // long fork
            return 1000;
        case 16:
        // aff
            return 2;
        default:
        // incorrect command
            return -1;
    }
}

int checkOperation(int command)
{
    if(command >= 1 && command <= 16)
        return 1;
    return -1;
}

int bytesToJump(int command, char** arena, int pos)
{
    return 1;
}

void placeInitialCursors(char** arena, champStruct* champs, fileNames* fileName, cursor** head)
{
    int np = numPlayers(fileName);
    int offset = MEM_SIZE/np;
    for(int i = 0; i < np; i++)
    {
        players[i] = champs->position;
        int params[NUM_PARAMETERS];
        for(int j = 0; j < NUM_PARAMETERS; j++)
            params[j] = 0;
        params[0] = i;
        params[2] = (checkOperation((*arena)[i*offset]) == 1)?(*arena)[i*offset]:-1;
        params[4] = getCycles(params[2]);
        params[5] = i * offset;
        // params[6] = bytesToJump(params[2], arena, i*offset);
        params[7] = - champs[i].position;
        pushCursor(head, params);
    }
    cycles++;
}

bool checkArgCode(int opCode)
{
    if(opCode != 1 && opCode != 9 && opCode != 12 && opCode != 15)
    {
        return true;
    }
    return false;
}

bool checkArgOrder(unsigned int args[3], int opCode)
{
    switch (opCode) {
        case 2:
            if((args[0] == T_DIR || args[0] == T_IND) && args[1] == T_REG && args[2] == 0)
                return true;
            break;
        case 3:
            if(args[0] == T_REG && (args[1] == T_REG || args[1] == T_IND) && args[2] == 0)
                return true;
            break;
        case 4:
            if(args[0] == T_REG && args[1] == T_REG && args[2] == T_REG)
                return true;
            break;
        case 5:
            if(args[0] == T_REG && args[1] == T_REG && args[2] == T_REG)
                return true;
            break;
        case 6:
            if((args[0] == T_REG || args[0] == T_DIR || args[0] == T_IND) && (args[1] == T_REG || args[1] == T_DIR || args[1] == T_IND) && args[2] == T_REG)
                return true;
            break;
        case 7:
            if((args[0] == T_REG || args[0] == T_DIR || args[0] == T_IND) && (args[1] == T_REG || args[1] == T_DIR || args[1] == T_IND) && args[2] == T_REG)
                return true;
            break;
        case 8:
            if((args[0] == T_REG || args[0] == T_DIR || args[0] == T_IND) && (args[1] == T_REG || args[1] == T_DIR || args[1] == T_IND) && args[2] == T_REG)
                return true;
            break;
        case 10:
            if((args[0] == T_REG || args[0] == T_DIR || args[0] == T_IND) && (args[1] == T_REG || args[1] == T_DIR) && args[2] == T_REG)
                return true;
            break;
        case 11:
            if(args[0] == T_REG && (args[1] == T_REG || args[1] == T_DIR || args[1] == T_IND) && (args[2] == T_REG || args[2] == T_DIR))
                return true;
            break;
        case 13:
            if((args[0] == T_DIR || args[0] == T_IND) && args[1] == T_REG && args[2] == 0)
                return true;
            break;
        case 14:
            if((args[0] == T_REG || args[0] == T_DIR || args[0] == T_IND) && (args[1] == T_REG || args[1] == T_DIR) && args[2] == T_REG)
                return true;
            break;
        case 16:
            if(args[0] == T_REG)
                return true;
            break;
    }
    return false;
}

int toJump(int opCode, int arg)
{
    if (arg == T_REG) return 1;
    if((opCode >= 1 && opCode <= 8) || opCode == 13 || opCode == 16)
    {
        if(arg == T_DIR) return 4;
    }
    else
    {
        return 2;
    }
    return 0;
}

bool checkRegValidity(unsigned int args[3], int opCode, int pos, char** arena)
{
    int reg = 0;
    int jmp = 0;
    int start = pos + 1;
    for(int j = 0; j < 3; j++)
    {
        jmp = toJump(opCode, args[j]);
        start += jmp;
        if(args[j] == T_REG)
        {
            reg = (*arena)[start];
            if(reg <= 0 || reg >= REG_NUMBER)
                return false;
        }
    }
    return true;
}

void checkArguments(int currOp, int currPos, char** arena, cursor** cr)
{
    if((*arena)[currPos] == currOp)
    {
        if(checkArgCode(currOp))
        {
            // For commands that have type of arguments code 
            unsigned int n = (unsigned int)(*arena)[currPos+1] << 24 >> 24;
            unsigned int tail = n ^ n >> 2 << 2;
            if(tail == 0)
            {
                unsigned int args[3];
                args[0] = n >> 6;
                args[1] = n >> 4 ^ n >> 6 << 2;
                args[2] = n >> 2 ^ n >> 4 << 2;
                if(checkArgOrder(args, currOp))
                {
                    if(checkRegValidity(args, currOp, currPos, arena))
                    {

                        // Execute command(i.e. shift cursor to the next position and and fill new data)
                    }
                    // Move cursor to a new position
                    
                }
            }
            else
            {
                // jump N number of bytes to the next operation
            }
        }
        else
        {
            // skip one byte and set counter to 0
        }
    }
}

bool iterOneCycle(char** arena, cursor** head)
{
    // extern int cycles;
    cursor* curr = *head;
    int i = 0;
    while(curr != NULL)
    {
        // Checks whether it's time to execute operation
        if(curr->parameters[4] != 0)
        {
            int pos = curr->parameters[5] % MEM_SIZE;
            checkArguments(curr->parameters[2], pos, arena, &curr);
        }
        // cycles++;
        curr = curr -> next;
        i++;
        // *head = (*head)->next;
        // (*head)->parameters[2] = (*arena)[(*head)->parameters[]]
    }
    cycles++;
    return true;
}
