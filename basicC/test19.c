#include<stdio.h>
#include<string.h>

int main()
{
	int * p1 = NULL;
	printf("p1 is %p",p1);
	printf("p1 is %d",*p1);  //对空指针进行解引用
}
