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
void removeZeros(Number *n1);
void insertAtBegining(Number *num, int no);
void makeLengthEqual(Number *a, Number *b);
void makeDecimalEqual(Number *a, Number *b);
int compareEqual(Number a, Number b);
int isNumber0(Number *n1);
void duplicateNumber(Number *n1, Number *n2);
// calculations
Number *add(Number *n1, Number *n2);
Number *sub(Number *n1, Number *n2);
Number *multiply(Number *n1, Number *n2);
Number *divide(Number *n1, Number *n2);
Number *modulus(Number *n1, Number *n2);
Number *floordivide(Number *n1, Number *n2);
Number *power(Number *n1, Number *n2);
Number *Sin(Number *n1);
Number *Cos(Number *n1);
Number *Tan(Number *n1);
#endif
