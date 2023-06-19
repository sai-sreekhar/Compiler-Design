#include <stdio.h>
#include <ctype.h>
#include <string.h>
char key[5][20] = {"void", "if", "while", "int", "main"};
int main()
{
   int i, n = 1;
   int label;
   char a[20];
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
         printf("\n\t%d\t%c\t a Special Symbol", n++, str);
         break;
      case '}':
         printf("\n\t%d\t%c\t a Special Symbol\n", n++, str);
         break;
      case '(':
         printf("\n\t%d\t%c\t a Special Symbol", n++, str);
         break;
      case ')':
         printf("\n\t%d\t%c\t a Special Symbol", n++, str);
         break;
      case ';':
         printf("\n\t%d\t%c\t a Special Symbol", n++, str);
         break;
      case '*':
         printf("\n\t%d\t%c\t a Multiplication Operator", n++, str);
         break;
      case '=':
         printf("\n\t%d\t%c\t a assignment operator", n++, str);
         break;
      case '+':
         printf("\n\t%d\t%c\t a addition operator", n++, str);
         break;

      case '#':
         printf("\n\t%d\t%c\t a pre-processor", n++, str);
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
            for (i = 0; i < 5; i++)
            {
               if (strcmp(a, key[i]) == 0)
               {
                  printf("\n\t%d\t%s\t a keyword", n++, a);
                  label = 1;
                  break;
               }
            }
            if (label == 0)
            {
               printf("\n\t%d\t%s\t an identifier", n++, a);
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
            printf("\n\t%d\t%s\t a constant", n++, a);
         }
      }
   }
   fclose(fp);
}
