#include<stdio.h>
#include<unistd.h>
pid_t cid;
int main()
{
	//printf("\nI am parent %d",getpid());

	cid=fork();
	switch(cid)
	{
		case -1: printf("\nfork() error");
			 break;
		case 0 : 
			 printf("\nI am a child process. My process id is %d",getpid());
			 printf("\nI am a child process and my parent is %d",getppid());
			 break;
		default: sleep(20);
			 printf("\nI am parent and my id is %d",getpid());
			 printf("\nI am waiting for child");
	}	
	return 0;
}
