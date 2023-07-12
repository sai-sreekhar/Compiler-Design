%{
#include <ctype.h>
%}

%%
[a-z]       { printf("%c", toupper(yytext[0])); }
.           { printf("%s", yytext); }
%%

int main(void) {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}