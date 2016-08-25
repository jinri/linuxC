obj = main.o function1.o function2.o  function3.o 
main : $(obj) 
	gcc $(obj) -o main
main.o : main.h
	gcc -c main.c
function1.o :  function1.h
	gcc -c function1.c
function2.o :  function2.h
	gcc -c function2.c
function3.o :  function3.h
	gcc -c function3.c
.PHONY :clean
clean :
	rm main $(obj)
