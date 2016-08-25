#include<stdio.h>
#include<iostream>
  void Func(char ch);
  void Func(signed char ch);
  void Func(unsigned char ch);
int main()
{
  char a = 'a';
  signed char b = 'b';
  unsigned char c = 'c';
  Func(a) ;
  Func(b) ;
  Func(c) ;
}
  void Func(char ch) 
{
	printf("char is %c\n",ch);
}
  void Func(signed char ch)
{
	printf("signed char is %c\n",ch);
}

  void Func(unsigned char ch) 
{
	printf("unsigned char is %c\n",ch);
}

