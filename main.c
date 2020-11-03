#include <stdio.h>
#include <string.h>
// function reads and returns length of the string that it read.
#include "infix.h"

#define LINE_LEN 1024
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
void insert0AtStartAndAfterBrac(char *line)
{
    // bracket related code
    // 	(    +8   - 6) =>
    // (    0+8   - 6)
    // (          -8 + 8) =>
    // (          0-8 + 8)
    int i = 0, j = 0, temp;
    if ((line[0] == '-') || (line[0] == '+'))
    {
        temp = strlen(line);
        while (temp >= 0)
        {
            // moving each character 1 place forward
            line[temp + 1] = line[temp];
            temp--;
        }
        line[0] = '0';
    }
    for (i = 0; i < strlen(line); i++)
    {
        if (line[i] == '(')
        {
            j = 1;

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
    char line[LINE_LEN];
    Number *result;
    while (readline(line, LINE_LEN))
    {
        insert0AtStartAndAfterBrac(line);
        // printf("%s", line);
        result = infix(line);
        if (result != NULL)
            displayNumber(result);
        else
            printf("Incorrect expression\n");
    }
}
// 2^3+5%2/2*4^3
// Sequence of executable files: 1.try  2.pro 3.tryPower