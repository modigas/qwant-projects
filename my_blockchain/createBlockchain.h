#include "libs.h"
#include "structs.h"

// void readFile(int fd, BstNode** root, State* CurrentState);
int readFile(int fd, BstNode** root, State* CurrentState);
void syncCheck(BstNode** root, Node** bid, State* CurrentState, bool* isTrueSync);
void printState(int fd, State* CurrentState);
void readInput(CommandContainer* Inputs, bool* isError);
bool isInt(char** string);
int strToNum(char* string);
void insertNid(BstNode** root, int nid);
void insertBlockToAllNids(BstNode** root, char** bids);
BstNode* searchNid(BstNode** root, int nid);
void insertBlock(Node** root, char** bids);
void removeAllNids(BstNode** root);
void deleteNid(BstNode** root, int nid);
void deleteBlock(BstNode** root, char** string);
void printTree(BstNode** root, int type);
void collectBids(BstNode** root, Node** tempList);
void syncBids(BstNode** root, Node** tempList);
void deleteAllBlocks(Node** root);
void writeToFile(BstNode** root, int fd);
void quitPrompt();
void removeAllNidsS(BstNode** root);