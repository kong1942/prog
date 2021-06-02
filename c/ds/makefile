all: stack.o queue.o linked-list.o hash.o
	gcc stack.o -o stack
	gcc queue.o -o queue
	gcc hash.o -o hash
	gcc linked-list.o -o linked-list

stack.o: ds.h 1.stack.c
	gcc -c 1.stack.c -o $@
queue.o: ds.h 2.queue.c
	gcc -c 2.queue.c -o $@
hash.o: ds.h 3.hash-table.c
	gcc -c 3.hash-table.c -o $@
linked-list.o: ds.h 4.linked-list.c
	gcc -c 4.linked-list.c -o $@

clean:
	rm -f stack.o stack queue.o queue linked-list.o linked-list hash.o hash
