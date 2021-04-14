#include "../headers/main.h"

int main(int ac, char** av)
{
    int fd = 0;
    int destfd = 0;
    char* name = NULL;
    char* fileContent = NULL;
    header_t header;
    int lineError = 1;
    int index = 0;
    codeStruct* codeHeader = NULL;
    labelStruct* head = NULL;
    int indexSize = 0;
    char* codeString = NULL;

    if (!isProperFilename(&ac, &av, &name, &fd))
    {
        if (name != NULL) free(name);
        return 0;
    }
    if (!readFile(&fd, &fileContent))
    {
        free(name);
        free(fileContent);
        return 0;
    }
    if (!fillHeader(&header, &fileContent, &lineError, &index))
    {
        free(name);
        free(fileContent);
        return 0;
    }
    deleteComments(&fileContent);
    if (!fillCode(&codeHeader, &head, &fileContent, &lineError, &index))
    {
        free(name);
        free(fileContent);
        freeCode(&codeHeader);
        if (head != NULL) freeLabelList(&head);
        return 0;
    }
    codeToString(&codeHeader, &header, &codeString, &indexSize);
    destfd = open(name, O_WRONLY | O_CREAT | O_TRUNC,
                  S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    write(destfd, codeString, indexSize);
    if (codeHeader != NULL) freeCode(&codeHeader);
    free(name);
    free(fileContent);
    free(codeString);
    close(fd);
    close(destfd);
    return 0;
}