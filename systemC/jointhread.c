#include<stdio.h>
#include<pthread.h>

void assisthread(void * arg)
{
	printf("do some jobs\n");
	sleep(3);
	pthread_exit(0);
}

int main()
{
	pthread_t thid;
	int status;
	pthread_create(&thid,NULL,(void *)assisthread,NULL);
	pthread_join(thid,(void *)&status);
	printf("the assisthread`s exit is caused %d\n",status);
	return 0;
}
