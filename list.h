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
