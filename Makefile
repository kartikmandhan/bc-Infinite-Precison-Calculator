project: infix.o istack.o list.o functions.o main.o
	cc infix.o istack.o list.o functions.o -lm -o project
functions.o: functions.c list.h functions.h
	cc -c functions.c -Wall
infix.o: infix.c istack.h functions.h
	cc -c infix.c -Wall
istack.o: istack.c istack.h
	cc -c istack.c -Wall
list.o: list.c list.h
	cc -c list.c -Wall

