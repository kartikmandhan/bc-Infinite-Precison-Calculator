#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
typedef struct cnode
{
    char ch;
    struct cnode *next;
} cnode;
typedef cnode *cstack;
void cinit(cstack *s);
void cpush(cstack *s, char ch);
char cpop(cstack *s);
int cisEmpty(cstack s);
char ctop(cstack s);

typedef struct inode
{
    int data;
    struct inode *next;
} inode;
typedef inode *istack;
void init(istack *s);
void push(istack *s, int d);
int pop(istack *s);
int isEmpty(istack s);
int top(istack s);