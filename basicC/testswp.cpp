#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


typedef int* Triplet;

void swap(int* a, int* b);
int InitArray(int* arr, int a, int b, int c);
int InitTriplet(Triplet* T, int a, int b, int c);
int TestPointAssign(Triplet T, int a, int b, int c);


int main()
{
	int m = 2, n = 4;
	int Array[] = {1, 2, 3};
	Triplet T_num = NULL;

	swap(&m, &n);
	printf("m = %d, n = %d\n", m, n);

	//为已分配空间（指针指向/数组）赋值
	InitArray(Array, 11, 12, 13);
	printf("A[0] = %d, A[1] = %d, A[2] = %d\n", Array[0], Array[1], Array[2]);
	
	//指针变量T_num的值（指向的地址）与自身地址
	printf("before test:T_num:%p, &T_num:%p\n", T_num,  &T_num);
	TestPointAssign(T_num, 111, 112, 113);
	
	//指针变量T_num的值（指向的地址）与自身地址
	printf("after test:T_num:%p, &T_num:%p\n", T_num,  &T_num);

	//指针指针指向新地址之前的地址 （此处 NULL--0000）
	//printf("address before resign:%d\n",T_num);

	//使指针指向新地址，在新地址处为其分配所指定大小的存储空间
	InitTriplet(&T_num, 1, 2, 3);
	//T_num存储指针指向新地址之后的地址 （即连续3个存储空间的首地址）
	printf("after resign:T_num:%p, *T_num:%d, &T_num:%p\n", T_num, *T_num, &T_num);
	printf("Init point:T_num[0] = %d, T_num[1] = %d, T_num[2] = %d\n", T_num[0], T_num[1], T_num[2]);

	return 0;
}

void swap(int* a, int* b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

int InitArray(int* arr, int a, int b, int c)
{
	arr[0] = a;
	arr[1] = b;
	arr[2] = c;

	return 0;
}

int InitTriplet(Triplet* T, int a, int b, int c)
{
	*T = (int*)malloc(sizeof(int) * 3);
	if ( !(*T) )
	{
		printf("overflow");
		exit(0);
	}
	(*T)[0] = a;
	(*T)[1] = b;
	(*T)[2] = c;

	return 0;
}

int TestPointAssign(Triplet T, int a, int b, int c)
{
	T = (int*)malloc(sizeof(int) * 3);
	if ( !T )
	{
		printf("overflow");
		exit(0);
	}
	T[0] = a;
	T[1] = b;
	T[2] = c;
	printf("In function 0~2: %d, %d, %d\n", T[0], T[1], T[2]);
	printf("In function test address:%p\n",T);

	return 0;
}
