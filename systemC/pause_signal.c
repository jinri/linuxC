#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void	my_handler(int signo)
{
	printf("recv my signal\n");//信号处理函数
}
int main()
{
	printf("main begining\n");
	if(signal(SIGINT,my_handler)==SIG_ERR) //安装信号处理函数
	{
		fprintf(stderr,"can not handle SIGINT!\n");
		exit(EXIT_FAILURE);
	}
	pause();
	printf("main ending\n");
	return 0;
}
