%{
   #include<stdio.h>
   #include<stdbool.h>
   bool isValid = true;  
   bool isKeyFound = false; 
%}

%token id key
%%
S: key {isKeyFound = true;} | id
%%

int yyerror()
{
   isValid = false;
   return 0;
}

int main()
{

   printf("\nEnter the identifier:\n");
   yyparse();
   if(isKeyFound == true)
   {
      printf("\nInValid identifier!\n");
      return 0;
   }

   if(isValid == false)
   {
      printf("\nInValid identifier!\n");
   }
   else
   {
      printf("\nValid Identifier!\n");
   }

}
