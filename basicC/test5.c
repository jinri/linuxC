#include<stdio.h>
int main(int argc ,char * argv[])
{
	char a [] = {'1','2','3','4','5'};
	char * p =a;
	for(p;p<a+5;p++){
	printf("p=%p",p);
	printf("*p=%c\n",*p);
	}

	printf("p=%p",p);
	*p = '6';
	printf("*p=%c\n",*p);
	p++;
	printf("p=%p",p);

	printf("*p=%c\n",*p);

}
