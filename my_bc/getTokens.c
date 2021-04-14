#include "getTokens.h"

char *getTokens(char *inputString)
{
    int tokenIndex = 0;
    bool initOp = true;
    bool error = false;
    bool numDetected = true;
    bool doubleOperator = true;
    bool negativeNumber = false;
    int nNegative = 0;
    char nType = '0';
    int inputLength = strlen(inputString);
    if (inputLength == 0)
    {
        fprintf(stderr, "Error: empty string\n");
        return NULL;
    }
    char *tokens = getString(16 * inputLength);
    struct stack brackets = stack.new();
    for (int i = 0; i < inputLength; i++)
    {
        if (skipSpace(inputString[i])) continue;
        if (initOp)
        {
            initOp = false;
            if (initOperator(inputString[i], &tokens, &tokenIndex))
            {
                nNegative += 1;
                nType = '-';
                continue;
            }
        }
        if (handleBrackets(inputString[i], &tokens, &tokenIndex, &brackets,
                           &doubleOperator, &numDetected, &error, &nNegative,
                           &nType))
            continue;
        if (handleArithmetic(inputString[i], &tokens, &tokenIndex,
                             &doubleOperator, &numDetected, &negativeNumber,
                             &error, &nNegative, &nType))
            continue;
        if (handleNumber(inputString[i], &tokens, &tokenIndex, &doubleOperator,
                         &numDetected, &negativeNumber))
        {
            nNegative = 0;
            nType = '0';
            continue;
        }
        if (error)
        {
            free(tokens);
            brackets.destroy(&brackets);
            return NULL;
        }
    }
    if (tokens[tokenIndex] != '\n') tokens[tokenIndex] = '\n';
    if (isBalancedBrackets(&brackets, &tokens))
        return tokens;
    else
        return NULL;
}

bool skipSpace(char input)
{
    if (input == ' ' || input == '\n' || input == '\t') return true;
    return false;
}

bool handleBrackets(char input, char **tokens, int *tokenIndex,
                    struct stack *brackets, bool *doubleOperator,
                    bool *numDetected, bool *error, int *nNegative, char *nType)
{
    if (isBr(input))
    {
        bool tempBool = false;
        if (input == '(')
        {
            brackets->push(brackets, input);
            (*doubleOperator) = true;
            if ((*nType) == '-')
            {
                (*nNegative) += 1;
                (*nType) = '(';
            }
            else
            {
                (*nNegative) = 0;
                (*nType) = '0';
            }
        }
        else if (!brackets->empty(brackets))
        {
            (*nNegative) = 0;
            (*nType) = '0';
            if (((*tokenIndex) - 2 >= 0) &&
                ((*tokens)[(*tokenIndex) - 2] == '('))
            {
                (*error) = true;
                fprintf(stderr, "Error: empty brackets\n");
                return false;
            }
            brackets->pop(brackets);
            (*doubleOperator) = false;
        }
        else
        {
            (*error) = true;
            fprintf(stderr, "Error: Unbalanced brackets\n");
            return false;
        }
        writeOpAndNum(tokens, input, tokenIndex, OPR, numDetected, &tempBool);
        (*numDetected) = true;
        return true;
    }
    return false;
}

bool isBalancedBrackets(struct stack *brackets, char **tokens)
{
    if (brackets->empty(brackets))
    {
        brackets->destroy(brackets);
        return true;
    }
    else
    {
        fprintf(stderr, "Error: Unbalanced brackets\n");
        brackets->destroy(brackets);
        free(*tokens);
        return NULL;
    }
}

bool handleArithmetic(char input, char **tokens, int *tokenIndex,
                      bool *doubleOperator, bool *numDetected,
                      bool *negativeNumber, bool *error, int *nNegative,
                      char *nType)
{
    if (isOp(input))
    {
        if (bracketMinus(input, tokens, tokenIndex, nNegative, nType))
            return true;
        if (*doubleOperator)
        {
            if ((*negativeNumber) || (input != '-'))
            {
                (*error) = true;
                fprintf(stderr, "Error: improper expression\n");
                return false;
            }
            else
            {
                (*negativeNumber) = true;
            }
        }
        else
        {
            writeOpAndNum(tokens, input, tokenIndex, OPR, numDetected,
                          negativeNumber);
            (*negativeNumber) = false;
            (*numDetected) = true;
            (*doubleOperator) = true;
        }
        return true;
    }
    return false;
}

bool handleNumber(char input, char **tokens, int *tokenIndex,
                  bool *doubleOperator, bool *numDetected, bool *negativeNumber)
{
    if (isNum(input))
    {
        writeOpAndNum(tokens, input, tokenIndex, VAR, numDetected,
                      negativeNumber);
        (*doubleOperator) = false;
        return true;
    }
    return false;
}

void writeOpAndNum(char **tokens, char input, int *tokenIndex, char type,
                   bool *numDetected, bool *negativeNumber)
{
    if (type == OPR)
    {
        if (!*numDetected)
        {
            (*tokens)[(*tokenIndex)++] = '\n';
        }
        (*tokens)[(*tokenIndex)++] = type;
        (*tokens)[(*tokenIndex)++] = SEP;
        (*tokens)[(*tokenIndex)++] = input;
        (*tokens)[(*tokenIndex)++] = NEWLINE;
    }
    else
    {
        if (*numDetected)
        {
            (*numDetected) = false;
            (*tokens)[(*tokenIndex)++] = type;
            (*tokens)[(*tokenIndex)++] = SEP;
            if (*negativeNumber)
            {
                (*tokens)[(*tokenIndex)++] = '-';
                (*negativeNumber) = false;
            }
        }
        (*tokens)[(*tokenIndex)++] = input;
    }
}

bool initOperator(char input, char **tokens, int *tokenIndex)
{
    if (input == '-' || input == '+')
    {
        (*tokens)[(*tokenIndex)++] = VAR;
        (*tokens)[(*tokenIndex)++] = SEP;
        (*tokens)[(*tokenIndex)++] = '0';
        (*tokens)[(*tokenIndex)++] = NEWLINE;
        (*tokens)[(*tokenIndex)++] = OPR;
        (*tokens)[(*tokenIndex)++] = SEP;
        (*tokens)[(*tokenIndex)++] = input;
        (*tokens)[(*tokenIndex)++] = NEWLINE;
        return true;
    }
    return false;
}

bool bracketMinus(char input, char **tokens, int *tokenIndex, int *nNegative,
                  char *nType)
{
    if (input != '-')
    {
        (*nType) = '0';
        (*nNegative) = 0;
    }
    else if (((*nType) == '(') && (input == '-'))
    {
        if ((*nNegative) == 2)
        {
            initOperator(input, tokens, tokenIndex);
            (*nNegative) = 1;
            (*nType) = '-';
        }
        else
        {
            (*nNegative) += 1;
            (*nType) = '-';
        }
        return true;
    }
    else if (((*nType) == '0') && (input == '-'))
    {
        (*nNegative) += 1;
        (*nType) = '-';
    }
    return false;
}