#include<stdio.h>
#include<pthread.h>
#include<string.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

void thread1()
{
	pthread_cleanup_push(pthread_mutex_unlock,&mutex);
	
	while(1)
	{
		printf("thread1 is running\n");
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		printf("thread1 applied the condition\n");
		pthread_mutex_unlock(&mutex);
		sleep(4);
	}
	pthread_cleanup_pop(0);
}
void thread2()
{
	pthread_cleanup_push(pthread_mutex_unlock,&mutex);
	
	while(1)
	{
		printf("thread2 is running\n");
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		printf("thread2 applied the condition\n");
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	pthread_cleanup_pop(0);
}
int main()
{
	pthread_t thid1,thid2;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	printf("main thread begins\n");
	pthread_create(&thid1,NULL,(void *)thread1,NULL);
	pthread_create(&thid2,NULL,(void *)thread2,NULL);
	do{
		pthread_cond_signal(&cond);
	}while(1);
	sleep(50);
	printf("main thread exit\n");
	pthread_exit(0);
}
