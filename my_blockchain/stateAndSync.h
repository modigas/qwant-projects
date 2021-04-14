#include "libs.h"
#include "structs.h"

void printState(int fd, State* CurrentState);
void insertBlockW(Node** root, char** bids);
void copyBlocks(Node** destBids, Node** bids);
void collectBids(BstNode** root, Node** tempList);
void syncBids(BstNode** root, Node** tempList);
Node* getNewBlock(char** bid);
void printTree(BstNode** root, int type);
void printLinkedList(Node** bid);
void syncCheck(BstNode** root, Node** bid, State* CurrentState, bool* isTrueSync);
bool compareBlock(Node** next, Node** current);