#include <handleResponse.h>

bool handleResponse(char*** tokens, char** response)
{
    //Our curl is without options, however it is possible to add it here
    //since we have tokens with "html-headers" and "html-page"
    printf("%s", *response);
    freeTokens(tokens);
    free(*response);
    return true;
}

void freeTokens(char*** tokens)
{
    for(int i = 0; (*tokens)[i] != NULL; i++)
    {
        free((*tokens)[i]);
    }
    free(*tokens);
}