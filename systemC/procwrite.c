#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>

#define FIFO_NAME "myfifo"
#define BUF_SIZE  1024

int main()
{
	int fd;
	char buf[BUF_SIZE] = "Hello,i am procwrite";
	umask(0);
	if (mkfifo (FIFO_NAME,S_IFIFO | 0666) == -1)
	{
		perror("mkfifo error!");
		exit(1);
	}
	
	if((fd = open(FIFO_NAME,O_WRONLY)) == -1)
	{
		perror("fopen error!");
		exit(1);
	}
	write(fd,buf,strlen(buf)+1);
	printf("write content:%s\n",buf);
	close(fd);
	exit(0);
}
