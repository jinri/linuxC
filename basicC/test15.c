 #include <stdio.h>
  int main ()
    {
       int  var1;
       char var2[10];
       printf("var1 变量的地址： %x\n", &var1  );
       printf("var2 变量的地址： %x\n", &var2  );
       printf("sizeof(&var1) %zd\n", sizeof(&var1));
       printf("sizeof(&var2) %zd\n", sizeof(&var2));
       return 0;
    }
