#include <stdio.h>

  struct person
{
	char name[20];
	int  age;
	char sex;
	char phone[15];
};

  int main ()
  {
	  struct person p1= {"jack",22,'n',"18800000000"};
	  struct person p2;
	  p2.name={'m','i'};
	  p2.age = 18;
	  p2.sex = 'y' ;
	  p2.phone = "13000000000";

	 printf("p1 name : %s\n",p1.name);
	 printf("p1 age : %d\n",p1.age);
	 printf("p1 sex : %c\n",p1.sex);
	 printf("p1 phone : %s\n",p1.phone);

	 printf("p2 name : %s\n",p2.name);
	 printf("p2 age : %d\n",p2.age);
	 printf("p2 sex : %c\n",p2.sex);
	 printf("p2 phone : %s\n",p2.phone);


  }
