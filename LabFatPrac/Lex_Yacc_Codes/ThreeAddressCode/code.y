%{
  #include<stdio.h>
  #include<string.h>
  #include<stdlib.h>
  void ThreeAddressCode();
  void triple();
  void qudraple();
  char AddToTable(char ,char, char);

  int currIdx=0;//count number of lines
  char currTemp = '1';//for t1,t2,t3.....
  struct incod
  {
    char opd1;
    char opd2;
    char opr;
  };
%}

%union
{
  char sym;
}

%token <sym> LETTER NUMBER
%type <sym> expr
%left '+' '-'
%left '*''/'
%%

statement: LETTER '=' expr ';' {AddToTable((char)$1,(char)$3,'=');}
| expr ';'
;

expr: 
 expr '+' expr {$$ = AddToTable((char)$1,(char)$3,'+');}
| expr '-' expr {$$ = AddToTable((char)$1,(char)$3,'-');}
| expr '*' expr {$$ = AddToTable((char)$1,(char)$3,'*');}
| expr '/' expr {$$ = AddToTable((char)$1,(char)$3,'/');}
| '(' expr ')' {$$ = (char)$2;}
| NUMBER {$$ = (char)$1;}
| LETTER {$$ = (char)$1;}
|'-' expr {$$ = AddToTable((char)$2,(char)'\t','-');}
;

%%

yyerror(char *s)
{
 printf("%s",s);
 exit(0);
}

struct incod code[20];

char AddToTable(char opd1,char opd2,char opr)
{
 code[currIdx].opd1=opd1;
 code[currIdx].opd2=opd2;
 code[currIdx].opr=opr;
 currIdx++;
 return currTemp++;
}

void ThreeAddressCode()
{

  for(int i = 0; i < 20; i++)
  {
    printf("%c %c %c\n", code[i].opd1, code[i].opd2, code[i].opr);
  }
 int cnt = 0;
 char currTemp = '1';
 printf("\n\n\t THREE ADDRESS CODE\n\n");
 while(cnt<currIdx)
 {
  if(code[cnt].opr != '=')
    printf("t%c : = \t",currTemp++);

  if(isalpha(code[cnt].opd1))
    printf(" %c\t",code[cnt].opd1);
  else if(code[cnt].opd1 >='1' && code[cnt].opd1 <='9')
    printf("t%c\t",code[cnt].opd1);

  printf(" %c\t",code[cnt].opr);

  if(isalpha(code[cnt].opd2))
    printf(" %c\n",code[cnt].opd2);
  else if(code[cnt].opd2 >='1' && code[cnt].opd2 <='9')
    printf("t%c\n",code[cnt].opd2);
  cnt++;
 }
}

void quadraple()
{
 int cnt = 0;
 char currTemp = '1';
 printf("\n\n\t QUADRAPLE CODE\n\n");
 while(cnt<currIdx)
 {
  printf(" %c\t",code[cnt].opr);
  if(code[cnt].opr == '=')
  {
   if(isalpha(code[cnt].opd2))
    printf(" %c\t \t",code[cnt].opd2);
   else if(code[cnt].opd2 >='1' && code[cnt].opd2 <='9')
    printf("t%c\t \t",code[cnt].opd2);
    printf(" %c\n",code[cnt].opd1);
   cnt++;
   continue;
  }
  if(isalpha(code[cnt].opd1))
    printf(" %c\t",code[cnt].opd1);
  else if(code[cnt].opd1 >='1' && code[cnt].opd1 <='9')
    printf("t%c\t",code[cnt].opd1);

  if(isalpha(code[cnt].opd2))
    printf(" %c\t",code[cnt].opd2);
  else if(code[cnt].opd2 >='1' && code[cnt].opd2 <='9')
    printf("t%c\t",code[cnt].opd2);
  else  printf("  %c",code[cnt].opd2);

  printf("t%c\n",currTemp++);
  cnt++;
 }
}

void triple()
{
 int cnt=0;
 char currTemp='1';
 printf("\n\n\t TRIPLE CODE\n\n");
  while(cnt<currIdx)
 {
  printf("(%c) \t",currTemp);
  printf(" %c\t",code[cnt].opr);
  if(code[cnt].opr == '=')
  {
   if(isalpha(code[cnt].opd2))
    printf(" %c \t \t",code[cnt].opd2);
   else if(code[cnt].opd2 >='1' && code[cnt].opd2 <='9')
    printf("(%c)\n",code[cnt].opd2);
   cnt++;
   currTemp++;
   continue;
  }
  if(isalpha(code[cnt].opd1))
    printf(" %c \t",code[cnt].opd1);
  else if(code[cnt].opd1 >='1' && code[cnt].opd1 <='9')
    printf("(%c)\t",code[cnt].opd1);

  if(isalpha(code[cnt].opd2))
    printf(" %c \n",code[cnt].opd2);
  else if(code[cnt].opd2 >='1' && code[cnt].opd2 <='9')
    printf("(%c)\n",code[cnt].opd2);
  cnt++;
  currTemp++;
 }
}

main()
{
  printf("\n Enter the Expression : ");
  yyparse();
  ThreeAddressCode();
  quadraple();
  triple();
}