#include "../headers/cursors.h"
#include "../headers/libs.h"

extern int cycles;
extern int cycles_to_die;
extern int players[MAX_PLAYERS_NUMBE];

int bytesToInt(char *arg, int size)
{
    if(size == 4)
        return (int)((unsigned char)(arg[0]) << 24 |
                    (unsigned char)(arg[1]) << 16 |
                    (unsigned char)(arg[2]) << 8 |
                    (unsigned char)(arg[3]));
    else
        return (int)((unsigned char)(arg[0]) << 8 |
                    (unsigned char)(arg[1])) << 24 >> 24;    
}

void live(cursor** curr, char** arena)
{
    int pos = (*curr)->parameters[5];
    char arg[4];
    for(int i = 0; i < 4; i++)
    {
        arg[i] = (*arena)[pos + 1 + i];
    }
    int res = bytesToInt(arg, 4);
    for(int i = 0; i < MAX_PLAYERS_NUMBE; i++)
    {
        if(res == -players[i])
        {
            printf("Player %d is still alive!\n", players[i]);
            break;
        }
    }
    (*curr)->parameters[3] = cycles;
}

void ld(cursor** curr, char** arena)
{
    int pos = (*curr)->parameters[5];
    unsigned int n = (unsigned int)(*arena)[pos+1] << 24 >> 24;
    unsigned int args[3];
    args[0] = n >> 6;
    args[1] = n >> 4 ^ n >> 6 << 2;
    args[2] = n >> 2 ^ n >> 4 << 2;
    if(args[0] == T_DIR)
    {
        char arg[4];
        for(int i = 0; i < 4; i++)
        {
            arg[i] = (*arena)[pos + 1 + i];
        }
        int res = bytesToInt(arg, 4);
        int reg = (*arena)[pos + 1 + 4 + 1];
        (*curr)->parameters[7 + reg] = res;
    }
    else if(args[0] == T_IND)
    {
        char arg[2];
        for(int i = 0; i < 2; i++)
        {
            arg[i] = (*arena)[pos + 1 + i];
        }
        int bytePos = bytesToInt(arg, 2) % IDX_MOD;
        int reg = (*arena)[pos + 1 + 2 + 1];
        int readPos = pos + bytePos;
        char toRead[4];
        for(int k = 0; k < 4; k++)
        {
            toRead[k] = (*arena)[readPos];
        }
        int data = bytesToInt(toRead, 4);
        (*curr)->parameters[7 + reg] = data;
    }
}

void st(cursor** curr, char** arena)
{
    
}