#include <main.h>

int main(int ac, char** av)
{
    if (ac == 2)
    {
        char* response = NULL;
        char** tokens;

        if ((response = getTokensAndHtml(&av[1], &tokens)) == NULL)
            return EXIT_FAILURE;
        if (!handleResponse(&tokens, &response)) return EXIT_FAILURE;
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "Error: usage my_curl [full-url]\n");
        return EXIT_FAILURE;
    }
}