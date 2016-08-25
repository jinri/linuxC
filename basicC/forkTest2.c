#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
	pid_t pid;
	pid = fork ();
	switch(pid){
	case 0:
	printf("pid of son = %d\n",pid);
	break;

	case -1:
	perror("fork");
	break;

	default:
	printf("pid of parent = %d\n",pid);
	break;
	}	
	exit(0);
}
