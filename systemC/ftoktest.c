#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	for (i = 1; i <= 5; i++)
	printf("key[%d] = %ul \n",i,ftok(".",i));
	exit(0);
}

