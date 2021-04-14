#include "../headers/tar.h"

void listFiles(char* argv[])
{
    tar_header tarHeader;
    char* name = argv[2];
    int fd = open(name, O_RDONLY);
    int j = 1, rd = 0;
    while(1)
    {
        if((rd = read(fd, tarHeader.block, 500)) == 0) break;
        int res = (int)oct_to_dec(my_atol(tarHeader.size, 12));
        printf("%s\n", tarHeader.name);
        if (res == 0) lseek(fd, 12, SEEK_CUR);
        else lseek(fd, 12 + res + BLOCKSIZE - res % BLOCKSIZE, SEEK_CUR);
        j++;
    }
    close(fd);
}