a.out : main.o bookTicket.o registration.o
	gcc main.o bookTicket.o registration.o -o a.out

main.o : main.c allFunctions.h
	gcc -c main.c

bookTicket.o: bookTicket.c allFunctions.h
	gcc -c bookTicket.c

registration.o: registration.c allFunctions.h
	gcc -c registration.c

clean : rm *.o a.out
