#include "libs.h"
#include "utils.h"
#include "checkers.h"
#include "stack.h"
#include "postfixEvaluator.h"

char *getTokens(char *inputString);
char *infixToPostfix(char **infixTokens);