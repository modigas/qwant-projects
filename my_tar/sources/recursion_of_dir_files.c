
#include <string.h>
#include "../headers/tar.h"

int recursion_of_dir_files(int fd_archive, char* filename)
{
    DIR* rep;
    struct dirent* ep;
    struct stat attribb;
    tar_header* header;
    if (stat(filename, &attribb) < 0)
    {
        printf("Error opening file\n");
        return 1;
    }

    if (!S_ISDIR(attribb.st_mode))
    {
        return 0;
    }

    char* path = malloc(50 * sizeof(char));
    sprintf(path, "./%s", filename);

    rep = opendir(path);

    if (rep == NULL)
    {
        printf("ERROR READING A FILE");
        return 2;
    }

    while ((ep = readdir(rep)))
    {
        if (ep->d_name[0] == '.')
        {
            continue;
        }
        char* new_temp = malloc(100 * sizeof(char));
        sprintf(new_temp, "%s/%s", path, ep->d_name);
        sprintf(new_temp, "%s/%s", filename, ep->d_name);
        printf("------>%s", new_temp);

        if (stat(new_temp, &attribb) < 0)
        {
            printf("Error opening file\n");
            return 1;
        }

        header = get_metadata(new_temp);
        write(fd_archive, header, BLOCKSIZE);
        write_file_content(fd_archive, new_temp);

        free(header);

        if (S_ISDIR(attribb.st_mode))
        {
            recursion_of_dir_files(fd_archive, new_temp);
        }
    }

    closedir(rep);
    return 0;
}