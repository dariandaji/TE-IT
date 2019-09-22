#include<stdio.h>
#include<unistd.h>

void insert(int a[50],int n)
{
	int i,j,temp;
	for(i=1;i<=n-1;i++)
	{
		temp=a[i];
		j=i-1;
		while((j>=0) && (a[j]>temp))
		{
			a[j+1]=a[j];
			j=j-1;
		}
		a[j+1]=temp;
	}
	for(i=0;i<n;i++)
	{
		printf("%d\t",a[i]);
	}
}
void swap(int *a,int *b)
{
    int t=0;
    t=*a;
    *a=*b;
    *b=t;
}
int partition(int a[50],int low,int high)
{
    int piv,i,j;
    piv=a[low];
    i=low+1;
    j=high;
    while(1)
    {
        while(a[i] <= piv && i<high)
            i++;
        while(a[j] >= piv && j>low)
            j--;
        if(i<j)
            swap(&a[i],&a[j]);
        else
            break;
    }
    swap(&a[low],&a[j]);
    return j;
}
void rec_quick(int a[50],int low,int high)
{
    int j=0,i;
    if(low < high)
    {
        /*for(i=low;i<high+1;i++)
            	printf("%d\t",a[i]);
	printf("\n");*/
        j = partition(a,low,high);
        rec_quick(a,low,j-1);
        rec_quick(a,j+1,high);
    }
}
 

pid_t cid;
int main()
{
	int a[50],n,i;
	printf("Enter no. of elements : ");
	scanf("%d",&n);
	printf("Enter numbers : ");
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	int low=0,high=n-1;
	//printf("I am parent %d\n",getpid());
	cid=fork();
	switch(cid)
	{
		case -1 :
			printf("Fork error.\n");
			break;
		case 0 :
			printf("I am a child process. My process id is %d.\n",getpid());
			printf("Insertion sort : ");
			insert(a,n);
			printf("\n\n");
			/*sleep(20);
			printf("I am a child process. My process id is %d.\n",getpid());
			printf("My parent id is %d.\n",getppid());*/
			
			break;
		default :
			wait(NULL);
			printf("I am parent and my id %d.\n",getpid());
			rec_quick(a,low,high);
			printf("\nQuick sort :");
    			for(i=0;i<n;i++)
       				printf("\t %d",a[i]);
  			printf("\n\n");
			/*printf("I am parent and my id %d.\n",getpid());
			printf("I am waiting for my child.\n");*/
	}
	return 0;
	
}
