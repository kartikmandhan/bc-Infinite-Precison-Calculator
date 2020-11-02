#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define SCALE 31

void initNumber(Number *n)
{
    n->head = NULL;
    n->tail = NULL;
    n->sign = PLUS;
    n->dec = 0;
}
void appendDigit(Number *n, char ch)
{
    if (ch >= '0' && ch <= '9')
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
void removeZeros(Number *n1)
{
    node *p = n1->head;
    int i, len = length(*n1);
    for (i = 0; i < len - n1->dec - 1; i++)
    {
        if (p->num == 0)
        {
            n1->head = p->next;
            n1->head->prev = NULL;
            free(p);
            p = n1->head;
        }
        else
        {
            break;
        }
    }
    p = n1->tail;
    int decimal = n1->dec;
    for (i = 0; i < decimal - 1; i++)
    {
        if (p->num == 0)
        {
            n1->tail = p->prev;
            n1->tail->next = NULL;
            free(p);
            p = n1->tail;
            n1->dec--;
        }
        else
        {
            break;
        }
    }
    return;
}
void displayNumber(Number *num)
{
    removeZeros(num);
    node *p = num->head;
    if (num->sign == MINUS)
    {
        printf("-");
    }
    int posDecimal = length(*num) - num->dec;
    if (posDecimal < 0)
    {
        printf("0.");
        for (int i = posDecimal; i < 0; i++)
        {
            printf("0");
        }
    }
    for (int i = 0; i < length(*num); i++)
    {
        if (i == posDecimal)
            printf(".");
        printf("%d", p->num);
        p = p->next;
    }
    printf("\n");
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
            new_node->next = NULL;
            num->head = new_node;
            num->tail = new_node;
            return;
        }
        new_node->next = num->head;
        num->head->prev = new_node;
        num->head = new_node;
    }
}
Number *makeLengthEqual(Number *a, Number *b)
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
int compareEqual(Number a, Number b)
{
    makeLengthEqual(&a, &b);
    makeDecimalEqual(&a, &b);
    // if some error try swapping positions ofabove two functions
    // 3.1234 3.12=>3.1234 003.1200
    node *p, *q;
    int len;
    int i;
    len = length(a);
    p = a.head;
    q = b.head;
    for (i = 1; i <= len; i++)
    {
        if (p->num > q->num)
            return 1; //i.e. Number a greater than Number b.
        else if (p->num < q->num)
            return -1; //i.e. a is less than b.
        p = p->next;
        q = q->next;
    }
    return 0; //i.e. both numbers are equal.
}

Number *sub(Number *n1, Number *n2)
{
    Number *ans = (Number *)malloc(sizeof(Number));
    initNumber(ans);
    makeDecimalEqual(n1, n2);
    makeLengthEqual(n1, n2);
    if (n1->sign != n2->sign && n1->sign == MINUS)
    {
        // (-5) - (3)
        n1->sign = PLUS;
        ans = add(n1, n2);
        ans->sign = MINUS;
    }
    else if (n1->sign != n2->sign && n2->sign == MINUS)
    {
        // 5 - (-3)
        n2->sign = PLUS;
        ans = add(n1, n2);
        ans->sign = PLUS;
    }
    else if (n1->sign == n2->sign)
    {
        if (n1->sign == MINUS)
        {
            // -5 - (-3)=>3-5
            n2->sign = n1->sign = PLUS;
            ans = sub(n2, n1);
        }
        else if (n1->sign == PLUS)
        {
            int substraction, diff = 0, borrow = 0, dig_a, dig_b, len = length(*n1);
            node *tail_a = n1->tail;
            node *tail_b = n2->tail;
            if (compareEqual(*n1, *n2) == 1)
            {
                // n1 is greater than n2
                for (int i = 0; i < len; i++)
                {
                    dig_a = tail_a->num;
                    dig_b = tail_b->num;
                    dig_a -= borrow;
                    if (dig_a >= dig_b)
                    {
                        diff = dig_a - dig_b;
                        borrow = 0;
                        insertAtBegining(ans, diff);
                    }
                    else
                    {
                        dig_a += 10;
                        diff = dig_a - dig_b;
                        borrow = 1;
                        insertAtBegining(ans, diff);
                    }
                    tail_a = tail_a->prev;
                    tail_b = tail_b->prev;
                }
            }
            else if (compareEqual(*n1, *n2) == -1)
            {
                for (int i = 0; i < len; i++)
                {
                    dig_a = tail_a->num;
                    dig_b = tail_b->num;
                    dig_b -= borrow;
                    if (dig_b >= dig_a)
                    {
                        diff = dig_b - dig_a;
                        borrow = 0;
                        insertAtBegining(ans, diff);
                    }
                    else
                    {
                        dig_b += 10;
                        diff = dig_b - dig_a;
                        borrow = 1;
                        insertAtBegining(ans, diff);
                    }
                    tail_a = tail_a->prev;
                    tail_b = tail_b->prev;
                }
                ans->sign = MINUS;
            }
            else
            {
                // both the numbers are equal
                insertAtBegining(ans, 0);
            }
        }
    }
    return ans;
}

