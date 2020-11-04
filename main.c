#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
int main(int argc, char *argv[])
{
    printf("This project is inspired from the bc command line calculator in Linux\n");
    printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
    if (argc == 2 && !strcmp(argv[1], "-h"))
    {
        printf("Usage: project [option]\n");
        printf("\t-h\t--help\t\tprint this help and exit\n");
        printf("\t-v\t--version\tprints information about version of this software\n");
        printf("\t-i\t--integers\tprints answers in integer format only\n");
        printf(" expr + expr\n");
        printf("\tThe result of the expression is the sum of the two expressions.\n");
        printf(" expr - expr\n");
        printf("\tThe result of the expression is the difference of the two expressions.\n\n");
        printf(" expr * expr\n");
        printf("\tThe result of the expression is the sum of the two expressions.\n\n");
        printf(" expr / expr\n");
        printf("\tThe result of the expression is the quotient of the two  expressions.\n\n");
        printf(" expr %% expr\n");
        printf("\tThe result of the expression is the \"remainder\n\n");
        printf(" expr ^ expr\n");
        printf("\tThe result of the expression is the value of the first raised to the second\n\n");
        exit(0);
    }
    if (argc > 2)
    {
        printf("Usage: project [option]\n");
    }

    char line[LINE_LEN];
    Number *result;
    printf(">>> ");
    while (readline(line, LINE_LEN))
    {
        insert0AtStartAndAfterBrac(line);
        // printf("%s", line);
        result = infix(line);
        if (result != NULL)
            displayNumber(result);
        else
            printf("Incorrect expression\n");
        printf("\n>>> ");
    }
}
// 2^3+5%2/2*4^3
// Sequence of executable files: 1.try  2.pro 3.tryPower