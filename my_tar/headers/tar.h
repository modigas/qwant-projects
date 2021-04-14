#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <utime.h>
#include <string.h>
#include <fcntl.h>
#define BLOCKSIZE 512
#define OCTAL_BASE 8
#define DEC_BASE 10

typedef union tar_header{
    struct {                           /* byte offset */
  char name[100];               /*   0 */
  char mode[8];                 /* 100 */
  char uid[8];                  /* 108 */
  char gid[8];                  /* 116 */
  char size[12];                /* 124 */
  char mtime[12];               /* 136 */
  char chksum[8];               /* 148 */
  char typeflag;                /* 156 */
  char linkname[100];           /* 157 */
  char magic[5];                /* 257 */
  char version[3];              /* 263 */
  char uname[32];               /* 265 */
  char gname[32];               /* 297 */
  char devmajor[8];             /* 329 */
  char devminor[8];             /* 337 */
  char prefix[155];             /* 345 */
                                /* 500 */
};
    char block[500];
} tar_header;
#define TMAGIC   "ustar"        /* ustar and a null */
#define TMAGLEN  6
#define TVERSION "00"           /* 00 and no null */
#define TVERSLEN 2
#define VERSION_WORKS "00"

/* Values used in typeflag field.  */
#define REGTYPE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* link */
#define SYMTYPE  '2'            /* reserved */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */

#define XHDTYPE  'x'            /* Extended header referring to the next file in the archive */
#define XGLTYPE  'g'            /* Global extended header */


typedef struct s_opt
{
    bool create;
    bool extract;
    bool append;
    bool append_by_time;
    bool list_of_files;
    char *archive_name;
    bool is_dir_name;
    char* dir_name;
    char** files;
    int size;
} tar_options;

int open_archive_file(tar_options *options);


tar_options * get_opt(int ac, char ** argv);
void delete_options(tar_options *);


int write_file_content(int fd_archive, char *filename);
void end_of_archive(int);
int create_archive(int fd_archive, tar_options *options);

// Conversion.c
char *my_itoa_base(char *, unsigned int, int, int);
long oct_to_dec(long);
long dec_to_oct(long);
long my_atol(const char *, int);
//recursion_of_dir_files
int recursion_of_dir_files(int fd, char* filename);

tar_header *get_metadata(char *filename);
int append_by_time(int fd_archive, tar_options * options);
int get_file_size(int fd);
tar_header *read_metadata(int fd_archive);

//tar extraction
void foldersFromNames(char* path);
char* lastFileName(char* path);
void createFile(tar_header* fileData, char** content, int* size);
void extractFiles(char* argv[]);
void listFiles(char* argv[]);

//utility functions
size_t my_strlen(char* str);
char* my_strncpy(char* dest, const char* src, int size);
char* my_strcpy(char* dest, const char* src);