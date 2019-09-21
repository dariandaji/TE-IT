#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
char input[10];
int i,error;
void E();
void T();
void Ed();
void Td();
void F();

int main()
{
	i=error=0;
	printf("\nEnter an arithmetic expression: ");
	gets(input);
//	fgets(input,50,stdin);
	E();
	if(strlen(input)==i && error==0)
		printf("\nExpression accepted.\n");
	else printf("\nString rejected.\n");
}

void E()
{
	T();
	Ed();
}

void Ed()
{
	if(input[i]=='+')
	{
		i++;
		T();
		Ed();
	}
}

void T()
{
	F();
	Td();
}

void Td()
{
	if(input[i]=='*')
	{
		i++;
		F();
		Td();
	}
}

void F()
{
	if(isalnum(input[i]))
		i++;
	else if(input[i]=='(')
	{
		i++;
		E();
		if(input[i]==')')
			i++;
			
		else error=1;
	}
	else error=1;
}
	
