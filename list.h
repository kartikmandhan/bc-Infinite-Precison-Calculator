#ifndef LIST_H_
#define LIST_H_

// List.h code
#include <stdio.h>
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
void writeNumberInfile(Number *num, FILE *fp);
void removeZeros(Number *n1);
void insertAtBegining(Number *num, int no);
void makeLengthEqual(Number *a, Number *b);
void makeDecimalEqual(Number *a, Number *b);
int compareMagnitude(Number a, Number b);
double NumberToDouble(Number *n1);
Number *doubletoNumber(double a);
int isNumber0(Number *n1);
void duplicateNumber(Number *n1, Number *n2);
Number *TheNumberE();
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
Number *exponent(Number *n1);
Number *sqRoot(Number *n1);
Number *Len(Number *n1);
Number *Factorial(Number *n1);
void setScale(Number *n1);
#endif
