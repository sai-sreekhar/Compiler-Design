%{
   #include<stdio.h>
   int valid = 1;   
%}

%token num id op factorial
%%
start : id '=' S ';'
S : id A       
   | num A       
   | '-' num A   
   | '(' S ')' A 
   ;
A : op S        
   | '-' S   
   | factorial A
   | 
   ;
%%

int yyerror()
{
   valid=0;
   printf("\nInvalid expression!\n");
   return 0;

}

int main()
{

   printf("\nEnter the expression:\n");
   yyparse();
   if(valid)
   {
      printf("\nValid expression!\n");
   }

}
