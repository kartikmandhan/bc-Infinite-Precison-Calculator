#include <stdio.h>
#include "stack.h"
#include "infix.h"
#include <stdio.h>
#include <ctype.h>

enum state
{
    SPACE,
    NUM,
    OP,
    DECIMAL,
    FINISH,
    ERROR
};
token getToken(char *expr, int reset)
{
    static int i = 0;
    static enum state currstate = SPACE;
    static enum state nextstate;
    char currentChar;
    token t;
    Number *new_number = (Number *)malloc(sizeof(Number));
    initNumber(new_number);
    while (1)
    {
        currentChar = expr[i];
        switch (currstate)
        {
        case SPACE:
            switch (currentChar)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                t.type = OPERAND;
                t.num = new_number;
                nextstate = NUM;
                currstate = nextstate;
                // i++;

                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '(':
            case ')':

                nextstate = OP;
                currstate = nextstate;
                i++;

                break;
            case ' ':
                nextstate = SPACE;
                currstate = nextstate;
                i++;

                break;
            case '\0':

                nextstate = FINISH;
                currstate = nextstate;
                break;
            case '.':

                nextstate = DECIMAL;
                currstate = nextstate;
                i++;

                break;
            default:
                nextstate = ERROR;
                currstate = nextstate;
                break;
            }
            break;
        case NUM:
            switch (currentChar)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                // t.type = OPERAND;
                // t.num = new_number;
                appendDigit(new_number, currentChar);
                nextstate = NUM;
                currstate = nextstate;
                i++;

                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '(':
            case ')':
                t.type = OPERAND;
                t.num = new_number;
                nextstate = OP;
                currstate = nextstate;
                i++;
                return t;
                break;
            case ' ':
                t.type = OPERAND;
                t.num = new_number;
                nextstate = SPACE;
                currstate = nextstate;
                i++;
                return t;
                break;
            case '\0':
                t.type = OPERAND;
                t.num = new_number;
                nextstate = FINISH;
                currstate = nextstate;
                return t;

                break;
            case '.':

                nextstate = DECIMAL;
                currstate = nextstate;
                i++;

                break;
            default:
                t.type = OPERAND;
                t.num = new_number;
                nextstate = ERROR;
                currstate = nextstate;

                return t;
                break;
            }
            break;
        case OP:
            switch (currentChar)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                t.type = OPERATOR;
                t.op = expr[i - 1];
                nextstate = NUM;
                currstate = nextstate;
                // i++;
                return t;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '(':
            case ')':
                t.type = OPERATOR;
                t.op = expr[i - 1];
                nextstate = OP;
                currstate = nextstate;
                i++;
                return t;
                break;
            case ' ':
                t.type = OPERATOR;
                t.op = expr[i - 1];
                nextstate = SPACE;
                currstate = nextstate;
                i++;
                return t;
                break;
            case '\0':
                t.type = OPERATOR;
                t.op = expr[i - 1];
                nextstate = FINISH;
                currstate = nextstate;

                return t;
                break;
            case '.':
                t.type = OPERATOR;
                t.op = expr[i - 1];
                nextstate = DECIMAL;
                currstate = nextstate;
                i++;
                return t;

                break;
            default:
                t.type = OPERATOR;
                t.op = expr[i - 1];
                nextstate = ERROR;
                currstate = nextstate;
                return t;
                break;
            }
            break;
        case DECIMAL:
            switch (currentChar)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                appendDigit(new_number, currentChar);
                new_number->dec++;
                nextstate = DECIMAL;
                currstate = nextstate;
                i++;

                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '(':
            case ')':
                t.type = OPERAND;
                t.num = new_number;
                nextstate = OP;
                currstate = nextstate;
                i++;
                return t;
                break;
            case ' ':
                t.type = OPERAND;
                t.num = new_number;
                nextstate = SPACE;
                currstate = nextstate;
                i++;
                return t;
                break;
            case '\0':
                t.type = OPERAND;
                t.num = new_number;
                nextstate = FINISH;
                currstate = nextstate;

                return t;
                break;
            case '.':
                // this is my choice

                nextstate = ERROR;
                currstate = nextstate;
                i++;
                return t;
                break;
            default:
                t.type = OPERAND;
                t.num = new_number;
                nextstate = ERROR;
                currstate = nextstate;
                i++;
                return t;
                break;
            }
            break;

        case FINISH:
            t.type = END;
            return t;
            break;
        case ERROR:
            t.type = ERR;
            return t;
            break;
        default:
            break;
        }
    }
}

