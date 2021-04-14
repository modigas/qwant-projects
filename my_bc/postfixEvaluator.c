#include "libs.h"
#include "stack.h"
#include "postfixEvaluator.h"
#include "utils.h"

#define NaN 1
#define mod(a, b) ((((a) % (b)) + (b)) % (b))

int postfixEval(char **postfixTokens)
{
    struct stack numbers = stack.new();
    int res = 0, flag = 0;
    char *tokens = *postfixTokens;
    char buffNum[100];
    int ind = 0, i = 0;
    while (tokens[i] != '\0')
    {
        if (tokens[i] != '\n')
        {
            if (isNum(tokens[i]) || (tokens[i] == '-' && isNum(tokens[i + 1])))
            {
                buffNum[ind++] = tokens[i];
            }
            if (isOp(tokens[i]) && !isNum(tokens[i + 1]))
            {
                int op2 = numbers.top(&numbers);
                numbers.pop(&numbers);
                int op1 = numbers.top(&numbers);
                numbers.pop(&numbers);
                res = evalExprs(op1, op2, tokens[i], &flag);
                //printf("%d %c %d = %d\n", op1, tokens[i], op2, res);
                if (flag)
                {
                    printf("Math Error\n!");
                    exit(1);
                }
                numbers.push(&numbers, res);
            }
        }
        if (tokens[i] == '\n' && ind != 0)
        {
            buffNum[ind] = '\0';
            numbers.push(&numbers, myAtoi(buffNum));
            ind = 0;
        }

        i++;
    }
    res = numbers.top(&numbers);
    numbers.destroy(&numbers);
    return res;
}

int evalExprs(int op1, int op2, char op, int *flag)
{
    int res = 0;

    switch (op)
    {
        case '-':
            res = op1 - op2;
            break;
        case '+':
            res = op1 + op2;
            break;
        case '*':
            res = op1 * op2;
            break;
        case '/':
            if (op2 == 0)
            {
                *flag = NaN;
                return res;
            }
            res = op1 / op2;
            break;
        case '%':
            if (op2 == 0)
            {
                *flag = NaN;
                return res;
            }
            res = mod(op1, op2);
            break;
    }
    return res;
}