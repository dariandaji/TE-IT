%token ID NUM WHILE
%right '='
%left '+' '-'
%left '*' '/'
%left UMINUS
%%

S : WHILE{while_kw();} '(' E ')'{cond();} E ';'{trueblk();}
  ;
E :V '='{push();} E{codegen_assign();}
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

#include "lex.yy.c"
#include<ctype.h>
char st[100][10];
int top=0;
char subscript[2]="0";
char temp[2]="t";

int lnum=1;
int start=1;

main()
 {
 printf("Enter the expression : ");
 yyparse();
 }



push()		//store the tokens as they come
 {
  strcpy(st[++top],yytext);
 }

codegen()
 {
 strcpy(temp,"t");			//to create a variable like t0,t1 etc.
 strcat(temp,subscript);
  printf("%s = %s %s %s\n",temp,st[top-2],st[top-1],st[top]);
  top-=2;					//remove 2 top tokens
 strcpy(st[top],temp);		//current top is overwritten by the subscript
 			//i.e. we are making k+8 as t0 and then storing t0 in the stack
 subscript[0]++;			//increase the subscript value of t like t0,t1
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



while_kw()		//to print the label corresponding to the while looping like L1:
{
printf("L%d: \n",lnum++);
}


cond()		
{
 strcpy(temp,"t");
 strcat(temp,subscript);	//assigning variable to a condition like t0 = k+8
 printf("%s = not %s\n",temp,st[top]);
 printf("if %s goto L%d\n",temp,lnum);
 subscript[0]++;
 }

trueblk()		//if condition is true then enter the loop
{
printf("goto L%d \n",start);
printf("L%d: \n",lnum);
}