int precedence(char op)
{
    switch (op)
    {
    case ')':
        return 3;
        break;
    case '+':
    case '-':
        return 4;
        break;
    case '*':
    case '/':
        return 5;
        break;
    case '%':
        return 6;
        break;
    case '(':
        return 7;
        break;

    default:
        // this case will never occur since our getnext function will handle any error in the string
        return 100;
        break;
    }
}
/*
int infix(char *expression)
{
    char line[1024], ch, digit, prev_op, curr_op;
    int i = 0, a, b, z, OBcount = 0, CBcount = 0;
    istack operandStack;
    cstack operatorStack;
    cinit(&operatorStack);
    init(&operandStack);

    while (line[i] != '\0')
    {
        ch = line[i];
        if (isdigit(ch))
        {
            digit = ch - '0';
            push(&operandStack, digit);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == ')' || ch == '(')
        {
            curr_op = ch;
            if (curr_op == '(')
                OBcount++;
            if (curr_op == ')')
                CBcount++;
            if (CBcount > OBcount)
            {
                printf("error\n");
                exit(0);
            }
            if (!cisEmpty(operatorStack))
            {
                prev_op = ctop(operatorStack);
                // for starting situation we dont hav prev_op,hence if stack is empty then dont do all this
                while (precedence(prev_op) >= precedence(curr_op))
                {
                    prev_op = cpop(&operatorStack);
                    if (!isEmpty(operandStack))
                    {
                        a = pop(&operandStack);
                    }
                    else
                    {
                        cpush(&operatorStack, prev_op);
                        break;
                    }
                    if (!isEmpty(operandStack))
                    {
                        b = pop(&operandStack);
                    }
                    else
                    {
                        cpush(&operatorStack, prev_op);
                        push(&operandStack, a);
                        break;
                    }
                    if ((prev_op == '/' || prev_op == '%') && a == 0)
                    {
                        fprintf(stderr, "Mathematical error\n");
                        printf("error\n");
                        exit(0);
                    }
                    switch (prev_op)
                    {
                    case '+':
                        z = b + a;
                        // z = add(a, b);
                        push(&operandStack, z);
                        break;
                    case '-':
                        z = b - a;
                        // z = sub(b, a);
                        push(&operandStack, z);
                        break;
                    case '*':
                        z = b * a;
                        push(&operandStack, z);
                        // z = mult(b, a);
                        break;
                    case '/':
                        z = b / a;
                        push(&operandStack, z);
                        // z = division(b, a);
                        break;
                    case '%':
                        z = b % a;
                        push(&operandStack, z);
                        // z = modulus(b, a);
                        break;
                    case '(':
                        cpush(&operatorStack, prev_op);
                        push(&operandStack, b);
                        push(&operandStack, a);
                    default:
                        printf("error\n");
                        exit(0);
                        break;
                    }
                    if (prev_op == '(')
                        break;
                    if (!cisEmpty(operatorStack))
                        prev_op = ctop(operatorStack);
                    else
                        break;
                }
            }
            cpush(&operatorStack, curr_op);
            if (curr_op == ')')
            {
                // pop opening and closing brackets from stack
                cpop(&operatorStack);
                CBcount--;
                cpop(&operatorStack);
                OBcount--;
            }
        }
        i++;
    }
    if (line[i] == '\0')
    {

        if (CBcount == OBcount)
        {
            while (!cisEmpty(operatorStack))
            {
                if (!isEmpty(operandStack))
                {
                    a = pop(&operandStack);
                }
                else
                {
                    fprintf(stderr, "less operands");
                }
                if (!isEmpty(operandStack))
                {
                    b = pop(&operandStack);
                }
                else
                {
                    fprintf(stderr, "less operands");
                }
                prev_op = cpop(&operatorStack);
                if ((prev_op == '/' || prev_op == '%') && a == 0)
                {
                    fprintf(stderr, "Mathematical error\n");
                    printf("error\n");
                    exit(0);
                }
                switch (prev_op)
                {
                case '+':
                    z = b + a;
                    // z = add(a, b);
                    push(&operandStack, z);
                    break;
                case '-':
                    z = b - a;
                    // z = sub(b, a);
                    push(&operandStack, z);
                    break;
                case '*':
                    z = b * a;
                    push(&operandStack, z);
                    // z = mult(b, a);
                    break;
                case '/':
                    z = b / a;
                    push(&operandStack, z);
                    // z = division(b, a);
                    break;
                case '%':
                    z = b % a;
                    push(&operandStack, z);
                    // z = modulus(b, a);
                    break;

                default:
                    printf("error\n");
                    exit(0);
                    break;
                }
            }
        }
        else
        {
            fprintf(stderr, "Error in Expression\n");
            //return INT_MIN;
            printf("error\n");
            exit(0);
        }
        if (!isEmpty(operandStack))
        {
            z = pop(&operandStack);
            if (isEmpty(operandStack))
            {

                printf("Result:%d\n", z);
            }
            else
            {
                fprintf(stderr, "Less Operators\n");
                printf("error\n");
                exit(0);
            }
        }
        else
        {
            fprintf(stderr, "Less Operands\n");

            printf("error\n");
            exit(0);
        }
    }

    return 0;
}
*/
int main()
{
    token t;
    char line[1024] = ".2323";
    // readline(line, 1024);
    scanf("%[^\n]", line);
    while (t.type != END && t.type != ERR)
    {
        t = getToken(line, 0);

        printf("%d ", t.type);
        if (t.type == OPERATOR)
            printf("%c", t.op);
        else if (t.type == OPERAND)
            displayNumber(t.num);
        else if (t.type == ERR)
        {
            printf("error");
        }
        printf("\n");
    }
}