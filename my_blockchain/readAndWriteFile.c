#include "readAndWriteFile.h"

void cleanString(char* str, int size)
{
    for(int i = 0; i < size; i++)
    {
        str[i] = '\0';
    }
}

int numDig(int num)
{
    if (num == 0) return 1;
    int count = 0;
    while(num != 0)
    {
        num /= 10;
        count++;
    }
    return count;
}

void my_itoa(int num, char* res)
{
    int nd = numDig(num);
    for(int i = nd-1; i >= 0; i--)
    {
        res[i] = (num%10) + '0';
        num /= 10;
    }
    res[nd] = '\0';
}

void recordLinkedList(Node** bid, int fd) {
    Node* temp = *bid;
    char sp = ' ';
    while (temp != NULL) {
        write(fd, temp->string, strlen(temp->string));
        write(fd, &sp, 1);
        temp = temp->next;
    }
    char nl = '\n';
    write(fd, &nl, 1);
}

void writeToFile(BstNode** root, int fd) {
    char sp = ' ';
    if (*root == NULL)
        return;
    writeToFile(&(*root)->left, fd);
    int nd = numDig((*root)->nid);
    char temp[nd + 1];
    my_itoa((*root)->nid, temp);
    write(fd, temp, nd);
    write(fd, &sp, 1);
    recordLinkedList(&(*root)->bid, fd);
    writeToFile(&(*root)->right, fd);
}

int readFile(int fd, BstNode** root, State* CurrentState){
    char c;
    int size = 0;
    int nid = 0;
    int numBid = 0;
    int space = 0;
    char buff[100];
    char bids[100];
    int rd = 0;
    int i = 0, j = 0;
    while((rd = read(fd, &c, 1)) != 0)
    {
        if( c != '\n')
        {
            if( c != ' ' && space == 0)
            {
                buff[i] = c;
                i++;
            }
            if( c != ' ' && space > 0)
            {
                bids[j] = c;
                j++;
                numBid++;
            }
            if( c == ' ' && space == 0)
            {
                buff[i] = '\0';
                nid = strToNum(buff);
                insertNidS(root, nid);
                space++;
            }
            if( c == ' ' && space > 0 && numBid > 0)
            {  
                bids[j] = '\0';
                char* bid = malloc(strlen(bids)+1);
                strcpy(bid, bids);
                insertBlockS(&(searchNid(root, nid))->bid, &bid);
                free(bid);
                cleanString(bids, j);
                j = 0;
                space++;
                numBid++;
            }
        }
        if( c == '\n')
        {
            cleanString(buff, i);
            cleanString(bids, j);
            i = 0;
            j = 0;
            space = 0;
            numBid = 0;
        }
        size++;
    }
    return size;
}