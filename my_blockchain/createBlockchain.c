#include "createBlockchain.h"
#include <fcntl.h>

int updateFile(int fd){
    fd = open("blockchain.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO );
    return fd;
}

void createBlockchain(int fd, bool NewFile)
{
    BstNode* root = NULL;
    State CurrentState;
    CurrentState.size = 0;
    CurrentState.sync = false;
    bool isTrueSync = true;
    bool isError = false;

    if (!NewFile)
    {
        int size = 0;
        size = readFile(fd, &root, &CurrentState);
        fd = updateFile(fd);
        CurrentState.size = 0;
        CurrentState.sync = false;
        isTrueSync = true;
        syncCheck(&root, &root->bid, &CurrentState, &isTrueSync);
    }

    while (1)
    {
        printState(fd, &CurrentState);
        CommandContainer Inputs;
        Node* tempList = NULL;
        readInput(&Inputs, &isError);
        if (isError) continue;
        int nid = 0;

        for (int i = 0; i < Inputs.count; i++)
        {
            switch (Inputs.action)
            {
                case ADD:
                    switch (Inputs.type)
                    {
                        case NODE:
                            if (isInt(&Inputs.nids[i]))
                            {
                                nid = strToNum(Inputs.nids[i]);
                                insertNid(&root, nid);
                            }
                            else
                            {
                                fprintf(stderr, "the node must be an integer\n");
                            }
                            free(Inputs.nids[i]);
                            if (i == Inputs.count - 1) free(Inputs.nids);
                            break;
                        case BLOCK:
                            if (i == Inputs.count - 1)
                            {
                                free(Inputs.bids[0]);
                                free(Inputs.bids);
                                if (Inputs.count != 1) free(Inputs.nids);
                                else fprintf(stderr, "Please specify nodes\n");
                                break;
                            }
                            if (isInt(&Inputs.nids[i]))
                            {
                                nid = strToNum(Inputs.nids[i]);
                            }
                            else if (Inputs.nids[i][0] == '*')
                            {
                                insertBlockToAllNids(&root, &Inputs.bids[0]);
                                free(Inputs.nids[i]);
                                continue;
                            }
                            else
                            {
                                fprintf(stderr, "the node must be an integer or '*'\n");
                                free(Inputs.nids[i]);
                                continue;
                            }
                            free(Inputs.nids[i]);
                            BstNode* tempNid = NULL;
                            tempNid = searchNid(&root, nid);
                            if (tempNid == NULL)
                            {
                                fprintf(stderr, "The node %d does not exist\n", nid);
                                continue;
                            }
                            insertBlock(&tempNid->bid, &Inputs.bids[0]);
                            break;
                        default:
                            printf("Error\n");
                            break;
                    }
                    break;
                case RM:
                    switch (Inputs.type)
                    {
                        case NODE:
                            if (isInt(&Inputs.nids[i]))
                            {
                                nid = strToNum(Inputs.nids[i]);
                            }
                            else if (Inputs.nids[i][0] == '*')
                            {
                                removeAllNids(&root);
                                free(Inputs.nids[i]);
                                if (i == Inputs.count - 1)
                                    free(Inputs.nids);
                                continue;
                            }
                            else
                            {
                                fprintf(stderr, "the node must be an integer or '*'\n");
                                free(Inputs.nids[i]);
                                continue;
                            }
                            deleteNid(&root, nid);
                            free(Inputs.nids[i]);
                            if (i == Inputs.count - 1) free(Inputs.nids);
                            break;
                        case BLOCK:
                            deleteBlock(&root, &Inputs.bids[i]);
                            free(Inputs.bids[i]);
                            if (i == Inputs.count - 1) free(Inputs.bids);
                            break;
                        default:
                            printf("Error\n");
                            break;
                    }
                    break;
                case LS:
                    printTree(&root, Inputs.type);
                    break;
                case SYNC:
                    collectBids(&root, &tempList);
                    syncBids(&root, &tempList);
                    deleteAllBlocks(&tempList);
                    break;
                case QUIT:
                    writeToFile(&root, fd);
                    removeAllNidsS(&root);
                    quitPrompt();
                    break;
                default:
                    printf("Error\n");
                    break;
            }
        }
        if (Inputs.action == QUIT) break;
        CurrentState.size = 0;
        CurrentState.sync = false;
        isTrueSync = true;
        syncCheck(&root, &root->bid, &CurrentState, &isTrueSync);
    }
}