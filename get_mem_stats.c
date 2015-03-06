//Alex Gingras and Max Golub
//CSE 374 HW 6
//3/4/2015
//get_mem_stats allows a user to get some stats about the freeList and the 
//amount of memory allocated over the session
#include "mem_impl.h"
#include "externs.h"


void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks);

//gets external variables for all desired fields and inputs them into the corresponding pointers
//these variables are created/updated in the other files. 
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks) {
	*total_size = totalSize;
	*total_free = totalFree;
	*n_free_blocks = nFreeBlocks;
}