#include<stdio.h>
#include<pthread.h>
#include<string.h>

pthread_key_t key;

void * thread2(void * arg)
{	
	int tsd = 5;
	printf("thread2 %ld is running\n",pthread_self());
	pthread_setspecific(key,(void *)tsd);
	printf("thread2 returns %d\n",pthread_getspecific(key));
}
void * thread1(void * arg)
{	
	int tsd = 0;
	pthread_t thid2;
	printf("thread1 %ld is running\n",pthread_self());
	pthread_setspecific(key,(void *)tsd);
	pthread_create(&thid2,NULL,thread2,NULL);
	sleep(3);
	printf("thread1 returns %d\n",pthread_getspecific(key));
}
int main()
{
	pthread_t thid1;
	printf("main thread begins\n");
	pthread_key_create(&key,NULL);
	pthread_create(&thid1,NULL,thread1,NULL);
	sleep(5);
	pthread_key_delete(key);
	printf("main thread exit\n");
	return 0;
}
