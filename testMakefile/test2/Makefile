main : main.o function1.o function2.o  function3.o 
	gcc main.o function1.o function2.o function3.o -o main
main.o : main.c test.h
	gcc -c main.c
function1.o : function1.c 
	gcc -c function1.c
function2.o : function2.c 
	gcc -c function2.c
function3.o : function3.c 
	gcc -c function3.c
clean :
	rm main main.o function1.o function2.o function3.o
