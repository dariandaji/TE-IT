#include<stdio.h>

int a[25];
int cnt=0;

int main()
{

	int n,i,min,max;
	printf("enter no.of element in array");
	scanf("%d",&n);
	printf("enter element of an array");
	for(i=0;i<n;i++)
	{
	scanf("%d",&a[i]);	
        }

	minmax(0,n-1,&max,&min);
	printf("Max is %d & Min is %d\n",max,min);
	printf("frequency is %d\n",cnt);


}



int minmax(int i,int j,int *max,int *min)
{

	int mid,max1,min1;
	if(i==j)
	{
	cnt++;
	*max=*min=a[i];
	}
	else if(i==j-1)
	{
	cnt++;
	if(a[i]<a[j])
	{
	*max=a[j];
	*min=a[i];
	}
	else
	{
	*max=a[i];
	*min=a[j];
	}
	}

		else
		{
	
			mid=(i+j)/2;
			minmax(i,mid,max,min);
			minmax(mid+1,j,&max1,&min1);
			
			if(*max<max1)
			{
			cnt++;
			*max=max1;
			}
			if(*min>min1)
			{
			cnt++;
			*min=min1;
			}
		
		}
}



/*
itexam@c05l0326:~/Desktop$ gcc daa1.c
itexam@c05l0326:~/Desktop$ ./a.out
enter no.of element in array5
enter element of an array10
2
6
7
9
Max is 10 & Min is 2
frequency is 6
itexam@c05l0326:~/Desktop$ gcc daa1.c
itexam@c05l0326:~/Desktop$ ./a.out
enter no.of element in array5
enter element of an array10
2
5
8
9
Max is 10 & Min is 2
frequency is 3
itexam@c05l0326:~/Desktop$ gcc daa1.c
itexam@c05l0326:~/Desktop$ ./a.out
enter no.of element in array2
enter element of an array10
3
Max is 10 & Min is 3
frequency is 1
itexam@c05l0326:~/Desktop$ 7
7: command not found
itexam@c05l0326:~/Desktop$ ./a.out
enter no.of element in array1
enter element of an array10
Max is 10 & Min is 10
frequency is 1
itexam@c05l0326:~/Desktop$ 


*/













