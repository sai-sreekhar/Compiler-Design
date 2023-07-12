#include <stdio.h>
#include <ctype.h>
#include <string.h>

char key[5][20] = {"void", "if", "while", "int", "main"};

int main()
{
    FILE *fp;
    int n = 1;
    fp = fopen("t.c", "w");
    printf("\n Enter a valid data:");
    char ch;
    while ((ch = getchar()) != 'z')
    {
        fputc(ch, fp);
    }
    fclose(fp);
    fp = fopen("t.c", "r");
    printf("\t\tTOKEN Seperation\n");
    printf("\n TokenNo  TokenName   Tokentype\n");

    while ((ch = fgetc(fp)) != EOF)
    {
        switch (ch)
        {
        case '{':
            printf("\n\t%d\t%c\t a Special Symbol", n++, ch);
            break;
        case '}':
            printf("\n\t%d\t%c\t a Special Symbol\n", n++, ch);
            break;
        case '(':
            printf("\n\t%d\t%c\t a Special Symbol", n++, ch);
            break;
        case ')':
            printf("\n\t%d\t%c\t a Special Symbol", n++, ch);
            break;
        case ';':
            printf("\n\t%d\t%c\t a Special Symbol", n++, ch);
            break;
        case '*':
            printf("\n\t%d\t%c\t a Multiplication Operator", n++, ch);
            break;
        case '=':
            printf("\n\t%d\t%c\t a assignment operator", n++, ch);
            break;
        case '+':
            printf("\n\t%d\t%c\t a addition operator", n++, ch);
            break;

        case '#':
            printf("\n\t%d\t%c\t a pre-processor", n++, ch);
            break;
        default:
            char arr[20];
            int i = 0;
            if (isalpha(ch))
            {
                do
                {
                    arr[i] = ch;
                    i++;
                    ch = fgetc(fp);
                } while (isalnum(ch));
                arr[i] = "\0";
                fseek(fp, -1, 1);
                int flag = 0;
                for (int j = 0; j < 5; j++)
                {
                    if (strcmp(arr, key[j]) == 0)
                    {
                        printf("\n\t%d\t%s\t a keyword", n++, arr);
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    printf("\n\t%d\t%s\t an identifier", n++, arr);
                }
            }
            else if (isdigit(ch))
            {
                do
                {
                    arr[i] = ch;
                    i++;
                    ch = fgetc(fp);
                } while (isdigit(ch));
                arr[i] = "\0";
                fseek(fp, -1, 1);
                printf("\n\t%d\t%s\t a number", n++, arr);
            }
        }
    }
    fclose(fp);
    return 0;
}