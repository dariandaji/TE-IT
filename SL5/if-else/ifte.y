%{
#include "lex.yy.c"
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char st[100][10];
int top=0;
char subscript[2]="0";
char temp[2]="t";

int label[20];
int lnum=0;
int ltop=0;
%}

%token ID NUM IF THEN ELSE
%right '='
%left '+' '-'
%left '*' '/'
%left UMINUS
%%

S : IF '(' E ')' {cond();} THEN E ';' {trueblk();} ELSE E ';' {falseblk();}
  ;
E : V '='{push();} E{codegen_assign();}
  | E '+'{push();} E{codegen();}
  | E '-'{push();} E{codegen();}
  | E '*'{push();} E{codegen();}
  | E '/'{push();} E{codegen();}
  | '(' E ')'
  | '-'{push();} E{codegen_umin();} %prec UMINUS
  | V
  | NUM{push();}
  ;
V : ID {push();}
  ;
%%


main()
{
	printf("Enter the expression : ");
	yyparse();
}

push()
{
	strcpy(st[++top],yytext);
}

codegen()
{
	strcpy(temp,"t");
	strcat(temp,subscript);
	printf("%s = %s %s %s\n",temp,st[top-2],st[top-1],st[top]);
	top-=2;
	strcpy(st[top],temp);
	subscript[0]++;
}

codegen_umin()
{
	strcpy(temp,"t");
	strcat(temp,subscript);
	printf("%s = -%s\n",temp,st[top]);
	top--;
	strcpy(st[top],temp);
	subscript[0]++;
}

codegen_assign()
{
	printf("%s = %s\n",st[top-2],st[top]);
	top-=2;
}

cond()
{
	lnum++;
	strcpy(temp,"t");
	strcat(temp,subscript);
	printf("%s = not %s\n",temp,st[top]);
	printf("if %s goto L%d\n",temp,lnum);
	subscript[0]++;
	label[++ltop]=lnum;
}

trueblk()
{
	int x;
	lnum++;
	x=label[ltop--];
	printf("goto L%d\n",lnum);
	printf("L%d: \n",x);
	label[++ltop]=lnum;
}

falseblk()
{
	int y;
	y=label[ltop--];
	printf("L%d: \n",y);
}
