#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "my_ls.h"

bool Option_A(char *args[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strncmp(args[i], "-", 1) == 0)
        {
            char *temp = args[i];
            while (*temp != '\0')
            {
                if (*temp == 'a')
                {
                    return true;
                }
                temp++;
            }
        }
    }
    return false;
}

bool Option_T(char *args[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strncmp(args[i], "-", 1) == 0)
        {
            char *temp = args[i];
            while (*temp != '\0')
            {
                if (*temp == 't')
                {
                    return true;
                }
                temp++;
            }
        }
    }
    return false;
}

bool Option_R(char *args[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strncmp(args[i], "-", 1) == 0)
        {
            char *temp = args[i];
            while (*temp != '\0')
            {
                if (*temp == 'R')
                {
                    return true;
                }
                temp++;
            }
        }
    }
    return false;
}

bool Options(char *args[], int n)
{
    if (Option_R(args, n) || Option_T(args, n) || Option_A(args, n))
        return true;
    return false;
}

bool IsFile(char *name)
{
    struct stat path_stat;
    stat(name, &path_stat);
    if ((S_ISREG(path_stat.st_mode)))
        return true;
    return false;
}

bool IsFolder(char *name)
{
    struct stat path_stat;
    stat(name, &path_stat);
    if ((S_ISDIR(path_stat.st_mode)))
        return true;
    return false;
}

bool FileExists(char *name)
{
    struct stat file;
    return (stat(name, &file) == 0);
}

int NumOfNonExist(char *argv[], int argc)
{
    int count = 0;
    for (int i = 1; i < argc; i++)
    {
        if (!FileExists(argv[i]))
            count++;
    }
    return count;
}

int numObjects(char *name, int flagA)
{
    DIR *dir = opendir(name);
    if (!dir)
        return 0;
    int count = 0;
    struct dirent *sd;
    while ((sd = readdir(dir)))
    {
        if (flagA)
        {
            count++;
        }
        else
        {
            if ((strncmp(sd->d_name, ".", 1) != 0))
            {
                count++;
            }
        }
    }
    closedir(dir);
    return count;
}

int numDirectories(char *name, int flagA)
{
    DIR *dir = opendir(name);
    if (!dir)
        return 0;
    struct dirent *sd;
    int count = 0;
    while ((sd = readdir(dir)))
    {
        if (sd->d_type == DT_DIR)
        {
            if (flagA)
            {
                count++;
            }
            else
            {
                if ((strncmp(sd->d_name, ".", 1) != 0))
                {
                    count++;
                }
            }
        }
    }
    closedir(dir);
    return count;
}

void SortByNameStruct(folder *f, int n)
{
    bool swap = false;
    while (1)
    {
        swap = false;
        for (int i = 0; i < n - 1; i++)
        {
            folder f1 = *(f + i);
            folder f2 = *(f + i + 1);
            char *n1 = f1.path;
            char *n2 = f2.path;
            if (strcmp(n1, n2) > 0)
            {
                *(f + i) = f2;
                *(f + i + 1) = f1;
                swap = true;
            }
        }
        if (!swap)
            break;
    }
}

void SortByTimeStruct(folder *f, int n)
{
    bool swap = false;
    while (1)
    {
        swap = false;
        for (int i = 0; i < n - 1; i++)
        {
            folder f1 = *(f + i);
            folder f2 = *(f + i + 1);
            time_t t1 = f1.modTime;
            time_t t2 = f2.modTime;
            if (t1 < t2)
            {
                *(f + i) = f2;
                *(f + i + 1) = f1;
                swap = true;
            }
        }
        if (!swap)
            break;
    }
}

void SortByName(file *f, int n)
{
    bool swap = false;
    while (1)
    {
        swap = false;
        for (int i = 0; i < n - 1; i++)
        {
            file f1 = *(f + i);
            file f2 = *(f + i + 1);
            char *n1 = f1.name;
            char *n2 = f2.name;
            if (strcmp(n1, n2) > 0)
            {
                *(f + i) = f2;
                *(f + i + 1) = f1;
                swap = true;
            }
        }
        if (!swap)
            break;
    }
}

