#include "../headers/tar.h"

int main(int argc, char **argv)
{
    int result = 0;
    int fd_archive;

    tar_options *options = get_opt(argc, argv);

    if (options == NULL)
    {
        printf("Error parsing options");
        return 1;
    }
    fd_archive = open_archive_file(options);
    if (fd_archive < 0)
    {
        printf("Error opening archive");
        return 2;
    }

    if (options->create == true)
        result += create_archive(fd_archive, options);
    else if (options->append == true)
    {
        result += create_archive(fd_archive, options);
    }
    else if (options->append_by_time == true)
    {
        result += append_by_time(fd_archive, options);
    }
    else if(options->list_of_files)
    {
        listFiles(argv);
    }
    else if (options->extract == true)
    {
        extractFiles(argv);
    }
    // for(int i = 0; i < argc - 2; i++)
    // {
    //     free(options->files[i]);
    // }
    free(options->files);
    free(options);
    close(fd_archive);
    
    return result;
}