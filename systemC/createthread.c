#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

int * thread(void  *arg)
{
	pthread_t newthid;

	newthid = pthread_self();          //获取本线程的线程
	printf("this is a new thread ,thread ID is %lu\n",newthid);
	return 0;
}

int main()
{
	pthread_t thid;

	printf("main thread , ID is %lu\n",pthread_self()); //打印主线程的ID
	if(pthread_create(&thid,NULL,(void *)thread,NULL) != 0)
	{
		printf("thread create failed\n");
		exit(1);
	}
	sleep(1);
	exit(0);
}
