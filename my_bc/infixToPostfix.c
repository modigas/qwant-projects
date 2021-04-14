#include "infixToPostfix.h"

char *infixToPostfix(char **infixTokens)
{
    int postfixLength = strlen((*infixTokens));
    char *postfixTokens = getString(postfixLength);
    char *token = NULL;
    char prevChar = '\0';
    int tokenLength = 0;
    int index = 0;
    int postfixIndex = 0;
    bool error = false;
    struct stack operators = stack.new();
    while ((token = readLine(&((*infixTokens)[index]))) != NULL)
    {
        isOperator(&token, &postfixTokens, &postfixIndex, &prevChar, &operators,
                   &error);
        isVariable(&token, &postfixTokens, &postfixIndex, &prevChar, &error);
        nextIndex(&tokenLength, &index, &token);
        free(token);
        if (error)
        {
            free(postfixTokens);
            free(*infixTokens);
            operators.destroy(&operators);
            return NULL;
        }
    }
    popRestStack(&postfixTokens, &postfixIndex, &operators);
    free(*infixTokens);
    operators.destroy(&operators);
    return postfixTokens;
}

void popRestStack(char **postfixTokens, int *postfixIndex,
                  struct stack *operators)
{
    while (!operators->empty(operators))
    {
        (*postfixTokens)[(*postfixIndex)++] = operators->top(operators);
        (*postfixTokens)[(*postfixIndex)++] = '\n';
        operators->pop(operators);
    }
}

void nextIndex(int *tokenLength, int *index, char **token)
{
    (*tokenLength) = strlen(*token) + 1;
    (*index) += (*tokenLength);
}

void isOperator(char **token, char **postfixTokens, int *postfixIndex,
                char *prevChar, struct stack *operators, bool *error)
{
    if ((*token)[0] == OPR)
    {
        if (((*prevChar) != OPR) || ((*token)[2] == '(') ||
            ((*token)[2] == ')'))
        {
            if ((*token)[2] == '(')
            {
                (*prevChar) = BRC;
                operators->push(operators, (*token)[2]);
            }
            else if ((*token)[2] == ')')
            {
                (*prevChar) = BRC;
                while ((!operators->empty(operators)) &&
                       (operators->top(operators) != '('))
                {
                    (*postfixTokens)[(*postfixIndex)++] =
                        operators->top(operators);
                    (*postfixTokens)[(*postfixIndex)++] = '\n';
                    operators->pop(operators);
                }
                operators->pop(operators);
            }
            else
            {
                (*prevChar) = OPR;
                while ((!operators->empty(operators)) &&
                       (precedence(operators->top(operators)) >=
                        precedence((*token)[2])))
                {
                    (*postfixTokens)[(*postfixIndex)++] =
                        operators->top(operators);
                    (*postfixTokens)[(*postfixIndex)++] = '\n';
                    operators->pop(operators);
                }
                operators->push(operators, (*token)[2]);
            }
        }
        else
        {
            (*error) = true;
            fprintf(stderr, "Error: consecutive operators\n");
        }
    }
}

void isVariable(char **token, char **postfixTokens, int *postfixIndex,
                char *prevChar, bool *error)
{
    int i = 2;
    if ((*token)[0] == VAR)
    {
        if ((*prevChar) != VAR)
        {
            (*prevChar) = VAR;
            while ((*token)[i] != '\0')
            {
                (*postfixTokens)[(*postfixIndex)++] = (*token)[i++];
            }
            (*postfixTokens)[(*postfixIndex)++] = '\n';
        }
        else
        {
            (*error) = true;
            fprintf(stderr, "Error: consecutive variables\n");
        }
    }
}

int precedence(char operator)
{
    if (operator== '*' || operator== '/' || operator== '%')
    {
        return 2;
    }
    else if (operator== '+' || operator== '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}