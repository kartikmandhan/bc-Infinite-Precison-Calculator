#include "stack.h"
void cinit(cstack *s)
{
    *s = NULL;
}
void cpush(cstack *s, char ch)
{
    cnode *new_node = (cnode *)malloc(sizeof(cnode));
    if (new_node == NULL)
        return;
    new_node->ch = ch;
    new_node->next = *s;
    *s = new_node;
}
char cpop(cstack *s)
{
    if (!cisEmpty(*s))
    {
        cnode *p = *s;
        char ch = p->ch;
        *s = p->next;
        free(p);
        return ch;
    }
    return '\0';
}
int cisEmpty(cstack s)
{
    return s == NULL;
}
char ctop(cstack s)
{
    if (!cisEmpty(s))
        return s->ch;
    return '\0';
}
void init(istack *s)
{
    *s = NULL;
}
void push(istack *s, int d)
{
    inode *new_node = (inode *)malloc(sizeof(inode));
    if (new_node == NULL)
        return;
    new_node->data = d;
    new_node->next = *s;
    *s = new_node;
}
int pop(istack *s)
{
    if (!isEmpty(*s))
    {
        inode *p = *s;
        char data = p->data;
        *s = p->next;
        free(p);
        return data;
    }
    return INT_MIN;
}
int isEmpty(istack s)
{
    return s == NULL;
}
int top(istack s)
{
    if (!isEmpty(s))
        return s->data;
    return INT_MIN;
}