//get_mem_stats.c
#include <inttypes.h>
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