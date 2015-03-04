//mem.h
//declares all the functions that can be used externally
#include <inttypes.h>
#include <stdio.h>
#include "mem_impl.h"
#ifndef test
#define test

// gets a block of memory of size size
void* getmem(uintptr_t size); 

//frees the block of memory stored at pointer p
void freemem(void * p); 

//stores stats about the state of the memory manager in the 3 pointers provided
//stores total size stored in bytes, total number amount of free storage in bytes, and the number of free blocks 
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks); 

//prints a list of all the blocks on the free list into the file provided
void print_heap(FILE * f);
#endif