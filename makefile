myshell : myshell.o utility.o
	gcc -o myshell myshell.o utility.o

myshell.o:
	gcc -c myshell.c

utility.o:
	gcc -c utility.c

clean :
	rm myshell
	rm *.o