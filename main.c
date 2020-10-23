#include <stdio.h>
#include <string.h>
// function reads and returns length of the string that it read.
#include "infix.h"
token getToken(char *expr, int reset);
int readline(char *line, int len)
{
    int i;
    char ch;
    i = 0;
    while (i < len - 1)
    {
        ch = getchar();
        if (ch == '\n')
        {
            line[i] = '\0';
            return i;
        }
        else
            line[i++] = ch;
    }
    line[len - 1] = '\0';
    return len - 1;
}
void insertZeroAfterBrac(char *line)
{
    // bracket related code
    // 	(    +8   - 6)
    // (    0+8   - 6)
    // (          -8 + 8)
    // (          0-8 + 8)
    int i;
    for (i = 0; i < strlen(line); i++)
    {
        if (line[i] == '(')
        {
            int j = 1;

            while (1)
            {
                if (line[i + j] == ' ')
                {
                    j++;
                }
                else
                {
                    break;
                }
            }
            if ((line[i + j] == '-') || (line[i + j] == '+'))
            {
                int temp = strlen(line);
                while (temp >= i + j)
                {
                    line[temp + 1] = line[temp];
                    temp--;
                }
                line[i + j] = '0';
            }
        }
    }
}
int main()
{
    printf("This project is inspired from the bc command line calculator in Linux\n");
    printf("It is free to use software with no WARANTY\n");
    char line[1024];
    readline(line, 1024);
    token t;
    // while (t.type != END)
    // {
    t = getToken(line, 0);

    printf("%d ", t.type);
    if (t.type == OPERATOR)
        printf("%c", t.op);
    else if (t.type == OPERAND)
        displayNumber(t.num);

    printf("\n");
    // }
}