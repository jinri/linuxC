#include<stdio.h>
#include<string.h>
int main(int argc ,char * argv[])
{
	char str1[10] = {'h','e','l','l','o'};
	char str2[] ={"hello"};
	printf("sizeof(str1)=%d,sizeof(str2)=%d\n",sizeof(str1),sizeof(str2));
	printf("strlen(str1)=%d,strlen(str2)=%d\n",strlen(str1),strlen(str2));
}