Number *add(Number *n1, Number *n2)
{
    Number *ans = (Number *)malloc(sizeof(Number));
    initNumber(ans);

    // 3.1234
    // 3.12
    // then tail points to 4 and 2 respectively but we dont want to add them in addition
    // hnce we make decimal equal by makeing 3.12 to 3.1200
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
        node *tail_b = n2->tail;

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
    // free(n1);
    return ans;
}

int isNumber0(Number *n1)
{
    node *p = n1->head;
    for (int i = 0; i < length(*n1); i++)
    {
        if (p->num != 0)
        {
            return 0;
        }
        p = p->next;
    }
    return 1;
}
Number *multiply(Number *n1, Number *n2)
{
    Number *ans = malloc(sizeof(Number));
    initNumber(ans);

    if (isNumber0(n1) || isNumber0(n2))
    {
        insertAtBegining(ans, 0);
        return ans;
    }
    if (n1->sign == n2->sign)
    {
        ans->sign = PLUS;
        n1->sign = n2->sign = PLUS;
    }
    else
    {
        ans->sign = MINUS;
        n1->sign = n2->sign = PLUS;
    }
    int len_a = length(*n1);
    int len_b = length(*n2);
    int max_len = len_a > len_b ? 2 * len_a : 2 * len_b;
    int i, j, p, q, multCarry, addCarry;
    node *tail_n1, *tail_n2 = n2->tail;
    int *tempMult = calloc(max_len, sizeof(int));

    for (i = 0; i < len_b; i++)
    {
        tail_n1 = n1->tail;
        addCarry = 0, multCarry = 0;
        for (j = max_len - i - 1; j >= 0; j--)
        {
            if (tail_n1 && tail_n2)
            {
                p = tail_n1->num * tail_n2->num + multCarry;
                tail_n1 = tail_n1->prev;
                multCarry = p / 10;
                p = p % 10;
                q = p + addCarry + tempMult[j];
                addCarry = q / 10;
                q = q % 10;
                tempMult[j] = q;
            }
            else
            {
                break;
            }
        }
        tempMult[j] += addCarry + multCarry;
        tail_n2 = tail_n2->prev;
        // for (int i = 0; i < max_len; i++)
        // {
        //     printf("%d ", tempMult[i]);
        // }
        // printf("\n");
    }
    for (int i = max_len - 1; i >= 0; i--)
    {
        insertAtBegining(ans, tempMult[i]);
    }
    ans->dec = n1->dec + n2->dec;
    return ans;
}

