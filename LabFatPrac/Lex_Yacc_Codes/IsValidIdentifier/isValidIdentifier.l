%{
    #include "y.tab.h"
%}

%%
for|if|return|scanf|printf|int|double|float|while return key;
[a-zA-Z_][a-zA-Z_0-9]* return id;
.                      return yytext[0];
\n                     return 0;
%%

int yywrap()
{
    return 1;
}
