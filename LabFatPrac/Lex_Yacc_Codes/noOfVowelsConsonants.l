%{
    int v = 0;
    int c = 0;
%}

%%
[a|e|i|o|u] {v++;}
[b|c|d|f|g|h|j|k|l|m|n|p|q|r|s|t|v|w|x|y|z] {c++;}
. {return yytext[0];}
\n {return 0;}
%%

int yywrap()
{
    return 1;
}

int main()
{
    yylex();
    printf("Vowels: %d\nConsonants: %d\n", v, c);
    return 0;
}