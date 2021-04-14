#include "../headers/main.h"
#include "../headers/openFiles.h"
#include "../headers/gamearena.h"

int cycles = 0;
int lastChamp = 0;
int cycles_to_die = CYCLE_TO_DIE;
int numOfChecks = 0;

int main(int ac, char** av)
{
    fileNames fileName[MAX_PLAYERS_NUMBE];
    options option;
    champStruct champions[MAX_PLAYERS_NUMBE];

    if (!getFileNameOption(ac, &av, fileName, &option))
    {
        for (int i = 0; i < MAX_PLAYERS_NUMBE; i++)
        {
            if (fileName[i].name != NULL)
                free(fileName[i].name);
        }
        return 0;
    }
    
    if (!openFiles(fileName, champions))
    {      
        for (int i = 0; i < MAX_PLAYERS_NUMBE; i++)
        {
            if (fileName[i].name != NULL)
                free(fileName[i].name);
            if (champions[i].code != NULL)
                free(champions[i].code);
        }
        return 0;
    }

    char* arena = (char*)calloc(MEM_SIZE, 1);
    placeChampCode(&arena, champions, fileName);
    // for(int i = 0; i < MEM_SIZE; i++)
    // {
    //     printf("%d", arena[i]);
    // }
        
    cursor* head = NULL;
    placeInitialCursors(&arena, champions, fileName, &head);
    printCursors(&head);
    iterOneCycle(&arena, &head);
    printf("cycles = %d\n", cycles);
    // printf("%p\n",  head);
    free2(head);

    // free(head);
    // freeCursors(head);
    free(arena);

    for (int i = 0; i < MAX_PLAYERS_NUMBE; i++)
    {
        if (fileName[i].name != NULL)
            free(fileName[i].name);
        if (champions[i].code != NULL)
            free(champions[i].code);
    }
    return 0;
}