#ifndef INFIX_H_
#define INFIX_H_
#include "list.h"
typedef struct token
{
    Number *num;
    int type;
    char op;
} token;
#define OPERAND 10
#define OPERATOR 20
#define END 30
#define ERR 40
token getToken(char *expr, int *reset);
int precedence(char op);
Number *infix(char *expression);
#endif