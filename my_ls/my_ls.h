#include <sys/stat.h>
#include <stdbool.h>
// #pragma once

typedef struct {
    char* name;
    time_t modTime;
} file;

typedef struct {
    // char** content;
    int numObjects;
    char* path;
    time_t modTime;
    file* files;
} folder;

// folder *folders;
// int size = 0;
// int ndirall = 0;

folder *folders;
extern int size;
extern int ndirall;

bool Option_A(char**, int);
bool Option_R(char**, int);
bool Option_T(char**, int);
bool Option(char**, int);
bool IsFile(char *);
bool IsFolder(char *);
bool FileExists(char *);
int NumOfNonExist(char **, int);
int numObjects(char*, int);
int numDirectories(char*, int);
void SortByNameStruct(folder*, int);
void SortByTimeStruct(folder*, int);
void SortByName(file*, int);
void SortByTime(file*, int);
void SortByNameArr(char **, int);
void SortByTimeArr(char **, int, int);
void SortByExist(char **, int);
void RecordDirectories(char*, int, int, int);
void FreeStruct(int);
int NumOfWords(char **, int);
void PrintDir(char*, int, int, int, int);
void my_ls(int, char**);
