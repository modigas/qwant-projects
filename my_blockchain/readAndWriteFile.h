#include "libs.h"
#include "structs.h"

void cleanString(char* str, int size);
int numDig(int num);
void my_itoa(int num, char* res);
void recordLinkedList(Node** bid, int fd);
void writeToFile(BstNode** root, int fd);
int readFile(int fd, BstNode** root, State* CurrentState);
// void readFile(int fd, BstNode** root, State* CurrentState);
int strToNum(char* string);
void insertNidS(BstNode** root, int nid);
BstNode* searchNid(BstNode** root, int nid);
void insertBlockS(Node** root, char** bids);