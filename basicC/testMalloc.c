#include<stdio.h>
#include<stdlib.h>
int main ()
{
	char * p = (char *)malloc(100*sizeof(char));
	printf("p is %p\n",p);
	free(p);
	p="testFreeLaterUse";	
	printf("str is %s\n",p);
}
