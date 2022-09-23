a.out : client.o date.o read.o bill_generate.o display.o
	gcc client.o date.o read.o bill_generate.o display.o
date.o : date.c date.h 
	gcc -c date.c
read.o : read.c read.h date.h
	gcc -c read.c
bill_generate.o : bill_generate.c bill_generate.h date.h read.h
	gcc -c bill_generate.c
display.o : display.c display.h date.h read.h bill_generate.h
	gcc -c display.c
client.o : client.c date.h read.h bill_generate.h display.h
	gcc -c client.c