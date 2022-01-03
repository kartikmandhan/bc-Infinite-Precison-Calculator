project: directInfix.o stack.o list.o  main.o
	gcc directInfix.o stack.o list.o main.o -o project
	rm -rf *.o

directInfix.o: directInfix.c stack.h 
	gcc -c directInfix.c -Wall
stack.o: stack.c stack.h
	gcc -c stack.c -Wall
list.o: list.c list.h
	gcc -c list.c -Wall
main.o: main.c
	gcc -c main.c -Wall