void SortByTime(file *f, int n)
{
    bool swap = false;
    while (1)
    {
        swap = false;
        for (int i = 0; i < n - 1; i++)
        {
            file f1 = *(f + i);
            file f2 = *(f + i + 1);
            time_t t1 = f1.modTime;
            time_t t2 = f2.modTime;
            if (t1 < t2)
            {
                *(f + i) = f2;
                *(f + i + 1) = f1;
                swap = true;
            }
        }
        if (!swap)
            break;
    }
}

void SortByNameArr(char *argv[], int argc)
{
    bool swap = false;
    while (1)
    {
        swap = false;
        for (int i = 1; i < argc - 1; i++)
        {
            char *n1 = argv[i];
            char *n2 = argv[i + 1];
            if (strcmp(n1, n2) > 0)
            {
                argv[i] = n2;
                argv[i + 1] = n1;
                swap = true;
            }
        }
        if (!swap)
            break;
    }
}

void SortByTimeArr(char *args[], int arc, int offset)
{
    bool swap = false;
    struct stat d1, d2;
    while (1)
    {
        swap = false;
        for (int i = offset; i < arc - 1; i++)
        {
            char *n1 = args[i];
            char *n2 = args[i + 1];
            stat(n1, &d1);
            time_t mt1 = d1.st_mtime;
            stat(n2, &d2);
            time_t mt2 = d2.st_mtime;
            if (mt1 < mt2)
            {
                args[i] = n2;
                args[i + 1] = n1;
                swap = true;
            }
        }
        if (!swap)
            break;
    }
}

void SortByExist(char *argv[], int argc)
{
    bool swap = false;
    while (1)
    {
        swap = false;
        for (int i = 1; i < argc - 1; i++)
        {
            char *n1 = argv[i];
            char *n2 = argv[i + 1];
            int cond1 = 0, cond2 = 0;
            if (FileExists(n1))
                cond1 = 1;
            if (FileExists(n2))
                cond2 = 1;
            if (cond2 < cond1)
            {
                argv[i] = n2;
                argv[i + 1] = n1;
                swap = true;
            }
        }
        if (!swap)
            break;
    }
}

int size = 0, ndirall = 0;
void RecordDirectories(char *path, int flagA, int flagR, int flagT)
{
    struct dirent *sd;
    DIR *dir = opendir(path);
    if (!dir)
    {
        printf("ls: cannot access '%s': No such file or directory\n", path);
        return;
    }
    int ndir = numDirectories(path, flagA);
    int nobj = numObjects(path, flagA);
    ndirall += ndir;
    if (size == 0)
    {
        if (ndirall == 0)
            folders = (folder *)malloc(sizeof(folder));
        else
            folders = (folder *)malloc(sizeof(folder) * ndirall);
    }
    else
    {
        folders = (folder *)realloc(folders, sizeof(folder) * (ndirall + 1));
    }
    folders[size].path = (char *)malloc(strlen(path) + 1);
    strcpy(folders[size].path, path);
    int k = 0;
    struct stat fileInfo, dirInfo;
    stat(path, &dirInfo);
    time_t mtime = dirInfo.st_mtime;
    folders[size].modTime = mtime;
    folders[size].files = (file *)malloc(nobj * sizeof(file));
    while ((sd = readdir(dir)))
    {
        if (flagA)
        {
            char *temp = (char *)malloc(strlen(sd->d_name) + strlen(path) + 2);
            sprintf(temp, "%s/%s", path, sd->d_name);
            stat(temp, &fileInfo);
            time_t modTime = fileInfo.st_mtime;
            folders[size].files[k].name = (char *)malloc(strlen(sd->d_name) + 1);
            strcpy(folders[size].files[k].name, sd->d_name);
            folders[size].files[k].modTime = modTime;
            free(temp);
            k++;
        }
        else
        {
            if ((strncmp(sd->d_name, ".", 1) != 0))
            {
                char *temp = (char *)malloc(strlen(sd->d_name) + strlen(path) + 2);
                sprintf(temp, "%s/%s", path, sd->d_name);
                stat(temp, &fileInfo);
                time_t modTime = fileInfo.st_mtime;
                folders[size].files[k].name = (char *)malloc(strlen(sd->d_name) + 1);
                strcpy(folders[size].files[k].name, sd->d_name);
                folders[size].files[k].modTime = modTime;
                free(temp);
                k++;
            }
        }
    }
    SortByName(folders[size].files, k);
    if (flagT)
        SortByTime(folders[size].files, k);
    closedir(dir);
    folders[size].numObjects = k;
    size++;
    if (flagR)
    {
        dir = opendir(path);
        while ((sd = readdir(dir)))
        {
            if ((strcmp(sd->d_name, ".") != 0) && (strcmp(sd->d_name, "..") != 0))
            {
                if (sd->d_type == DT_DIR)
                {
                    char newpath[512];
                    sprintf(newpath, "%s/%s", path, sd->d_name);
                    RecordDirectories(newpath, flagA, flagR, flagT);
                }
            }
        }
        closedir(dir);
    }
}

