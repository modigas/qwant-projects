#include "../headers/tar.h"

void print_options(tar_options *options)
{
    printf("============TAR_OPTIONS============\n");
    printf("Creation mode: %s\n", options->create ? "true" : "false");
    printf("Extraction mode: %s\n", options->extract ? "true" : "false");
    printf("Append mode: %s\n", options->append ? "true" : "false");
    printf("Append By Time mode: %s\n",
           options->append_by_time ? "true" : "false");
    printf("List File Names mode: %s\n",
           options->list_of_files ? "true" : "false");
    printf("Archive name: %s\n", options->archive_name);
    printf("===================================\n");

    return;
}

tar_options *init_tar_options(void)
{
    tar_options *options = (tar_options*)malloc(sizeof(tar_options));

    if (options != NULL)
    {
        options->create = false;
        options->extract = false;
        options->archive_name = NULL;
        options->append = false;
        options->append_by_time = false;
        options->list_of_files = false;
        options->is_dir_name = false;
        options->dir_name = NULL;
        options->size = 0;
    }
    else
    {
        free(options);
    }
    return options;
}

bool validate_options(tar_options *options)
{
    int sum = (int)options->append + (int)options->append_by_time +
              (int)options->create + (int)options->extract +
              (int)options->list_of_files;
    if (sum > 1)
    {
        printf("tar: Can't specify many modes\n");
        return false;
    }
    if (sum == 0)
    {
        printf("tar: Must specify one of -c, -r, -t, -u, -x\n");
        return false;
    }
    if (options->archive_name == NULL)
    {
        printf("tar: Must specify a filename\n");
        return false;
    }
    return true;
}

tar_options *get_opt(int ac, char **argv)
{
    if (ac < 2)
    {
        fprintf(stderr, "%s: No argument specified\n", argv[0]);
        return NULL;
    }
    tar_options *options = init_tar_options();

    if (argv[1][0] == '-')
    {
        for (int j = 1; j < (int)my_strlen(argv[1]); j++)
        {
            if (argv[1][j] == 'u')
            {
                options->append_by_time = true;
            }
            else if (argv[1][j] == 'r')
            {
                options->append = true;
            }
            else if (argv[1][j] == 'c')
            {
                options->create = true;
            }
            else if (argv[1][j] == 't')
            {
                options->list_of_files = true;
            }
            else if (argv[1][j] == 'x')
            {
                options->extract = true;
            }
        }
    }
    else
    {
        printf("Specify option\n");
        free(options);
        return NULL;
    }
    options->archive_name = argv[2];
    // options->files = malloc((ac - 3));
    options->files = (char**)malloc((ac - 3)*sizeof(char*));
    options->size = ac - 3;

    for (int i = 3; i < ac; i++)
    {
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'C')
            {
                options->is_dir_name = true;
                options->dir_name = argv[i + 1];
                break;
            }
        }
        else
        {
            options->files[i - 3] = argv[i];
        }
    }
    if (validate_options(options) != true)
    {
        return NULL;
    }
    // print_options(options);
    return options;
}