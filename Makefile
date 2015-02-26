#The main program
bench: bench.c freemem.o getmem.o get_mem_stats.o print_heap.o
	gcc -std=c11 -Wall -g -o bench freemem.o getmem.o get_mem_stats.o print_heap.o bench.c 

freemem.o: freemem.c
	gcc -std=c11 -Wall -g -c freemem.c

getmem.o: getmem.c
	gcc -std=c11 -Wall -g -c getmem.c

get_mem_stats.o: get_mem_stats.c
	gcc -std=c11 -Wall -g -c get_mem_stats.c

print_heap.o: print_heap.c
	gcc -std=c11 -Wall -g -c print_heap.c
clean:
	rm -rf *.o bench
