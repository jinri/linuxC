#include<stdio.h>
void sayHello();
int main (int argc,char * argv[])
{
	int a = 1;
	int b = 2;
	char c = 'a';
	sayHello();
	return 0;
}

void sayHello()
{
	printf("%s","hello\n");
}
