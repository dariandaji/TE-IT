#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
//#define size 5
//#define numb_threads 10

int size;
int buffer[30];
int buffer_index;
pthread_mutex_t buffer_mutex;

sem_t full_sem;
sem_t empty_sem;

void insertbuffer(int value)
{
	if(buffer_index<size)
	{
		buffer[buffer_index++]=value;
	}
	else
	{
		printf("buffer overflow\n");
	}
}
int dequeuebuffer()
{
	if(buffer_index>0)
	{
		return buffer[--buffer_index];
	}
	else
	{
		printf("buffer underflow\n");
	}
}
void *producer(void *thread_n)
{
	int thread_numb=*(int *) thread_n;
	int value;
	int i=0;
	value=rand()%100;
	sem_wait(&full_sem);
	pthread_mutex_lock(&buffer_mutex);
	insertbuffer(value);
	pthread_mutex_unlock(&buffer_mutex);
	sem_post(&empty_sem);
	printf("producer %d added %d to buffer\n",thread_numb,value);
	pthread_exit(0);
}
void *consumer(void *thread_n)
{
	int thread_numb=*(int *) thread_n;
	int value;
	int i=0;
	sem_wait(&empty_sem);
	pthread_mutex_lock(&buffer_mutex);
	value=dequeuebuffer(value);
	pthread_mutex_unlock(&buffer_mutex);
	sem_post(&full_sem);
	printf("consumer %d dequeue %d from buffer\n",thread_numb,value);
	pthread_exit(0);
}
int main()
{	
	int p,c;
	while(1)
	{
	printf("\nenter size of buffer:\n");
	scanf("%d",&size);
	printf("\nenter no of producers:");
	scanf("%d",&p);
	printf("\nenter no of consumers:");
	scanf("%d",&c);
	if(c>p || p>size ||c>size)
		printf("\nERROR");
	if(c<=p && size>=p)
		break;
	}
	int buffer[size];
	int numb_threads=c+p;
	buffer_index=0;
	sem_init(&full_sem,0,size);
	sem_init(&empty_sem,0,0);
	pthread_t thread[numb_threads];
	int thread_numb[numb_threads];
	int i;
	for(i=0;i<numb_threads;i++)
	{
		thread_numb[i]=i;
		pthread_create(&thread[i],NULL,producer,&thread_numb[i]);
		i++;
		thread_numb[i]=i;
		pthread_create(&thread[i],NULL,consumer,&thread_numb[i]);
	}
	for(i=0;i<numb_threads;i++)
	{
		pthread_join(thread[i],NULL);
		
	pthread_mutex_destroy(&buffer_mutex);
	sem_destroy(&full_sem);
	sem_destroy(&empty_sem);
	}
	return 0;
}
