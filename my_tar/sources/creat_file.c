
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../headers/tar.h"
#include <pwd.h>
#include <grp.h>

// struct stat {
//     dev_t     st_dev;     /* ID of device containing file */
//     ino_t     st_ino;     /* inode number */
//     mode_t    st_mode;    /* protection */
//     nlink_t   st_nlink;   /* number of hard links */
//     uid_t     st_uid;     /* user ID of owner */
//     gid_t     st_gid;     /* group ID of owner */
//     dev_t     st_rdev;    /* device ID (if special file) */
//     off_t     st_size;    /* total size, in bytes */
//     blksize_t st_blksize; /* blocksize for file system I/O */
//     blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
//     time_t    st_atime;   /* time of last access */
//     time_t    st_mtime;   /* time of last modification */
//     time_t    st_ctime;   /* time of last status change */
// };

tar_header *init_tar_header()
{
    tar_header *header = (tar_header*)malloc(BLOCKSIZE);
    if (header != NULL)
    {
        bzero(header, BLOCKSIZE);
    }
    return header;
}

char get_typeflag(int mode)
{
    switch (mode & S_IFMT)
    {
        case S_IFREG:
            return REGTYPE;
        case S_IFLNK:
            return SYMTYPE;
        case S_IFCHR:
            return CHRTYPE;
        case S_IFBLK:
            return BLKTYPE;
        case S_IFDIR:
            return DIRTYPE;
        case S_IFIFO:
            return FIFOTYPE;
        default:
            return REGTYPE;
    }
}
int checkSum(tar_header **tar)
{
    int checksum = 0;
    for (int i = 0; i < 512; i++)
    {
        checksum += (unsigned char)(*tar)->block[i];
    }
    return checksum + 7 * 32;
}

tar_header *read_metadata(int fd_archive)
{
    tar_header *header = init_tar_header();
    struct stat info;
    read(fd_archive, header->name, 100);
    if (stat(header->name, &info) < 0)
    {
        free(header);
        return NULL;
    }
    char typef[1];
    read(fd_archive, header->mode, 8);
    read(fd_archive, header->uid, 8);
    read(fd_archive, header->gid, 8);
    read(fd_archive, header->size, 12);
    read(fd_archive, header->mtime, 12);
    read(fd_archive, header->chksum, 8);
    read(fd_archive, typef, 1);
    header->typeflag = get_typeflag(info.st_mode);
    read(fd_archive, header->linkname, 100);
    read(fd_archive, header->magic, 5);
    read(fd_archive, header->version, 3);
    read(fd_archive, header->uname, 32);
    read(fd_archive, header->gname, 32);
    read(fd_archive, header->devmajor, 8);
    read(fd_archive, header->devminor, 8);
    read(fd_archive, header->prefix, 167);
    return header;
}

tar_header *get_metadata(char *filename)
{
    // char nul = '\0';
    struct stat info;
    struct group *grp;
    struct passwd *pwd;

    if (stat(filename, &info) < 0)
    {
        printf("Error opening file\n");
        return NULL;
    }

    tar_header *header = init_tar_header();
    grp = getgrgid(info.st_gid);
    pwd = getpwuid(info.st_uid);
    // name             sucseess

    // mode                 sucsess
    if (S_ISDIR(info.st_mode))
    {
        char str[100];
        sprintf(str, "%s/", filename);
        my_strncpy(header->name, str, 100);
    }
    else
    {
        my_strncpy(header->name, filename, 100);
    }
    my_itoa_base(header->mode, info.st_mode & 0777, 8, OCTAL_BASE);

    // uid                   sucsess
    my_itoa_base(header->uid, info.st_uid, 8, OCTAL_BASE);
    // gid                   sucsess
    my_itoa_base(header->gid, info.st_gid, 8, OCTAL_BASE);
    // size

    // mtime
    my_itoa_base(header->mtime, info.st_mtime, 12, OCTAL_BASE);

    header->typeflag = get_typeflag(info.st_mode);

    // my_strncpy(header->chksum, &nul, 8);
    my_strncpy(header->magic, TMAGIC, 6);
    my_strncpy(header->version, TVERSION, 3);
    my_strncpy(header->uname, pwd->pw_name, 32);
    my_strncpy(header->gname, grp->gr_name, 32);

    if (S_ISDIR(info.st_mode))
    {
        my_itoa_base(header->size, info.st_size & 0777, 12, OCTAL_BASE);
    }
    else
    {
        my_itoa_base(header->size, info.st_size, 12, OCTAL_BASE);
    }
    int checksum = checkSum(&header);
    my_itoa_base(header->chksum, checksum, 7, OCTAL_BASE);

    header->version[0] = ' ';
    header->version[1] = ' ';

    return header;
}

int create_archive(int fd_archive, tar_options *options)
{
    // printf("\n Start \n");
    int res = 0;
    tar_header *header;

    for (int i = 0; i < options->size; i++)
    {
        header = get_metadata(options->files[i]);
        if (header != NULL)
        {
            write(fd_archive, header, BLOCKSIZE);
            write_file_content(fd_archive, options->files[i]);
            recursion_of_dir_files(fd_archive, options->files[i]);
            free(header);
        }
        else
        {
            res++;
        }
    }
    return res;
}