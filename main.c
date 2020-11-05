#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// function reads and returns length of the string that it read.
#include "infix.h"

#define LINE_LEN 1024
int scale;
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
        printf("\tThe result of the expression is the difference of the two expressions.\n");
        printf(" expr * expr\n");
        printf("\tThe result of the expression is the sum of the two expressions.\n");
        printf(" expr / expr\n");
        printf("\tThe result of the expression is the quotient of the two  expressions.\n");
        printf(" expr %% expr\n");
        printf("\tThe result of the expression is the \"remainder\n");
        printf(" expr ^ expr\n");
        printf("\tThe result of the expression is the value of the first raised to the second, provided second number should be an integer \n");
        printf(" S(x)\n");
        printf("\tThe sine of x, x is in radians.\n");
        printf(" C(x)\n");
        printf("\tThe cosine of x, x is in radians.\n");
        printf(" T(x)\n");
        printf("\tThe tangent of x, x is in radians.\n");
        printf(" e(x)\n");
        printf("\tThe result of the expression is e^x, provided x should be an integer \n");
        exit(0);
    }
    if (argc > 2)
    {
        printf("Usage: project [option]\n");
    }
    printf("Enter the scale for calculations:\n");
    scanf("%d", &scale);
    getchar();
    char line[LINE_LEN];
    FILE *fp = fopen("history.txt", "a");
    Number *result;
    printf(">>> ");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fp, "%02d-%02d-%d %02d:%02d:%02d\n\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(fp, "Scale: %d\n\n", scale);
    fprintf(fp, ">>> ");
    while (readline(line, LINE_LEN))
    {

        insert0AtStartAndAfterBrac(line);
        fprintf(fp, "%s\n", line);
        result = infix(line);
        if (result != NULL)
        {
            displayNumber(result);
            writeNumberInfile(result, fp);
        }
        else
        {
            printf("Incorrect expression\n");
            fprintf(fp, "Incorrect expression\n");
        }
        printf("\n>>> ");
        fprintf(fp, "\n>>> ");
    }
    fprintf(fp, "--------------------------------------------------------------------------------------------------------------\n");
    fclose(fp);
}
// 2^3+5%2/2*4^3
// Sequence of executable files: 1.try  2.pro 3.tryPower