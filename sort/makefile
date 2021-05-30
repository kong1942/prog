all: rand.o bsort.o isort.o ssort.o qsort.o msort.o rsort.o
	cc rand.o -o rand
	./rand
	cc bsort.o -o bsort
	cc isort.o -o isort
	cc ssort.o -o ssort
	cc qsort.o -o qsort
	cc msort.o -o msort
	cc rsort.o -o rsort

rand.o: rand.c
bsort.o: sort.h 1.bubble_sort.c
	gcc -c 1.bubble_sort.c -o $@
isort.o: sort.h 2.insertion_sort.c
	gcc -c 2.insertion_sort.c -o $@
ssort.o: sort.h 3.selection_sort.c
	gcc -c 3.selection_sort.c -o $@
qsort.o: sort.h 4.quick_sort.c
	gcc -c 4.quick_sort.c -o $@
msort.o: sort.h 5.merge_sort.c
	gcc -c 5.merge_sort.c -o $@
rsort.o: sort.h 7.radix_sort.c
	gcc -c 7.radix_sort.c -o $@


clean:
	rm -f rand.o bsort.o isort.o ssort.o qsort.o msort.o rsort.o rand data bsort isort ssort qsort msort rsort
