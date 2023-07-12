#include <stdio.h>
#include <ctype.h>
#include <string.h>
char key[6][20] = {"void", "if", "while", "int", "main", "printf"};
char isDisplayed[6][20];
int k = -1;
int main()
{
    int i, n = 1;
    int label;
    char a[20];
    int pvsKeyWordIdx;
    char str;
    FILE *fp;

    fp = fopen("t.c", "w");
    printf("\n Enter a valid data:");
    while ((str = getchar()) != 'z')
    {
        fputc(str, fp);
    }
    fclose(fp);
    fp = fopen("t.c", "r");
    printf("\t\tTOKEN Seperation\n");
    printf("\n TokenNo  TokenName   Tokentype\n");
    while ((str = fgetc(fp)) != EOF)
    {
        i = 0;
        label = 0;
        switch (str)
        {
        case '{':
            break;
        case '}':
            break;
        case '(':
            break;
        case ')':
            break;
        case ';':
            break;
        case '*':
            break;
        case '=':
            break;
        case '+':
            break;
        case '#':
            break;
        default:
            if (isalpha(str))
            {
                do
                {
                    a[i] = str;
                    i++;
                    str = fgetc(fp);
                } while (isalpha(str) || isalnum(str));
                a[i] = '\0';
                fseek(fp, -1, 1);
                for (i = 0; i < 6; i++)
                {
                    if (strcmp(a, key[i]) == 0)
                    {
                        label = 1;
                        pvsKeyWordIdx = i;
                        break;
                    }
                }
                if (k == -1)
                {
                    k++;
                    strcpy(isDisplayed[k], a);
                }
                else
                {
                    for (int i = 0; i <= k; i++)
                    {
                        if (strcmp(a, isDisplayed[i]) == 0)
                        {
                            label = 1;
                            break;
                        }
                    }

                    if (label == 0)
                    {
                        printf("\n%s\t%s\t%d\t%d", a, key[pvsKeyWordIdx], 4, 2024);
                        k++;
                        strcpy(isDisplayed[k], a);
                    }
                }
            }
            else if (isdigit(str))
            {
                do
                {
                    a[i] = str;
                    i++;
                    str = fgetc(fp);
                } while (isdigit(str));
                a[i] = '\0';
                fseek(fp, -1, 1);
            }
        }
    }
    fclose(fp);
}
