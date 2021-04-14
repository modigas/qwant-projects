#include "main.h"

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (checkAllowed(&argv[1]))
        {
            char *tokens = getTokens(argv[1]);
            if (tokens == NULL) return 0;
            char *postfixTokens = infixToPostfix(&tokens);
            if (postfixTokens == NULL) return 0;
            int res = postfixEval(&postfixTokens);
            printf("ans = %d\n", res);
            free(postfixTokens);
        }
        else
        {
            printf("Invalid characters\n");
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "Error: the format\
                         should be in a form =>\
                         ./my_bc \"1 + 2 * (3 \
                         - 42) %% 5\" \n");
        return 1;
    }
    return 0;
}