//freemem.c
#include <inttypes.h>
#include "mem.h"
#include "mem_impl.h"

extern memNode * root;
extern int totalFree;
extern int usedMem;
extern int freeMem;

void freemem(memNode * p);
void combineSmallBlocks(memNode * p, memNode * prev);
memNode * findMemorySpot(memNode * p);
void addToFree(memNode * p, memNode * prev);

//will free the block of memory the passed in pointer points to
void freemem(memNode * p) {
	if (!p) {
		return;
	} 
	memNode * prev = findMemorySpot(p);
	addToFree(p, prev);
	combineSmallBlocks(p, prev);
}

void combineSmallBlocks(memNode * p, memNode * prev) {
	if (p->next) {
		memNode * pNext = (memNode *) p->next;
		if (p + p->size+16 - pNext == 0) {
			p->size = p->size + pNext->size + 32;
			if (pNext->next) {
				p->next = pNext->next;
			} else {
				p->next = (uintptr_t) NULL;
			}
		}
	}
	if (prev) {
		if (prev + prev->size+16 - p == 0) {
			prev->size = prev->size + p->size + 32;
			if (p->next) {
				prev->next = p->next;
			} else {
				prev->next = (uintptr_t) NULL;
			}
		}
	}
}

//returns a pointer to the data block that appears before the passed in data block in memory
//returns null if p should be added front of free
memNode * findMemorySpot(memNode * p) {
	if (!root || root > p) {
		return NULL;
	}
	memNode * node = root;
	//address of next size is &root + (root->size+2)/8
	//difference between 2 addresses in bytes is a1 + root->size+16 - a2 
	while (node->next) {
		if ((memNode *) node->next < p) {
			node = (memNode *) node->next;
		} else {
			return node;
		}
	}
	return node;
}

void addToFree(memNode * p, memNode * prev) {
	if (!prev) {
		if (root->next) {
			p->next = root->next;
			root = p;
		} else {
			root = p;
		}
	} else if (!prev->next) {
		prev->next = (uintptr_t) &p;
	} else {
		p->next = prev->next;
		prev->next = (uintptr_t) &p;
	}
}
