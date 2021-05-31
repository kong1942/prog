all: stack.o
	gcc stack.o -o stack

stack.o: ds.h 1.stack.c
	gcc -c 1.stack.c -o $@

clean:
	rm -f stack.o stack
