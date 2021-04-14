#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct
{
    time_t modTime;
    char* name;
} fileStats;

void SortArrTime(fileStats *files, int size) {
  bool swap = true;
  while (1) {
    swap = false;
    for (int i = 0; i < size - 1; i++) {
      fileStats f1 = *(files + i);
      fileStats f2 = *(files + i + 1);
      time_t t1 = f1.modTime;
      time_t t2 = f2.modTime;
      if (t1 < t2) {
        *(files + i) = f2;
        *(files + i + 1) = f1;
        swap = true;
      }
    }
    if (!swap) {
      break;
    }
  }
}

void RecurDir(char* path)
{
    char strPath[512];
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        return;
    }
    struct dirent *sd;
    printf("%s\n", path);
    while ((sd = readdir(dir)) != NULL)
    {
        if (sd->d_type == DT_DIR) {
            if (strncmp(sd->d_name,".",1) != 0)
            {
                printf("%s      ", sd->d_name);
                strcpy(strPath, path);
                strcat(strPath, "/");
                strcat(strPath, sd->d_name);
                RecurDir(strPath);
            }
        }
    }
    closedir(dir);
}

int main(int argc, char* argv[]) {
    RecurDir(argv[1]);
    // DIR *dir;
    // struct dirent *cd;
    // dir = opendir(argv[1]);
    // if (dir == NULL) {
    //     printf("%s no such file\n", argv[1]);
    //     exit(1);
    // }
    // struct stat data;
    // fileStats *ptr;
    // int numObj = 0;
    // while((cd = readdir(dir))) {
    //     if (strncmp(cd->d_name, ".", 1) != 0) numObj++;
    // }
    // closedir(dir);
    // ptr = (fileStats*)malloc(sizeof(fileStats)*numObj);
    // printf("size of memory = %lu\n", sizeof(fileStats)*numObj);
    // dir = opendir(argv[1]);
    // int i = 0;
    // while((cd = readdir(dir)))
    // {
    //     if (strncmp(cd->d_name, ".", 1) != 0) 
    //     {
    //         stat(cd->d_name,&data);
    //         time_t mt = data.st_mtime;
    //         (ptr+i)->name = cd->d_name;
    //         (ptr+i)->modTime = mt;
    //         i++;
    //     }
    // }
    // SortArrTime(ptr, numObj);
    // for (int j = 0; j < numObj; ++j)
    // {   
    //     time_t dt = (ptr+j)->modTime;
    //     printf("%s mod date %s\n", (ptr+j)->name, ctime(&dt));
    // }
    // closedir(dir);
    // free(ptr);
    return 0;
}