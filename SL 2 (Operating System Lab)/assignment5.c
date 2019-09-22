
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

pthread_mutex_t x;
pthread_mutex_t wsem;
int readcount = 0;
FILE *fp;
char str[15];
char txt;

void *reader(void *thread_n) 
{
	pthread_mutex_lock(&x);
	readcount++;
	if(readcount == 1)
		pthread_mutex_lock(&wsem);
	pthread_mutex_unlock(&x);
	
	printf("\n\n Enter File Name to read \n ");
	scanf("%s",str);

	fp=fopen(str,"r");

	printf("\n\n Contents Of Requested File Are:\n");

	while(!feof(fp))
	{
		txt=fgetc(fp);
		printf("%c",txt);
	}
	printf("\n");

	fclose(fp);
	sleep(1);
	pthread_mutex_lock(&x);
	readcount--;
	if(readcount == 0)
		pthread_mutex_unlock(&wsem);
	pthread_mutex_unlock(&x);

}

void *writer(void *thread_n) 
{
	pthread_mutex_lock(&wsem);
	printf("\nEnter File Name to Write\n");
	scanf("%s",str);

	fp=fopen(str,"a");

	printf("\n\n Inorder To Stop Writting Press Q ");
	printf("\n\n Enter The Text");

	do
	{
		scanf("%c",&txt);
		if(txt!='Q')
			fputc(txt,fp);
	}while(txt!='Q');
	fclose(fp);  
	sleep(1);
	pthread_mutex_unlock(&wsem);
}

int main()
{
    pthread_mutex_init(&x, NULL);
    pthread_mutex_init(&wsem, NULL);
    pthread_t thread[10];
    int thread_numb[10];
    int i;
    for (i = 0; i < 10;  i++) {
        thread_numb[i] = i;
        pthread_create(&thread[i], NULL, reader,&thread_numb[i]);  
 	i++;      
        thread_numb[i] = i;        
        pthread_create(&thread[i], NULL, writer, &thread_numb[i]);  
    }
 
    for (i = 0; i < 10; i++)
        pthread_join(thread[i], NULL);
 
    pthread_mutex_destroy(&x);
    pthread_mutex_destroy(&wsem);
    return 0;
}
