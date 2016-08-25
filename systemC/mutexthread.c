#include<stdio.h>
#include<pthread.h>
#include<string.h>

pthread_mutex_t mutex;
int  globalnum;

void write_num()
{
	pthread_mutex_lock(&mutex);
	globalnum ++;
	pthread_mutex_unlock(&mutex);
}
int read_num()
{
	int temp;
	pthread_mutex_lock(&mutex);
	temp = globalnum;
	pthread_mutex_unlock(&mutex);
	return (temp);
}
void thread1()
{	
	int i=0;
	for (i;i<5;i++)
	{
		write_num();
		sleep(1);
	}
	pthread_exit(0);
}
void thread2()
{
	int j=0;
	for (j;j<5;j++)
	{
		printf("read number:%d\n",read_num());
		sleep(1);
	}
	pthread_exit(0);
	
}
int main()
{
	pthread_t thid1,thid2;
	pthread_mutex_init(&mutex,NULL);
	printf("main thread begins\n");
	pthread_create(&thid1,NULL,(void *)thread1,NULL);
	pthread_create(&thid2,NULL,(void *)thread2,NULL);
	sleep(5);
	pthread_mutex_destroy(&mutex);
	printf("main thread exit\n");
	return 0;
}
