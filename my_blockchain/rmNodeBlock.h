#include "libs.h"
#include "structs.h"

void removeAllNids(BstNode** root);
void removeAllNidsS(BstNode** root);
void deleteNid(BstNode** root, int nid);
void deleteAllBlocks(Node** root);
BstNode* findMinNode(BstNode* root);
void insertBlock(Node** root, char** bids);
void deleteBlock(BstNode** root, char** string);
void deleteSingleBlock(Node** bid, char** string);
void insertBlockS(Node** root, char** bids);
void deleteNidS(BstNode** root, int nid);