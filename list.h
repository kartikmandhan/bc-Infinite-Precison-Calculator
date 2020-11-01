#ifndef LIST_H_
#define LIST_H_

// List.h code

#define PLUS 1
#define MINUS -1

typedef struct node
{
    int num;
    struct node *next, *prev;
} node;
typedef struct Number
{
    int sign, dec;
    node *head, *tail;
} Number;
void initNumber(Number *n);
void appendDigit(Number *n, char ch);
int length(Number n);
void displayNumber(Number *num);
Number *add(Number *n1, Number *n2);
void removeZeros(Number *n1);
void insertAtBegining(Number *num, int no);
Number *makeLengthEqual(Number *a, Number *b);
Number *makeDecimalEqual(Number *a, Number *b);
int compareEqual(Number a, Number b);
Number *sub(Number *n1, Number *n2);
int isNumber0(Number *n1);
Number *multiply(Number *n1, Number *n2);
Number *divide(Number *n1, Number *n2);
Number *modulus(Number *n1, Number *n2);
#endif
