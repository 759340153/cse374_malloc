//Alex Gingras and Max Golub
//CSE 374 HW 6
//3/4/2015
//This is freemem, which takes a pointer to a data field which the user has
//gotten using getmem and adds it to the freeList so that it may be gotten again.
//It also combines contiguous blocks of memory if they are past a certain size threshold

#include <inttypes.h>
#include "mem.h" //function protos
#include "mem_impl.h" //definition of a memNode
#include "externs.h" //external variabls to keep track of stats

void freemem(void * p);
void combineSmallBlocks(memNode * p, memNode * prev);
memNode * findMemorySpot(memNode * p);
void addToFree(memNode * p, memNode * prev);

//Takes in a pointer, and frees the block of memory associated with that pointer.
//Also combines blocks of memory if they are contiguous and larger than a certain threshold 
void freemem(void * p) {
	if (!p) {
		return;
	} 
	memNode* pNode = p - sizeof(memNode);
	printf("pNODE: 0x%08lx %lu\n", (long) pNode, pNode->size);
	printf("0x%08lx\n", (long) root);
	memNode * prev = findMemorySpot(pNode);
	addToFree(pNode, prev);
	totalFree = totalFree + pNode->size + sizeof(memNode);
	nFreeBlocks = nFreeBlocks + 1;
	combineSmallBlocks(pNode, prev);
}

//combines all contiguous blocks into one large block
//takes in the pointer that is being freed and a pointer to to the
//memNode before p.
void combineSmallBlocks(memNode * p, memNode * prev) {
	if (p->next) {
		memNode * pNext = (memNode *) p->next;
		if ((long) p + p->size + sizeof(memNode) - (long) pNext == 0) {
			p->size = p->size + pNext->size + sizeof(memNode);
			if (pNext->next) {
				p->next = pNext->next;
			} else {
				p->next = (uintptr_t) NULL;
			}
			nFreeBlocks = nFreeBlocks - 1;
		}
	}
	if (prev) {
		if ((long) prev + prev->size+sizeof(memNode) - (long) p == 0) {
			prev->size = prev->size + p->size + sizeof(memNode);
			if (p->next) {
				prev->next = p->next;
			} else {
				prev->next = (uintptr_t) NULL;
			}
			nFreeBlocks = nFreeBlocks - 1;
		}
	}
}

//returns a pointer to the data block that appears before the passed in data block in memory
//returns null if p should be added front of free
memNode * findMemorySpot(memNode * p) {
	if (!root || root >= p) {
		return NULL;
	}
	memNode * node = root;
	while (node->next) {
		if ((memNode *) node->next < p) {
			node = (memNode *) node->next;
		} else {
			return node;
		}
	}
	return node;
}

//takes in the memNode being freed and a pointer to the node before p
//adds p to the freelist.
void addToFree(memNode * p, memNode * prev) {
	if (!prev) {
		if (root) {
			uintptr_t temp = (uintptr_t) root;
			printf("0x%08lx\n", (long) temp);
			p->next = temp;
			root = p;
			printf("NOTE: 0x%08lx 0x%08lx \n", (long) root, (long) root->next);

		} else {
			root = p;
		}
	} else if (!prev->next) {
		prev->next = (uintptr_t) p;
	} else {
		uintptr_t temp = prev->next;
		p->next = temp;
		prev->next = (uintptr_t) p;
	}
}

