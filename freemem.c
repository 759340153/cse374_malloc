//freemem.c
#include <inttypes.h>
#include "mem.h"

//will free the block of memory the passed in pointer points to
void freemem(void* p) {
	if (!p) {
		return;
	} 
	//void* prev = findMemorySpot
	//add p to free
	//combineSmallBlocks(p, prev);
	return;
}

void combineSmallBlocks(void* p, void* prev) {
	//combine small blocks
		//if p.next is at the address &p + size of p, combine
		//if prev + size of prev is the address of p, combine
	return;
}

//returns a pointer to the data block that appears before the passed in data block in memory
//returns null if p should be added front of free
void* findMemorySpot(void* p) {
	//if free is empty, pass null
	//goes until the address of one block + the size of that block is < the address of p and address of the next block is > than the address of p
	//if the end of free is reached, pass the last block in free
}
