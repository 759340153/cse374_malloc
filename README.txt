Max Golub was responsible for Bench.c, getmem.c, and print_heap.c.  Alex Gingras was
in charge of freemem.c, get_mem_stats.c, mem_impl.h, mem.h, and externs.h.  We did
each of our parts separately, although we occasionally asked each other for a 
little bit of help.

Our heap is designed as a linked list of memNodes, each of which has a size field 
containing the size of the data which that object can hold and a next field which
contains a pointer to the next node in the linked list.  Each memNode is followed
by an empty array of size memNode->size which is followed by the memNode memNode->next
points to.  This works because each block of memory is initially gotten by malloc
so we know we have enough free space.

We used /dev/urandom in our bench.c to get a more random pseudo-random number.  we
did not implement any extra credit.  

[DESCRIPTION OF BENCH RESULTS]

We used Wikipedia, stackExchange, the Malloc source code, and http://g.oswego.edu/dl/html/malloc.html
for help in creating our code.  