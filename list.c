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
    if (num->sign == MINUS)
    {
        printf("-");
    }

    for (int i = 0; i < len; i++)
    {
        if (i == posDecimal)
            printf(".");
        printf("%d", p->num);
        p = p->next;
    }
}
void insertAtBegining(Number *num, int no)
{
    if (no >= 0 && no <= 9)
    {
        node *new_node = (node *)malloc(sizeof(node));
        if (new_node == NULL)
        {
            return;
        }
        new_node->num = no;
        new_node->prev = NULL;
        if (num->head == NULL && num->tail == NULL)
        {
            new_node->prev = NULL;
            num->head = new_node;
            num->tail = new_node;
            return;
        }
        new_node->next = num->head;
        num->head->prev = new_node;
        num->head = new_node;
    }
}
Number *makeBeforeDecimalEqual(Number *a, Number *b)
{
    int diff = length(*a) - length(*b);
    if (diff > 0)
    {
        for (int i = 0; i < diff; i++)
        {
            insertAtBegining(b, 0);
        }
    }
    else
    {
        diff = -diff;
        for (int i = 0; i < diff; i++)
        {
            insertAtBegining(a, 0);
        }
    }
}
Number *makeDecimalEqual(Number *a, Number *b)
{
    int diff = a->dec - b->dec;
    if (diff > 0)
    {
        for (int i = 0; i < diff; i++)
        {
            appendDigit(b, '0');
            b->dec++;
        }
    }
    else
    {
        diff = -diff;
        for (int i = 0; i < diff; i++)
        {
            appendDigit(a, '0');
            a->dec++;
        }
    }
}
Number *sub(Number *n1, Number *n2)
{
}

Number *add(Number *n1, Number *n2)
{
    Number *ans = (Number *)malloc(sizeof(Number));
    initNumber(ans);
    makeDecimalEqual(n1, n2);
    if (n1->sign != n2->sign && n1->sign == MINUS)
    {
        n1->sign = PLUS;
        ans = sub(n2, n1);
    }
    else if (n1->sign != n2->sign && n2->sign == MINUS)
    {
        n2->sign = PLUS;
        ans = sub(n1, n2);
    }
    else if (n1->sign == n2->sign)
    {
        int addition, sum = 0, carry = 0, len_a = length(*n1), len_b = length(*n2);
        node *tail_a = n1->tail;
        node *tail_b = n1->tail;

        if (len_a >= len_b)
        {
            for (int i = 0; i < len_b; i++)
            {
                addition = tail_a->num + tail_b->num + carry;
                sum = addition % 10;
                carry = addition / 10;
                insertAtBegining(ans, sum);
                tail_a = tail_a->prev;
                tail_b = tail_b->prev;
            }
            for (int i = 0; i < len_a - len_b; i++)
            {
                addition = tail_a->num + carry;
                sum = addition % 10;
                carry = addition / 10;
                insertAtBegining(ans, sum);
                tail_a = tail_a->prev;
            }
        }
        else
        {
            for (int i = 0; i < len_a; i++)
            {
                addition = tail_b->num + tail_a->num + carry;
                sum = addition % 10;
                carry = addition / 10;
                insertAtBegining(ans, sum);
                tail_b = tail_b->prev;
                tail_a = tail_a->prev;
            }
            for (int i = 0; i < len_b - len_a; i++)
            {
                addition = tail_b->num + carry;
                sum = addition % 10;
                carry = addition / 10;
                insertAtBegining(ans, sum);
                tail_b = tail_b->prev;
            }
        }
        ans->dec = n1->dec;
        if (carry != 0)
        {
            insertAtBegining(ans, carry);
        }

        if (n1->sign == MINUS)
            ans->sign = MINUS;
        else
            ans->sign = PLUS;
    }
    return ans;
}