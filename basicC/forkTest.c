#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
	pid_t pid;
	pid = fork ();
	if(pid > 0)
	printf("pid of parent = %d\n",pid);
	else if(!pid)
	printf("pid of son = %d\n",pid);
	else if(pid == -1)
	perror("fork");
	exit(0);
}
