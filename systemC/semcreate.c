#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/msg.h>  
#include <sys/types.h>
#include <sys/ipc.h>  
#include <errno.h>  

 int main() 
{  
	key_t key;
	int sem;
	
	if((key=ftok(".",123)) == -1)
	{
        fprintf(stderr, "ftol failed with error: %d\n", errno);  
	}
    //建立信号量 
    sem = semget(key,3, 0666 | IPC_CREAT);  
    if(sem == -1)  
    {  
        fprintf(stderr, "semget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);  
    } 
	printf("sem id is :%d\n",sem);
	sleep(15);
	semctl(sem,0,IPC_RMID,(struct semid_ds *) 0);
  
    exit(EXIT_SUCCESS);  
}  