Number *divide(Number *n1, Number *n2)
{
    if (isNumber0(n2))
    {
        printf("Can't divide by 0\n");
        return NULL;
    }
    removeZeros(n1);
    removeZeros(n2);
    int k = n1->dec > n2->dec ? n1->dec : n2->dec;
    int i = 0;
    // remove decimal and append 0 eg
    // 3.144/22.1 =>3144/22100
    while (i < k)
    {
        if (n1->dec > 0)
            n1->dec--;
        else
            appendDigit(n1, '0');
        if (n2->dec > 0)
            n2->dec--;
        else
            appendDigit(n2, '0');
        i++;
    }
    i = 9;
    Number *c, *dividend, *tmpAns, *q, *pro;
    c = (Number *)malloc(sizeof(Number));
    dividend = (Number *)malloc(sizeof(Number));
    tmpAns = (Number *)malloc(sizeof(Number));
    pro = (Number *)malloc(sizeof(Number));
    q = (Number *)malloc(sizeof(Number));
    initNumber(tmpAns);
    initNumber(c);
    initNumber(q);
    initNumber(dividend);
    initNumber(pro);
    if (n1->sign == n2->sign)
    {
        q->sign = PLUS;
        n1->sign = n2->sign = PLUS;
    }
    else
    {
        q->sign = MINUS;
        n1->sign = n2->sign = PLUS;
    }
    node *p = n1->head;
    char ch = p->num + '0';
    appendDigit(dividend, ch);
    while (q->dec < SCALE)
    {
        while (i >= 0)
        {
            insertAtBegining(c, i); //converting i from int to Number Datatype,so that we can directly use functions
            pro = multiply(n2, c);
            tmpAns = sub(dividend, pro);
            if (tmpAns->sign != MINUS)
            {
                // printf("%d inside\n", i);
                appendDigit(q, i + '0');
                // delete c number to make it again assign to single digit and free up memory
                node *tmp = c->head;
                free(tmp);
                c->head = c->tail = NULL;
                break;
            }
            else
            {
                // delete c number to make it again assign to single digit and free up memory
                node *tmp = c->head;
                free(tmp);
                c->head = c->tail = NULL;
                i--;
            }
        }
        dividend = tmpAns;
        if (p->next != NULL)
        {
            // this part does bringing down next digit in division i.e 51/3=>2'1' brings 1 and append it to dividend
            p = p->next;
            ch = p->num + '0';
            appendDigit(dividend, ch);
        }
        else
        {
            // add zeroes to end of dividend 10/11=>100/11 and increase count of decimal by 1
            q->dec++;
            // printf("%d\n", q->dec);
            appendDigit(dividend, '0');
        }
        i = 9;
        // delete c number to make it again assign to single digit and free up memory
        node *tmp = c->head;
        free(tmp);
        c->head = c->tail = NULL;
    }
    q->dec--;
    // makes count of decimal from 31 to 30(correct)
    return q;
}
Number *modulus(Number *n1, Number *n2)
{
    if (isNumber0(n2))
    {
        printf("Can't perform modulus by 0\n");
        return NULL;
    }
    removeZeros(n1);
    removeZeros(n2);
    int k = n1->dec > n2->dec ? n1->dec : n2->dec;
    int i = 0;
    // remove decimal and append 0 eg
    // 3.144/22.1 =>3144/22100
    while (i < k)
    {
        if (n1->dec > 0)
            n1->dec--;
        else
            appendDigit(n1, '0');
        if (n2->dec > 0)
            n2->dec--;
        else
            appendDigit(n2, '0');
        i++;
    }
    i = 9;
    Number *c, *dividend, *tmpAns, *q, *pro;
    c = (Number *)malloc(sizeof(Number));
    dividend = (Number *)malloc(sizeof(Number));
    tmpAns = (Number *)malloc(sizeof(Number));
    pro = (Number *)malloc(sizeof(Number));
    q = (Number *)malloc(sizeof(Number));
    initNumber(tmpAns);
    initNumber(c);
    initNumber(q);
    initNumber(dividend);
    initNumber(pro);
    if (n1->sign == n2->sign)
    {
        q->sign = PLUS;
        n1->sign = n2->sign = PLUS;
    }
    else
    {
        q->sign = MINUS;
        n1->sign = n2->sign = PLUS;
    }
    node *p = n1->head;
    char ch = p->num + '0';
    appendDigit(dividend, ch);
    while (q->dec < SCALE)
    {
        while (i >= 0)
        {
            insertAtBegining(c, i); //converting i from int to Number Datatype,so that we can directly use functions
            pro = multiply(n2, c);
            tmpAns = sub(dividend, pro);
            if (tmpAns->sign != MINUS)
            {
                // printf("%d inside\n", i);
                appendDigit(q, i + '0');
                // delete c number to make it again assign to single digit and free up memory
                node *tmp = c->head;
                free(tmp);
                c->head = c->tail = NULL;
                break;
            }
            else
            {
                // delete c number to make it again assign to single digit and free up memory
                node *tmp = c->head;
                free(tmp);
                c->head = c->tail = NULL;
                i--;
            }
        }
        dividend = tmpAns;
        if (p->next != NULL)
        {
            // this part does bringing down next digit in division i.e 51/3=>2'1' brings 1 and append it to dividend
            p = p->next;
            ch = p->num + '0';
            appendDigit(dividend, ch);
        }
        else
        {
            // set decimal count of the answer as the max of the two digit's decimal
            tmpAns->dec = k;
            return tmpAns;
        }
        i = 9;
        // delete c number to make it again assign to single digit and free up memory
        node *tmp = c->head;
        free(tmp);
        c->head = c->tail = NULL;
    }
}

