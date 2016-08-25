 #include <stdio.h>
 #include <string.h>
    int main ()
    {
		char str1[10] = {'h','e','l','l','o'};
		char str2[] = {"hello"};
		int i,j;
		for( i =0;i<10;i++)
		{
			printf("str1[%d] is %c\n",i,str1[i]);
		}
		for( j=0;j < 6;j++)
		{
			printf("str2[%d] is %c\n",j,str2[j]);
		}
		printf("str2 is %s\n",str2);
		printf("sizeof(str1) =  %zd\n",sizeof(str1));
		printf("sizeof(str2) =  %zd\n",sizeof(str2));
		printf("strlen(str1) =  %zd\n",strlen(str1));
		printf("strlen(str2) =  %zd\n",strlen(str2));
    }
