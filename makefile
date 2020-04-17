myshell : myshell.o utility.o
	gcc myshell.o utility.o -o myshell

myshell.o:
	gcc -c myshell.c myshell.h

utility.o:
	gcc -c utility.c

clean :
	rm myshell
	rm *.o
	rm myshell.h.gch