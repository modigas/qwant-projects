#include <main.h>

int main(int ac, unused char** av, char** env)
{
    if (ac == 1)
    {
        char* string = NULL;
        signal(SIGINT, SIG_IGN);
        bool exitLoop = false;
        char** copyEnv = copyEnvi(&env);
        while (!exitLoop)
        {
            printf("%smy_zsh%s:%s>%s ", YELLOW_B, RED_B, GREEN_B, RESET_COLOR);
            if ((string = readTerminal()) == NULL) continue;
            struct queue tokens = queue.new();
            if (!tokenize(&string, &tokens)) continue;
            struct queue options = queue.new();
            char** args = NULL;
            char** path = getPath(copyEnv);
            if (!parse(&args, &tokens, &options, &path)) continue;
            if ((exitLoop = execute(&args, &options, &copyEnv)) == false)
                continue;
        }
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "%sError:%s usage ./my_zsh\n", RED_B, RESET_COLOR);
        return EXIT_FAILURE;
    }
}