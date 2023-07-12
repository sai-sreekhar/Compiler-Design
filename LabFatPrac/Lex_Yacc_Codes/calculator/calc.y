%{	
	#include <stdio.h>
	#include <math.h>
	int flag = 0;
%}


%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%right '^'
%left '(' ')'

%%
	start: E {printf("Result = %d\n",$$);return 0;};
	E: E'+'E{$$=$1+$3;}
	|E'-'E{$$=$1-$3;}
	|E'*'E{$$=$1*$3;}
	|E'/'E{$$=$1/$3;}
	|E'%'E{$$=$1%$3;}
	|E'^'E{$$=pow($1,$3);}
	|'('E')'{$$=$2;}
	|NUMBER{$$=$1;}
	;
%%

int main()
{
	printf("Enter the expression: ");
	yyparse();
	
}

yyerror(char *s)
{
	printf("%s\n",s);
}