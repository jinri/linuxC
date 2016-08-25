#include<stdio.h>
int main()
{
	int a=10;
	char c = 'a';
	int * p = &a;
	char *t = &c;
	printf("%d\n",p-t);
}
