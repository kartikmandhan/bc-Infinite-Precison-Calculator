#ifndef STACK_H_
#define STACK_H_

#include "list.h"

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
    Number *data;
    struct inode *next;
} inode;
typedef inode *istack;
void init(istack *s);
void push(istack *s, Number *d);
Number *pop(istack *s);
int isEmpty(istack s);
Number *top(istack s);
#endif
