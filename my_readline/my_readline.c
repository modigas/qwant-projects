#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define READLINE_READ_SIZE 1

char* my_strcat(char* str, const char* cat)
{
    int i, j;
    for (i = 0; str[i] != '\0'; i++)
        ;
    for (j = 0; cat[j] != '\0'; j++) str[i + j] = cat[j];

    str[i + j] = '\0';
    return str;
}

char* appendChar(char* str, char c)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
        ;
    str[i] = c;
    str[i + 1] = '\0';
    return str;
}

int fileSize(int fd)
{
    int size = 0;
    char c;
    while (read(fd, &c, 1))
    {
        size++;
    }
    return size;
}

int checkNewLine(char* str)
{
    int count = 0;
    for (int i = 0; i < READLINE_READ_SIZE; i++)
    {
        if (str[i] == '\n') count++;
    }
    return count;
}

void clearArr(char* rem, int size)
{
    for (int i = 0; i < size; i++)
    {
        rem[i] = '\0';
    }
}

char* my_readline(int fd)
{
    int fr, condNL = 0;
    char buff[BUFSIZ];
    buff[0] = '\0';
    int last = 0;
    static char rem[READLINE_READ_SIZE + 1];
    if (strlen(rem) == 0) rem[0] = '\0';

    int n = strlen(rem);
    int end = 0;
    char str[READLINE_READ_SIZE + 1];
    if (n > 0)
    {
        my_strcat(buff, rem);
        clearArr(rem, n);
    }
    int iter = 0;
    while (1)
    {
        if (condNL) break;
        fr = read(fd, str, READLINE_READ_SIZE);
        if (fr < 0) return NULL;
        str[fr] = '\0';
        if (fr < READLINE_READ_SIZE) last = 1;
        if (checkNewLine(str) == 0 && fr == READLINE_READ_SIZE)
        {
            my_strcat(buff, str);
        }
        else
        {
            for (int i = 0; i < fr; i++)
            {
                if (str[i] != '\n' && !condNL)
                {
                    appendChar(buff, str[i]);
                }
                if (str[i] == '\n')
                {
                    condNL++;
                    if (condNL == 1) str[i] = '\0';
                }
                if (condNL)
                {
                    appendChar(rem, str[i]);
                }
            }
            if (last && fr == 0) end = 1;
        }
        iter++;
        if (fr == 0) break;
    }
    if (end)
    {
        return NULL;
    }
    else
    {
        char* res = (char*)malloc(strlen(buff) + 1);
        strcpy(res, buff);
        res[strlen(res)] = '\0';
        return res;
    }
}

// int main(int argc, char* argv[]) {
//     char* str = NULL;
//     int fd = open(argv[1], O_RDONLY);
//     if (fd < 0) exit(1);
//     while((str = my_readline(fd)) != NULL) {
//         printf("%s\n", str);
//         free(str);
//     }
//     close(fd);
//     return 0;
// }