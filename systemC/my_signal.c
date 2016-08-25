#include<stdio.h>
#include<signal.h>

void	my_handler(int signo)
{
	printf("recv my signal\n");//信号处理函数
}
int main()
{
	signal(SIGINT,my_handler); //安装信号处理函数
	while(1)
	{
		;
	}
	return 0;
}
