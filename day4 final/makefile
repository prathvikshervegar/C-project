a : client.o customer.o item.o date.o bill_generate.o
	gcc client.o customer.o item.o date.o bill_generate.o
bill_generate.o : bill_generate.c bill_generate.h customer.h item.h date.h
	gcc -c bill_generate.c
date.o : date.c date.h
	gcc -c date.c
item.o : item.c item.h
	gcc -c item.c
customer.o : customer.c customer.h
	gcc -c customer.c
client.o : client.c customer.h item.h date.h bill_generate.h
	gcc -c client.c