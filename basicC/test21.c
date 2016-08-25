#include<stdio.h>
#include<stdlib.h>

void GetMemory(char *p, int num)
{
    p = (char*)malloc(sizeof(char) * num);//使用new也能够检测出来
}

int main(){
	char *str = NULL;	   //第一种情况
    GetMemory(str, 100);   //如果main中存在while循环调用GetMemory, 那么问题将变得很严重 ,while(1){GetMemory(...);}
	printf("Memory leak test\n");
	
	char *memoryArea = malloc(10);
	char *newArea = malloc(10);
	newArea = memoryArea;  //第二种情况，把memoryArea 赋值给newArea后，原来newArea指向的内存首地址会丢失，造成内存泄露     
	free(newArea);
	//free(memoryArea);a   //会造成释放同一块内存两次的错误
    return 0;
}
