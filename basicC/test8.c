#include <stdio.h>

int main()
{
	printf("char is %zd\n",sizeof(char));
	printf("signed char is %lu\n",sizeof(signed char));
	printf("unsigned char is %ld\n",sizeof(unsigned char));

    if(sizeof(int) - sizeof(double) < 0)
    {
        printf("<\n");
    }
    else
    {
        printf(">=\n");
    }

    return 0;
}
