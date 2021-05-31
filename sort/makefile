all: rand.o bsort.o isort.o ssort.o qsort.o msort.o hsort.o rsort.o
	gcc rand.o -o rand
	./rand
	gcc bsort.o -o bsort
	gcc isort.o -o isort
	gcc ssort.o -o ssort
	gcc qsort.o -o qsort
	gcc msort.o -o msort
	gcc hsort.o -o hsort
	gcc rsort.o -o rsort

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
hsort.o: sort.h 6.heap_sort.c
	gcc -c 6.heap_sort.c -o $@
rsort.o: sort.h 7.radix_sort.c
	gcc -c 7.radix_sort.c -o $@


clean:
	rm -f rand.o bsort.o isort.o ssort.o qsort.o msort.o hsort.o rsort.o rand data bsort isort ssort qsort msort rsort hsort
