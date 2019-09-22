#include <stdio.h>
#include <stdlib.h>

struct myStruct
{
	int p_index, p_size;
};

int tapes[10][10];
struct myStruct acc[10], rej[10];

void sort(int progs[], int p)
{
	int min_val, indx;
	for(int i=0; i<p-1; i++)
	{
		min_val = progs[i];
		indx = -1;
		for(int j=i+1; j<p; j++)
			if(progs[j] < min_val)
				min_val = progs[j], indx = j;
				
		if(indx!=-1)
		{
			int tmp = progs[i];
			progs[i] = progs[indx];
			progs[indx] = tmp;
		}
	}
}

int store(int progs[], int noOfProgs, int noOfTapes, int tapeSize)
{
	int i, j=0, k=0, a=0, r=0;
	int sum[noOfTapes];
	for(int i=0; i<noOfTapes; i++)
		sum[i] = 0;
		
	for(int i=0; i<noOfProgs; i++)
	{
		struct myStruct ms;
		ms.p_index = i;
		ms.p_size = progs[i];
		if(sum[j]+progs[i] <= tapeSize)
		{
			tapes[j][k] = progs[i];
			sum[j] += progs[i];
			acc[a++] = ms;
		}
		else
		{
			rej[r++] = ms;
		}	
		j = (j+1) % noOfTapes;
		if(j==0) k++;
	}
	return k;
}

void printArr(int arr[], int n)
{
	for(int i=0; i<n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void printMat(int rows, int cols)
{
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
			printf("%d ", tapes[i][j]);
		printf("\n");
	}
}

int main()
{
	int p;
	printf("Enter no. of programs: ");
	scanf("%d", &p);
	
	int progs[p];
	printf("Enter size of programs sequentially:\n");
	for(int i=0; i<p; i++)
	{
		printf("Program %d: ",i+1);
		scanf("%d", &progs[i]);
	}
	
	int t, t_size;
	printf("Enter no. of tapes: ");
	scanf("%d", &t);
	printf("Enter size of tapes: ");
	scanf("%d", &t_size);
	
	sort(progs, p);
	printArr(progs, p);
	printf("\n");
	
	int k = store(progs, p, t, t_size);
	printMat(t, k+1);
	
	printf("\nAccepted: ");
	for(int i=0; i<10; i++)
	{
		printf("P%d: %d\n", acc[i].p_index, acc[i].p_size);
	}
	
	printf("\nRejected: ");
	for(int i=0; i<10; i++)
	{
		printf("P%d: %d\n", rej[i].p_index, rej[i].p_size);
	}
}




