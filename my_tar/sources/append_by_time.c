#include <stdio.h>
#include <string.h>
#include "../headers/tar.h"

int strcompare(char* first, char* second)
{
    if (my_strlen(first) != my_strlen(second))
    {
        return -1;
    }
    for (int i = 0; i < (int)my_strlen(second); i++)
    {
        if (first[i] != second[i])
        {
            return -1;
        }
    }
    return 0;
}

int append_by_time(int fd_archive, tar_options* options)
{
    struct stat attribb;
    char filename[100];

    int size = options->size;
    bool is_changable = false;
    bool is_exist = false;

    for (int i = 0; i < size; i++)
    {
        // char* pointer = options->files[i];
        sprintf(filename, "%s", options->files[i]);
        if (stat(filename, &attribb) < 0)
        {
            printf(" opening file\n");
            return 1;
        }
        if (S_ISDIR(attribb.st_mode))
        {
            sprintf(filename, "%s/", options->files[i]);
        }
        else
        {
            sprintf(filename, "%s", options->files[i]);
        }
        tar_header* tar_head = NULL;
        // while ((tar_head = read_metadata(fd_archive)) != NULL)
        while(1)
        {
            tar_head = read_metadata(fd_archive);
            if(tar_head == NULL)
            {
                free(tar_head);
                break;
            }
            // printf("%s\n", tar_head->name);
            long length =
                oct_to_dec(my_atol(tar_head->size, my_strlen(tar_head->size)));
            if (length % BLOCKSIZE != 0)
            {
                length += BLOCKSIZE - (length % BLOCKSIZE);
            }
            char con[length];
            read(fd_archive, con, length);
            if (strcompare(tar_head->name, filename) == 0)
            {
                long date_current_file = (attribb.st_mtime);
                long date_tar_file = oct_to_dec(
                    my_atol(tar_head->mtime, my_strlen(tar_head->mtime)));
                // printf("%ld %ld", date_current_file, date_tar_file);
                is_exist = true;
                if (date_current_file > date_tar_file)
                {
                    is_changable = true;
                }
                else
                {
                    is_changable = false;
                }
            }
            free(tar_head);
        }
        lseek(fd_archive, 0, SEEK_SET);

        if (is_changable == true && is_exist == true)
        {
            tar_header* header = get_metadata(options->files[i]);
            if (header != NULL)
            {
                write(fd_archive, header, BLOCKSIZE);
                write_file_content(fd_archive, options->files[i]);
                recursion_of_dir_files(fd_archive, options->files[i]);
                free(header);
            }
        }
        if (is_exist == false)
        {
            tar_header* header = get_metadata(options->files[i]);
            if (header != NULL)
            {
                write(fd_archive, header, BLOCKSIZE);
                write_file_content(fd_archive, options->files[i]);
                recursion_of_dir_files(fd_archive, options->files[i]);
                free(header);
            }
        }
    }
    return 0;
}