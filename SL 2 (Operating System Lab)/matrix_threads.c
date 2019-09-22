#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

/*int arr1[3][3];
int arr2[3][3];
int res[3][3];
*/

int r1,c1,r2,c2;
int **arr1;
int **arr2;
int **res;

struct v
{
	int i,j;
};

int sum;

void* result(void *arg);

int main()
{
	struct v* data = (struct v*)malloc(sizeof(struct v));
	pthread_t tid;
	int i,j,res1=0;
	void *status=NULL;
	
	arr1 = (int **)malloc(r1 * sizeof(int *));
	arr2 = (int **)malloc(r2 * sizeof(int *));
	res = (int **)malloc(r1 * sizeof(int *));
	
	while(1)
	{
		printf("Enter dimensions of 1st matrix : ");
		scanf("%d%d",&r1,&c1);
		printf("Enter dimensions of 2nd matrix : ");
		scanf("%d%d",&r2,&c2);
		if(c1 != r2)
			printf("Error! col1 and row2 should be same.\n");
		else
			break;
	}
	
	
	for(i=0;i<r1;i++)
		arr1[i]=(int *)malloc(c1 * sizeof(int));
	for(i=0;i<r2;i++)
		arr2[i]=(int *)malloc(c2 * sizeof(int));
	for(i=0;i<r1;i++)
		res[i]=(int *)malloc(c2 * sizeof(int));
	
		
	printf("Enter elements of 1st matrix : ");
	for(i=0;i<r1;i++)
		for(j=0;j<c1;j++)
			scanf("%d",&arr1[i][j]);
			
	printf("Enter elements of 2nd matrix : ");
	for(i=0;i<r2;i++)
		for(j=0;j<c2;j++)
			scanf("%d",&arr2[i][j]);
			
	for(i=0;i<r1;i++)
		for(j=0;j<c2;j++)
		{
			data->i = i;
			data->j = j;
			pthread_create(&tid,NULL,result,data);
			pthread_join(tid,&status);
			res1=*((int*)status);
			printf("\nSum is : %d",res1);
			res[data->i][data->j]=res1;
		}
	printf("\n");
	printf("Resultant matrix is : \n");
	for(i=0;i<r1;i++)
	{
		for(j=0;j<c2;j++)
		{
			printf("%d\t",res[i][j]);
		}	
		printf("\n");
	}	
}

void *result(void *arg)
{
	struct v *data1=arg;
	int k;
	sum=0;
	for(k=0;k<r2;k++)
		sum+=arr1[data1->i][k] * arr2[k][data1->j];
	pthread_exit(&sum);
}