Number *power(Number *n1, Number *n2)
{

    Number *ans = (Number *)malloc(sizeof(Number));
    initNumber(ans);
    Number *one = (Number *)malloc(sizeof(Number));
    initNumber(one);
    insertAtBegining(one, 1);
    int reciprocate = 0;
    node *b = n2->tail;
    if (n1->sign == PLUS && n2->sign == MINUS)
    {
        n2->sign = PLUS;
        reciprocate = 1;
    }
    else if (n1->sign == MINUS)
    {
        if (b->num % 2 == 0)
        {
            ans->sign = PLUS;
        }
        else
        {
            ans->sign = MINUS;
        }
        n1->sign = PLUS;
        if (n2->sign == MINUS)
        {
            reciprocate = 1;
            n2->sign = PLUS;
        }
    }
    n2 = sub(n2, one);
    // displayNumber(n2);
    while (!isNumber0(n2))
    {
        ans = multiply(n1, n1);
        // displayNumber(ans);
        n2 = sub(n2, one);
    }
    if (reciprocate)
    {
        ans = divide(one, ans);
    }

    return ans;
}

int main()
{
    Number *n1, *n2, *n3;
    n1 = (Number *)malloc(sizeof(Number));
    n2 = (Number *)malloc(sizeof(Number));
    n3 = (Number *)malloc(sizeof(Number));
    initNumber(n1);
    initNumber(n2);
    initNumber(n3);
    insertAtBegining(n1, 9);
    // appendDigit(n1, '0');
    // appendDigit(n1, '5');
    // appendDigit(n1, '4');
    // n1->dec = 1;
    // n1->dec = 6;
    appendDigit(n2, '2');
    // appendDigit(n2, '0');
    // appendDigit(n1, '3');
    // appendDigit(n1, '8');
    // appendDigit(n2, '8');
    // appendDigit(n2, '9');
    // appendDigit(n2, '2');
    // appendDigit(n2, '3');
    // displayNumber(n1);
    displayNumber(n1);
    displayNumber(n2);
    n3 = power(n1, n2);
    displayNumber(n3);
    // printf("%d", length(*n1));

    // displayNumber(n3);
    // n3 = add(n1, n2);
    // displayNumber(n3);

    // printf("%d\n", compareEqual(*n1, *n2));
}