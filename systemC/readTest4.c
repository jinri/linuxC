#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAXSIZE 35

int main()
{	
	int n;
	int fd;
	int size;
	int len ;
	int i,j;
	char * buf="hello! I`m writing this file!";
	char buf_r[MAXSIZE];
	
	len  = strlen(buf);
	fd = open("testRead.txt",O_CREAT|O_TRUNC|O_RDWR,0666);
	if(fd < 0)
	{
		perror("open:");
		exit(1);
	}else
	{
		printf("Open file:testRead.c %d\n",fd);
	}
	if((size = write(fd,buf,len)) < 0)
	{
		perror("write:");
		exit(1);
	}
	else

	printf("write:%s\n\n\n",buf);
	printf("now test started \n");
	

	for(i=0;i<20;i++){
                lseek(fd,0,SEEK_SET);
                for(j=0;j<MAXSIZE;j++)
                        buf_r[j]=0;
				
                size=read(fd,buf_r,MAXSIZE-i);
				printf("first read from file:%s \n",buf_r);
				printf("size=%d\n",size);
                while(size > 0)
				{
                for(j=0;j<MAXSIZE;j++)
                        buf_r[j]=0;
					size=read(fd,buf_r,MAXSIZE-i);
					buf_r[MAXSIZE-i]='\0';
					printf("string-len=%d,count=%d,size=%d\n",len,MAXSIZE-i,size);
					printf("while read from file:%s \n",buf_r);
				}
				printf("\n");
                if(size < 0){
					perror("read:");
					exit(1);
                }
        }
        printf("\n\nNow test stops...\n");
        //close
        if(close(fd)<0){
                perror("close:");
                exit(1);
        }
        else
                printf("close hello.c\n");
        exit(0);	

}
