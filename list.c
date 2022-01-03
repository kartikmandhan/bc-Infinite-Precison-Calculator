#include <stdio.h>
#include <stdlib.h>
#include "list.h"
// int scale = 30;
extern int scale;
#include <string.h>
#include <math.h>
void initNumber(Number *n)
{
    n->head = NULL;
    n->tail = NULL;
    n->sign = PLUS;
    n->dec = 0;
}
// this function takes char 0 to 9 and appends them into Number
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
// this function converts Number to double
double NumberToDouble(Number *n1)
{
    double ans;
    char temp[1024];
    node *p = n1->head;
    int i;
    int posDecimal = length(*n1) - n1->dec;
    for (i = 0; p != NULL; i++)
    {
        if (i == posDecimal)
        {
            temp[i] = '.';
            i++;
        }
        temp[i] = p->num + '0';
        p = p->next;
    }
    temp[i] = '\0';
    sscanf(temp, "%lf", &ans);
    if (n1->sign == MINUS)
    {
        ans = -1 * ans;
    }
    return ans;
}
// this function converts double to Number
Number *doubletoNumber(double a)
{
    Number *ans = (Number *)malloc(sizeof(Number));
    initNumber(ans);
    char temp[1024];
    sprintf(temp, "%lf", a);
    int i = 0;
    if (temp[i] == '-')
    {
        ans->sign = MINUS;
        i++;
    }
    for (; temp[i] != '\0'; i++)
    {
        if (temp[i] == '.')
        {
            ans->dec = strlen(temp) - i - 1;
        }
        else
        {
            appendDigit(ans, temp[i]);
        }
    }
    return ans;
}
// this length function is needed by other functions for their working
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
// this function converts int to Number
void intToNumber(int d, Number *n1)
{
    char temp[256];
    sprintf(temp, "%d", d);
    int i = 0;
    if (temp[i] == '-')
    {
        n1->sign = MINUS;
        i++;
    }
    for (; temp[i] != '\0'; i++)
    {
        appendDigit(n1, temp[i]);
    }
}
// This Length function serves as a operation
Number *Len(Number *n1)
{
    Number *ans = (Number *)malloc(sizeof(Number));
    initNumber(ans);
    int len = length(*n1);
    intToNumber(len, ans);
    return ans;
}
// this function removes zeros from starting as well as after decimal point 003.1400 =>3.14
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
// this function displays Number on stdout
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
// this function prints the Number in the File
void writeNumberInfile(Number *num, FILE *fp)
{
    removeZeros(num);
    node *p = num->head;
    if (num->sign == MINUS)
    {
        fprintf(fp, "-");
    }
    int posDecimal = length(*num) - num->dec;
    if (posDecimal < 0)
    {
        fprintf(fp, "0.");
        for (int i = posDecimal; i < 0; i++)
        {
            fprintf(fp, "0");
        }
    }
    for (int i = 0; i < length(*num); i++)
    {
        if (i == posDecimal)
            fprintf(fp, ".");
        fprintf(fp, "%d", p->num);
        p = p->next;
    }
    fprintf(fp, "\n");
}
// This function inserts insert int 0 to 9 at head position
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
// Makes length of two Number equal by prepending Zeroes at the start
void makeLengthEqual(Number *a, Number *b)
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
// Makes length of two Number equal by appending Zeroes after decimal point
void makeDecimalEqual(Number *a, Number *b)
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
// Return 1 |n1|>|n2|, -1 for |n1|<|n2|, 0 for |n1|=|n2|
int compareMagnitude(Number n1, Number n2)
{
    makeDecimalEqual(&n1, &n2);
    makeLengthEqual(&n1, &n2);
    // 3.1234, 3.12=>3.1234, 3.1200
    node *p, *q;
    int len;
    int i;
    // as length of both the numbers is same at this point
    len = length(n1);
    p = n1.head;
    q = n2.head;
    for (i = 1; i <= len; i++)
    {
        if (p->num > q->num)
            return 1; //i.e. Number n1 greater than Number n2.
        else if (p->num < q->num)
            return -1; //i.e. n1 is less than n2.
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
            int diff = 0, borrow = 0, dig_a, dig_b, len = length(*n1);
            node *tail_a = n1->tail;
            node *tail_b = n2->tail;
            if (compareMagnitude(*n1, *n2) == 1)
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
            else if (compareMagnitude(*n1, *n2) == -1)
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
    ans->dec = n1->dec;
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
// Returns 1(True) if Number is 0, else returns 0(False)
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
    int max_len = len_a > len_b ? len_a : len_b;
    // printf("len1:%d\n", max_len);
    int twice_max_len = max_len * 2;
    int i, j, p, q, multCarry, addCarry;
    node *tail_n1, *tail_n2 = n2->tail;
    // twice of max len to be on safe side,as 99*10=990,i.e 3 digits but 99*99=9801,i.e 4 digits
    int *tempMult = calloc(twice_max_len, sizeof(int));
    // calloc makes all the array elements 0
    for (i = 0; i < len_b; i++)
    {
        tail_n1 = n1->tail;
        addCarry = 0, multCarry = 0;
        // for (j = twice_max_len - i - 1; j > 0; j--)
        for (j = twice_max_len - i - 1; j > max_len - 2; j--)
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
        // max_len at the end will keep track of how many digits to be inserted
        // so that 0s at the start are not unnecessary filled in our number
        max_len--;
        // printf("len:%d\n", max_len);
        tail_n2 = tail_n2->prev;
        // for (int i = 0; i < twice_max_len; i++)
        // {
        //     printf("%d ", tempMult[i]);
        // }
        // printf("\n");
    }
    // for (int i = twice_max_len - 1; i >= 0; i--)
    for (int i = twice_max_len - 1; i >= max_len && i >= 0; i--)
    {
        insertAtBegining(ans, tempMult[i]);
    }
    ans->dec = n1->dec + n2->dec;
    free(tempMult);
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
    while (1)
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
                // delete c Number to make it again assign to single digit and free up memory
                node *tmp = c->head;
                free(tmp);
                c->head = c->tail = NULL;
                break;
            }
            else
            {
                // delete c Number to make it again assign to single digit and free up memory
                node *tmp = c->head;
                free(tmp);
                c->head = c->tail = NULL;
                i--;
            }
        }
        dividend = tmpAns;
        if (p->next != NULL)
        {
            // this part does bringing down next digit in divide i.e 51/3=>2'1' brings 1 and append it to dividend
            p = p->next;
            ch = p->num + '0';
            appendDigit(dividend, ch);
        }
        else
        {
            // add zeroes to end of dividend 10/11=>100/11 and increase count of decimal by 1
            if (q->dec == scale)
            {
                free(c->head);
                free(c);
                free(dividend);
                // dividend and tempans point to same memory
                // free(tmpAns);
                free(pro);
                return q;
            }
            q->dec++;
            appendDigit(dividend, '0');
        }
        i = 9;
        // delete c Number to make it again assign to single digit and free up memory
        node *tmp = c->head;
        free(tmp);
        c->head = c->tail = NULL;
    }
}
// 1/3 =>0, 4/3=>1,it returns quotient with no decimal points
Number *floordivide(Number *n1, Number *n2)
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
    while (1)
    {
        while (i >= 0)
        {
            insertAtBegining(c, i);
            pro = multiply(n2, c);
            tmpAns = sub(dividend, pro);
            if (tmpAns->sign != MINUS)
            {
                // printf("%d inside\n", i);
                appendDigit(q, i + '0');
                // delete c Number to make it again assign to single digit and free up memory
                node *tmp = c->head;
                free(tmp);
                c->head = c->tail = NULL;
                break;
            }
            else
            {
                // delete c Number to make it again assign to single digit and free up memory
                node *tmp = c->head;
                free(tmp);
                c->head = c->tail = NULL;
                i--;
            }
        }
        dividend = tmpAns;
        if (p->next != NULL)
        {
            // this part does bringing down next digit in divide i.e 51/3=>2'1' brings 1 and append it to dividend
            p = p->next;
            ch = p->num + '0';
            appendDigit(dividend, ch);
        }
        else
        {
            free(c);
            free(dividend);
            // free(tmpAns);
            free(pro);
            return q;
        }
        i = 9;
        // delete c Number to make it again assign to single digit and free up memory
        node *tmp = c->head;
        free(tmp);
        c->head = c->tail = NULL;
    }
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
    while (1)
    {
        while (i >= 0)
        {
            insertAtBegining(c, i); //converting i from int to Number Datatype,so that we can directly use functions
            pro = multiply(n2, c);
            tmpAns = sub(dividend, pro);
            if (tmpAns->sign != MINUS)
            {
                appendDigit(q, i + '0');
                // delete c Number to make it again assign to single digit and free up memory
                node *tmp = c->head;
                free(tmp);
                c->head = c->tail = NULL;
                break;
            }
            else
            {
                // delete c Number to make it again assign to single digit and free up memory
                node *tmp = c->head;
                free(tmp);
                c->head = c->tail = NULL;
                i--;
            }
        }
        dividend = tmpAns;
        if (p->next != NULL)
        {
            // this part does bringing down next digit in divide i.e 51/3=>2'1' brings 1 and append it to dividend
            p = p->next;
            ch = p->num + '0';
            appendDigit(dividend, ch);
        }
        else
        {
            // set decimal count of the answer as the max of the two digit's decimal
            free(c->head);
            free(c);
            free(q->head);
            free(q);
            free(pro);
            tmpAns->dec = k;
            return tmpAns;
        }
        i = 9;
        // delete c Number to make it again assign to single digit and free up memory
        node *tmp = c->head;
        free(tmp);
        c->head = c->tail = NULL;
    }
}
// copy n2 into n1
void duplicateNumber(Number *n1, Number *n2)
{
    n1->sign = n2->sign;
    n1->sign = n2->sign;
    node *p = n2->head;
    int d;
    for (int i = 0; i < length(*n2); i++)
    {
        d = p->num;
        appendDigit(n1, d + '0');
        p = p->next;
    }
}
// this return value of 2pi accurate upto 30 decimal places
Number *twoPI()
{
    Number *twopi = (Number *)malloc(sizeof(Number));
    initNumber(twopi);
    // value of 2pi upto 30 decimal digits
    char value[] = "6.283185307179586476925286766559";
    int i = 0;
    while (value[i] != '\0')
    {
        appendDigit(twopi, value[i]);
        i++;
    }
    twopi->dec = 30;
    return twopi;
}
int NumberToint(Number *n1)
{
    int ans;
    char temp[1024];
    node *p = n1->head;
    int i;
    for (i = 0; p != NULL; i++)
    {
        temp[i] = p->num + '0';
        p = p->next;
    }
    temp[i] = '\0';
    sscanf(temp, "%d", &ans);
    if (n1->sign == MINUS)
    {
        ans = -1 * ans;
    }
    return ans;
}
Number *power(Number *n1, Number *n2)
{
    // if(n2->dec)

    int reciprocate = 0, answerNegative = 0, countDecimal = n1->dec;
    if (n2->sign == MINUS)
    {
        reciprocate = 1;
    }
    Number *ans = (Number *)malloc(sizeof(Number));
    initNumber(ans);
    insertAtBegining(ans, 1);
    Number *one = (Number *)malloc(sizeof(Number));
    initNumber(one);
    insertAtBegining(one, 1);
    Number *copyn2 = (Number *)malloc(sizeof(Number));
    initNumber(copyn2);
    Number *two = (Number *)malloc(sizeof(Number));
    initNumber(two);
    insertAtBegining(two, 2);
    if (isNumber0(n2))
    {
        return one;
    }
    else if (isNumber0(sub(n2, one)))
    {
        return n1;
    }
    // copy n1 to answer
    node *lastDigit = n2->tail;

    if (n1->sign == PLUS && n2->sign == MINUS)
    {
        n2->sign = PLUS;
    }
    else if (n1->sign == MINUS)
    {
        if (lastDigit->num % 2)
            // power is odd,hence answer will be negative
            answerNegative = 1;
        n1->sign = PLUS;
        if (n2->sign == MINUS)
        {
            n2->sign = PLUS;
        }
    }
    duplicateNumber(copyn2, n2);
    // while (y > 0)
    // {
    //     if (y % 2)
    //     {
    //         prod *= term;
    //     }
    //     term = term * term;
    //     y = y / 2;
    // }
    // faster algorithm try 2054^3000->it contains 9938 digits,this algo computes this in 1 sec
    while (!isNumber0(n2))
    {
        lastDigit = n2->tail;
        if (lastDigit->num % 2)
        {
            ans = multiply(ans, n1);
        }
        n1 = multiply(n1, n1);
        n2 = floordivide(n2, two);
    }
    // slower approach,takes n2 Number of multiplications
    // while (!isNumber0(n2))
    // {
    //     ans = multiply(n1, ans);
    //     // displayNumber(ans);
    //     n2 = sub(n2, one);
    // }
    if (reciprocate)
        ans = divide(one, ans);
    if (answerNegative)
        ans->sign = MINUS;
    if (countDecimal > ans->dec)
    {
        int multiplicativeFactor = NumberToint(copyn2);
        ans->dec = countDecimal * multiplicativeFactor;
    }
    free(one);
    free(copyn2);
    free(two);
    return ans;
}
Number *Sin(Number *n1)
{
    int minus = 0;
    Number *ans = (Number *)malloc(sizeof(Number));
    Number *angleInRadians = (Number *)malloc(sizeof(Number));
    initNumber(ans);
    initNumber(angleInRadians);
    if (n1->sign == MINUS)
        minus = 1;
    // this minus variable is created to remember sign of n1
    angleInRadians = modulus(n1, twoPI());
    // After modulus call gets finished sign of n1 is changed to PLUS inside modulus
    if (minus)
        angleInRadians->sign = MINUS;
    double angle = NumberToDouble(angleInRadians);
    double value = sinl(angle);
    ans = doubletoNumber(value);
    free(angleInRadians);
    return ans;
}
Number *Cos(Number *n1)
{
    int minus = 0;
    Number *ans = (Number *)malloc(sizeof(Number));
    Number *angleInRadians = (Number *)malloc(sizeof(Number));
    initNumber(ans);
    initNumber(angleInRadians);
    if (n1->sign == MINUS)
        minus = 1;
    // this minus variable is created to remember sign of n1
    angleInRadians = modulus(n1, twoPI());
    // After modulus call gets finished sign of n1 is changed to PLUS inside modulus
    if (minus)
        angleInRadians->sign = MINUS;
    double angle = NumberToDouble(angleInRadians);
    double value = cosl(angle);
    ans = doubletoNumber(value);
    free(angleInRadians);
    return ans;
}
Number *Tan(Number *n1)
{
    int minus = 0;
    Number *ans = (Number *)malloc(sizeof(Number));
    Number *angleInRadians = (Number *)malloc(sizeof(Number));
    initNumber(ans);
    initNumber(angleInRadians);
    if (n1->sign == MINUS)
        minus = 1;
    // this minus variable is created to remember sign of n1
    angleInRadians = modulus(n1, twoPI());
    // After modulus call gets finished sign of n1 is changed to PLUS inside modulus
    if (minus)
        angleInRadians->sign = MINUS;
    double angle = NumberToDouble(angleInRadians);
    double value = tanl(angle);
    ans = doubletoNumber(value);
    free(angleInRadians);
    return ans;
}
// this return value of e accurate upto 20 decimal places
Number *TheNumberE()
{
    Number *e = (Number *)malloc(sizeof(Number));
    initNumber(e);
    // value of e upto 20 decimal digits
    char value[] = "2.71828182845904523536";
    int i = 0;
    while (value[i] != '\0')
    {
        appendDigit(e, value[i]);
        i++;
    }
    e->dec = 20;
    return e;
}
// evaluates e^x
Number *exponent(Number *n1)
{
    return power(TheNumberE(), n1);
}
Number *Factorial(Number *n1)
{
    Number *ans = (Number *)malloc(sizeof(Number));
    initNumber(ans);
    insertAtBegining(ans, 1);
    Number *one = (Number *)malloc(sizeof(Number));
    initNumber(one);
    insertAtBegining(one, 1);
    if (isNumber0(n1))
    {
        return one;
    }
    while (!isNumber0(n1))
    {
        ans = multiply(ans, n1);
        n1 = sub(n1, one);
    }
    free(one);
    return ans;
}
Number *sqRoot(Number *n1)
{
    Number *ans = (Number *)malloc(sizeof(Number));
    initNumber(ans);
    double temp = NumberToDouble(n1);
    temp = sqrt(temp);
    ans = doubletoNumber(temp);
    return ans;
}

