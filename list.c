#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void initNumber(Number *n)
{
    n->head = NULL;
    n->tail = NULL;
    n->sign = PLUS;
    n->dec = 0;
}
void appendDigit(Number *n, char ch)
{
    if (ch >= '0' && ch < '9')
    {

        node *new_node = (node *)malloc(sizeof(node));
        // if malloc failed
        if (new_node == NULL)
            return;
        new_node->num = ch - '0';
        new_node->next = NULL;
        while (n->head == NULL && n->tail == NULL)
        {
            // node to be inserted is first
            n->head = new_node;
            n->tail = new_node;
            new_node->prev = NULL;
            return;
        }
        // node *p = n->head;
        // while (p->next != NULL)
        // {
        //     p = p->next;
        // }
        n->tail->next = new_node;
        new_node->prev = n->tail;
        n->tail = new_node;
    }
    return;
}
int length(Number n)
{
    node *p = n.head;
    int len = 0;
    while (p)
    {
        len++;
        p = p->next;
    }
    return len;
}
void displayNumber(Number *num)
{
    node *p = num->head;
    int len = length(*num);
    int posDecimal = len - num->dec;
    for (int i = 0; i < len; i++)
    {
        if (i == posDecimal)
            printf(".");
        printf("%d", p->num);
        p = p->next;
    }
}