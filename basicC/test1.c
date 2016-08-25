#include<stdio.h>
int main(int argc,char * argv[])
{
	int n=10;
	int b[n]={0};
	int i = 0; 
	for(i;i<10;i++)
	{
		b[i] = i;
		printf("i=%d,b[i]=%d\n",i,b[i]);
	}
}