void setScale(Number *n1)
{
    if (n1->sign == PLUS && n1->dec == 0)
    {
        scale = NumberToint(n1);
    }
    printf("Scale is set to: ");
}
/*
int main()
{
    Number *n1, *n2, *n3;
    n1 = (Number *)malloc(sizeof(Number));
    n2 = (Number *)malloc(sizeof(Number));
    n3 = (Number *)malloc(sizeof(Number));
    initNumber(n1);
    initNumber(n2);
    initNumber(n3);
    // insertAtBegining(n1, 3);
    // appendDigit(n1, '2');
    // appendDigit(n1, '6');
    appendDigit(n1, '5');
    appendDigit(n1, '2');
    // appendDigit(n1, '5');
    // appendDigit(n1, '4');
    // n2->sign = MINUS;
    // n1->sign = MINUS;
    n2->dec = 2;
    // n2->dec = 4;
    // n2->sign = MINUS;
    // n1->sign = MINUS;
    // n1 = twoPI();

    appendDigit(n2, '6');
    appendDigit(n2, '3');
    appendDigit(n2, '5');
    // appendDigit(n2, '4');
    // appendDigit(n2, '5');
    // appendDigit(n2, '9');
    // appendDigit(n2, '9');
    // appendDigit(n2, '5');
    // appendDigit(n2, '4');
    // appendDigit(n1, '3');
    // appendDigit(n1, '8');
    // appendDigit(n2, '8');
    // appendDigit(n2, '9');
    // appendDigit(n2, '2');
    // appendDigit(n2, '3');
    // displayNumber(n1);

    // displayNumber(TheNumberE());
    // intToNumber(300, n1);
    displayNumber(n1);
    displayNumber(n2);
    // n3 = multiply(n1, n2);
    n3 = power(n2, n1);
    displayNumber(n3);
    // int n = NumberToint(n1);
    // printf("%d", n);
    // n = NumberToint(n2);
    // printf("%d", n);
    // int t = compareMagnitude(*n2, *n1);
    // printf("%d", t);
    // displayNumber(n3);
    // printf("%d", length(*n1));
    // displayNumber(n3);
    // n3 = add(n1, n2);
    // displayNumber(n3);
}
*/