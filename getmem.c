 //
//  getmem.c
//  hw6
//
//  Created by Max Golub on 2/25/15.
//  Copyright (c) 2015 Max Golub. All rights reserved.
//
#include <inttypes.h>
#include <stdlib.h>
#include "mem_impl.h"
#include "mem.h"

#define SPLIT_SIZE 256 //what size we split a block at
#define LARGE_BLOCK_SIZE 1024 * 16 //size of initial block
#define ALIGN 16
#define maxOveragePercent .20

//funtion protos
memNode * splitBlock(memNode * block, uintptr_t Splitsize); //split a block into many blocks
void removeFromFree(memNode * block); //remove a memnode from the freelist
memNode * mallocData(memNode * block); //give memory to a block
memNode * chooseBlock(memNode * block, uintptr_t size);
//globals
memNode * root;
int totalFree = 0;
int usedMem = 0;
int freeMem = 0;

//grab at least size amount of mem and return a void pointer to the user
void* getmem(uintptr_t size) {
    if (!root) {
        mallocData(root);
    }
    memNode * choosenBlock = chooseBlock(root, size);
    return (void *) &choosenBlock->next+1; //should be start of data
}

//return
memNode * splitBlock(memNode * block, uintptr_t splitSize) {
    int alignment = splitSize % ALIGN;
    if(alignment) {
        splitSize = splitSize + ALIGN - alignment;
    }
    uintptr_t oldSize = block->size;
    block->size = splitSize;
    block->next = (uintptr_t) block+splitSize+2; //maybe want a define for fields?
    memNode newBlock;
    newBlock.size = oldSize - splitSize; // set the new size.
    newBlock.next = (uintptr_t) NULL;
    *(memNode *)(block->next) = newBlock; //lol wat (does this werk?)
    return block; //do we need to return this, or should we figure out a new way
}

memNode * chooseBlock(memNode * block, uintptr_t size) {
    if (block->size < size) { //do we need both? hmmm
        if (block->size) {
           return chooseBlock((memNode *) block->next, size);
        }
        else {
            //also need sto account for if getmem is called on an amount
            //larger than LARGE_BLOCK_SIZE
            return chooseBlock(mallocData(block), size); //errr might need to link things
        }
    }
    else if (root->size > maxOveragePercent*size) {
        return splitBlock(block, size);
    }
    else {
        return block;
    }
}

void removeFromFree(memNode * block) {
    //remove a memNode wheee
}

memNode * mallocData(memNode * block) {
    root = malloc(LARGE_BLOCK_SIZE);
    root->size = LARGE_BLOCK_SIZE-sizeof(root); //should be 16 less
    return root;
}