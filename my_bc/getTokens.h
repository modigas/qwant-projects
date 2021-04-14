#include "libs.h"
#include "utils.h"
#include "stack.h"

#define OPR 'o'
#define VAR 'v'
#define SEP ','
#define NEWLINE '\n'

char *getTokens(char *inputString);
bool skipSpace(char input);
bool handleBrackets(char input, char **tokens, int *tokenIndex,
                    struct stack *brackets, bool *doubleOperator,
                    bool *numDetected, bool *error, int *nNegative, char *nType);
bool isBalancedBrackets(struct stack *brackets, char **tokens);
bool handleArithmetic(char input, char **tokens, int *tokenIndex,
                      bool *doubleOperator, bool *numDetected,
                      bool *negativeNumber, bool *error, int *nNegative,
                      char *nType);
bool handleNumber(char input, char **tokens, int *tokenIndex,
                  bool *doubleOperator, bool *numDetected,
                  bool *negativeNumber);
void writeOpAndNum(char **tokens, char input, int *tokenIndex, char type,
                   bool *numDetected, bool *negativeNumber);
bool initOperator(char input, char **tokens, int *tokenIndex);
bool bracketMinus(char input, char **tokens, int *tokenIndex, int *nNegative,
                  char *nType);