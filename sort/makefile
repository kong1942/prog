all: rand.o bsort.o isort.o
	cc rand.o -o rand
	./rand
	cc bsort.o -o bsort
	cc isort.o -o isort

rand.o: rand.c
bsort.o: sort.h 2.insertion_sort.c
	gcc -c 1.bubble_sort.c -o $@
isort.o: sort.h 2.insertion_sort.c
	gcc -c 2.insertion_sort.c -o $@

clean:
	rm -f rand.o bsort.o isort.o rand data bsort isort
