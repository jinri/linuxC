#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){
	printf("sizeof(bool)%lu\n",sizeof(bool));
	printf("sizeof(char)=%lu\n",sizeof(char));
	printf("sizeof(short)=%lu\n",sizeof(short));
	printf("sizeof(int)=%lu\n",sizeof(int));
	printf("sizeof(long)=%lu\n",sizeof(long));
	printf("sizeof(long long)=%lu\n",sizeof(long long));
	printf("sizeof(float)=%lu\n",sizeof(float));
	printf("sizeof(double)=%lu\n",sizeof(double));
	printf("sizeof(long double)=%lu\n",sizeof(long double));
	printf("sizeof(void)=%lu\n",sizeof(void));
	return 0;
}

