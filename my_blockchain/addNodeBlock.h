#include "libs.h"
#include "structs.h"

bool isInt(char** string);
int strToNum(char* string);
void insertNid(BstNode** root, int nid);
BstNode* getNewNode(int nid);
void insertBlockToAllNids(BstNode** root, char** bids);
void insertBlock(Node** root, char** bids);
Node* getNewBlock(char** bid);
void getNewString(char** string, int start, int end);
BstNode* searchNid(BstNode** root, int nid);
