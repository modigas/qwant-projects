#include "../headers/tar.h"

void foldersFromNames(char* path)
{
    char sepChar = '/';
    int len = (int)my_strlen(path), k = 0;
    char buff[100];
    for(int i = 0; i < len; i++)
    {
        if(path[i] != sepChar)
        {
            buff[k++] = path[i];
        }
        else
        {
            if(k > 1)
            {
                buff[k] = '\0';
                mkdir(buff, 511);
                for(int j = 0; j < (int)my_strlen(buff); j++) buff[j] = '\0';
                k = 0;
            }
        }
    }
}

char* lastFileName(char* path)
{
    char sepChar = '/';
    int len = (int)my_strlen(path), k = 0;
    char buff[100];
    char* str = NULL;
    for(int i = 0; i < len; i++)
    {
        if(path[i] != sepChar)
        {
            buff[k++] = path[i];
        }
        else
        {
            if(k > 1)
            {
                for(int j = 0; j < (int)my_strlen(buff); j++) buff[j] = '\0';
                k = 0;
            }
        }
    }
    buff[k] = '\0';
    str = (char*)malloc(my_strlen(buff) + 1);
    my_strcpy(str, buff);
    return str;
}

void createFile(tar_header* fileData, char** content, int* size)
{
    int newFile = 0;
    int mode = 0777;
    // int ut;
    time_t modTime;
    struct utimbuf mtime;
    // char* str = NULL;
    mode = (int)oct_to_dec(my_atol(fileData->mode, 8));
    modTime = (time_t)oct_to_dec(my_atol(fileData->mtime, 12));
    mtime.modtime = modTime;
    mtime.actime = modTime;
    switch (fileData->typeflag) {
        case '0':
            foldersFromNames(fileData->name);
            newFile = open(fileData->name, O_WRONLY | O_CREAT | O_TRUNC, mode);
            write(newFile, *content, *size);
            // ut = utime(fileData->name, &mtime);
            utime(fileData->name, &mtime);
            close(newFile);
            break;
        case '2':
            foldersFromNames(fileData->name);
            symlink(fileData->linkname, fileData->name);
            // ut = utime(fileData->name, &mtime);
            utime(fileData->name, &mtime);
            break;
        case '5':
            mkdir(fileData->name, mode);
            // ut = utime(fileData->name, &mtime);
            utime(fileData->name, &mtime);
            break;
        default:
            printf("Type is not supported\n");
            break;
    }
}

void extractFiles(char* argv[])
{
    tar_header tarHeader;
    char* name = argv[2];
    int fd = open(name, O_RDONLY);
    int j = 1, rd = 0, padding = 0;
    while(1)
    {
        rd = read(fd, tarHeader.block, 500);
        if(rd == 0 || my_strlen(tarHeader.name) == 0) break;
        int res = (int)oct_to_dec(my_atol(tarHeader.size, 12));
        char* content = (char*)malloc(res + 1);
        lseek(fd, 12, SEEK_CUR);
        rd = read(fd, content, res);
        if(res > 0) padding = BLOCKSIZE - res % BLOCKSIZE;
        else padding = 0;
        createFile(&tarHeader, &content, &res);
        free(content);
        lseek(fd, padding, SEEK_CUR);
        j++;
    }
    close(fd);
}