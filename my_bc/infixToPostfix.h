#include "libs.h"
#include "utils.h"
#include "stack.h"
#include "getTokens.h"
#define BRC 'b'

char *infixToPostfix(char **infixTokens);
void nextIndex(int *tokenLength, int *index, char **token);
void isOperator(char **token, char **postfixTokens, int *postfixIndex,
                char *prevChar, struct stack *operators, bool *error);
void isVariable(char **token, char **postfixTokens, int *postfixIndex,
                char *prevChar, bool *error);
int precedence(char operator);
void popRestStack(char **postfixTokens, int *postfixIndex,
                  struct stack *operators);