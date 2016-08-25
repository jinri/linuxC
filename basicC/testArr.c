#include<stdio.h>
#include<string.h>

char * getName()
{
	
	char arr[100];
	strcpy(arr,"jack");
	return arr;
}
int 
main()
{
	char * name = getName();
	printf("%s\n",name);
}
