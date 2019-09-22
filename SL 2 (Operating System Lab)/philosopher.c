#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<signal.h>
#include<semaphore.h>
sem_t chopstick[5];
sem_t room;
int cnt[5]={0};
void *philosopher(void *arg)
{
	int j=*(int *)arg;
	while(cnt[j]<3)
	{
		printf("\nphilosopher %d is now thinking\n",j);
		sleep(3);
		sem_wait(&room);
		sem_wait(&chopstick[j]);
		sem_wait(&chopstick[(j+1)%5]);
		printf("\nPhilosopher %d is now eating using fork %d and %d for %dth time\n",j,j,(j+1),(cnt[j]+1));
		sleep(2);
		cnt[j]+=1;
		sem_post(&chopstick[(j+1)%5]);
		sem_post(&chopstick[j]);
		sem_post(&room);
	}
	printf("\nPhilosopher %d is eating\n",j);
	sleep(2);
	pthread_exit(NULL);
}

int main()
{
	pthread_t philo[5];
	int i,temp[5];
	for(i=0;i<5;i++)
		sem_init(&chopstick[i],0,1);
	sem_init(&room,0,4);
	for(i=0;i<5;i++)
	{
		temp[i]=i;
		pthread_create(&philo[i],NULL,philosopher,&temp[i]);
	}
	for(i=0;i<5;i++)
		pthread_join(philo[i],NULL);
return 0;
}
