#include<stdio.h>
extern char ** environ;

int main()
{
	int i;
	printf("environment:\n");
	for(i = 0;environ[i] != NULL;i++)
		printf("%s\n",environ[i]);
	return 0;
}
