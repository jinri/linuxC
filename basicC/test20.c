#include<stdio.h>
#include<stdlib.h>

int main()
{
	int * s = (int *)malloc(sizeof(int)*10);
	int i;
	for( i=0 ;i < 10;i++)
	{
		s[i]=0;	
	}	
	for( i=0 ;i < 10;i++)
	{
		printf("legal access %d,%d\n",i,s[i]);
	}	
	printf("illegal access %d,%d\n",i,s[i]);
	free(s);
}