void FreeStruct(int n)
{
    if (folders != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            int num = folders[i].numObjects;
            for (int j = 0; j < num; j++)
            {
                free(folders[i].files[j].name);
            }
            free(folders[i].files);
            free(folders[i].path);
        }
    }
}

int NumOfWords(char *argv[], int argc)
{
    int count = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "-", 1) != 0)
            count++;
    }
    return count;
}

void PrintDir(char *name, int flagA, int flagR, int flagT, int argc)
{
    if (FileExists(name))
    {
        if (IsFile(name))
        {
            printf("%s\n", name);
            return;
        }
    }
    else
    {
        printf("ls: cannot access '%s': No such file or directory\n", name);
        return;
    }
    RecordDirectories(name, flagA, flagR, flagT);
    SortByNameStruct(folders, size);
    if (flagT)
        SortByTimeStruct(folders, size);
    for (int i = 0; i < size; i++)
    {
        if (flagR || argc > 1)
            printf("%s:\n", folders[i].path);
        int num = folders[i].numObjects;
        for (int j = 0; j < num; j++)
        {
            if (strncmp(name, "-", 1) != 0)
                printf("%s      ", folders[i].files[j].name);
        }
        printf("\n");
    }
    FreeStruct(size);
    free(folders);
    ndirall = 0;
    size = 0;
}

void my_ls(int argc, char *argv[])
{
    if (argc == 1)
    {
        PrintDir(".", 0, 0, 0, argc);
        exit(0);
    }
    else
    {
        SortByNameArr(argv, argc);
        SortByExist(argv, argc);
        int ne = NumOfNonExist(argv, argc);
        if (!Options(argv, argc))
        {
            for (int j = 1; j <= ne; j++)
            {
                printf("ls: cannot access '%s': No such file or directory\n", argv[j]);
            }
            for (int i = 1; i < argc; i++)
            {
                if (strncmp(argv[i], "-", 1) != 0)
                {
                    if (IsFile(argv[i]))
                        printf("%s     ", argv[i]);
                }
            }
            printf("\n");
            for (int i = 1; i < argc; i++)
            {
                if (strncmp(argv[i], "-", 1) != 0)
                {
                    if (IsFolder(argv[i]))
                        PrintDir(argv[i], 0, 0, 0, argc);
                }
            }
            exit(0);
        }
        int nw = NumOfWords(argv, argc);
        int offset = ne + 1;
        int flagA = 0, flagR = 0, flagT = 0;
        if (Option_A(argv, argc))
            flagA = 1;
        if (Option_R(argv, argc))
            flagR = 1;
        if (Option_T(argv, argc))
            flagT = 1;
        if (flagT)
            SortByTimeArr(argv, argc, offset);
        for (int j = 1; j < offset; j++)
        {
            if (strncmp(argv[j], "-", 1) != 0)
                printf("ls: cannot access '%s': No such file or directory\n", argv[j]);
        }
        if (nw == 0)
        {
            PrintDir(".", flagA, flagR, flagT, argc);
            exit(0);
        }
        for (int i = 1; i < argc; i++)
        {
            if (strncmp(argv[i], "-", 1) != 0)
            {
                if (IsFile(argv[i]))
                    printf("%s     ", argv[i]);
            }
        }
        printf("\n");
        for (int i = 1; i < argc; i++)
        {
            if (strncmp(argv[i], "-", 1) != 0)
            {
                if (IsFolder(argv[i]))
                    PrintDir(argv[i], flagA, flagR, flagT, nw);
            }
        }
        exit(0);
    }
}
