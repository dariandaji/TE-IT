#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/stat.h>

#define SZ 4096

int main()
{
	int shm_id;
	key_t mykey;
	int *shm_ptr;
	int ret_val;
	int data;
	
	mykey=ftok(".",'A');
	shm_id=shmget(mykey,SZ, IPC_CREAT | 0666);
	if(shm_id<0)
	{
		printf("\nshmget error");
		_exit(-1);
	}
	else
	{
		printf("\nShared memory is created\n");
		printf("\nShared memory id = %d\n",shm_id);
		
		shm_ptr=(int*)shmat(shm_id,NULL,0);
		if((long)shm_ptr!=-1)
		{
			printf("\nShared memory is attached at address : %p\n",shm_ptr);
		}
		
		printf("Enter the data\n");
		scanf("%d",&data);
		*shm_ptr= data;
		sleep(5);
	}
	ret_val=shmdt((void*)shm_ptr);
	if(ret_val==0)
	{
		printf("\nShared memory successfully detached.\n");
	}
	else
	{
		printf("\nshmdt error\n");
	}
	return 0;
}
