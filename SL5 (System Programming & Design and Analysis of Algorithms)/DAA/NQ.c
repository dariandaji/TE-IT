#include<stdio.h>
#include<stdlib.h>
#include<math.h>

static int cnt=0;
int *x;
void NQueen(int,int);
int place(int,int);
void print(int);
 
int main()
{
	int n;
	printf("Enter the value of 'n': ");
	scanf("%d",&n);
	x=(int*)malloc(sizeof(int)*n);
	NQueen(1,n);
	return 0;
} 

void NQueen(int r, int n)
{
	int c;
	for(c=1;c<=n;c++)
	{
		if(place(r,c))
		{
			x[r]=c;
			if(r==n)
				print(n);
			else
				NQueen(r+1,n);
		}
	}
}

int place(int r, int c)
{
	int i;
	for(i=1;i<=r-1;i++)
	{
		if(x[i]==c || abs(x[i]-c)==abs(i-r))
			return 0;
	}
	return 1;
}

void print(int n)
{
	printf("Solution %d->\n",++cnt);
	int i,j;
	for(i=0;i<=n;i++)
		printf("%d\t",i);
	
	for(i=1;i<=n;i++)
	{
		printf("\n%d",i);
		for(j=1;j<=n;j++)
		{
			if(x[i]==j) printf("\tQ");
			else printf("\t-");
		}
	}
	printf("\n\n");
}
