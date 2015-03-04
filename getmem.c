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

#define ALIGN_VAL 16
#define SPLIT_SIZE 256 //what size we split a block at
#define LARGE_BLOCK_SIZE 1024 * 16 //size of initial block
#define maxOveragePercent .20

//funtion protos
memNode * splitBlock(memNode * block, uintptr_t Splitsize); //split a block into many blocks
void removeFromFree(memNode * block); //remove a memnode from the freelist
memNode * mallocData(memNode * block, uintptr_t size); //give memory to a block
memNode * chooseBlock(memNode * block, memNode * prevBlock, uintptr_t size);
//globals
memNode * root;

int totalFree = 0;
int usedMem = 0;
int freeMem = 0;

//grab at least size amount of mem and return a void pointer to the user
void* getmem(uintptr_t size) {
    if (!root) {
        root = mallocData(root, NULL);
        print_heap(stdout);
        //current = root;
    }
    memNode * choosenBlock = chooseBlock(root, NULL, size);
    return (void *) &choosenBlock->next+1; //should be start of data
}

//return
memNode * splitBlock(memNode * block, uintptr_t splitSize) {
    int alignment = splitSize % ALIGN_VAL;
    if(alignment) {
        splitSize = splitSize + ALIGN_VAL - alignment;
    }
    else if (splitSize < ALIGN_VAL) {
        splitSize = ALIGN_VAL;
    }
    uintptr_t oldSize = block->size;
    block->size = splitSize;
    block->next = (uintptr_t) block+splitSize+sizeof(memNode); //maybe want a define for fields?
    memNode newBlock;
    newBlock.size = oldSize-splitSize-sizeof(memNode); // set the new size.
    newBlock.next = (uintptr_t) NULL;
    *(memNode *)(block->next) = newBlock; //lol wat (does this werk?)
    print_heap(stdout);
    return block; //do we need to return this, or should we figure out a new way
}

memNode * chooseBlock(memNode * block, memNode * prevBlock, uintptr_t size) {
    if (block->size < size) {
        if (block->size) {
           return chooseBlock((memNode *) block->next, block, size);
        }
        else {
            //also needs to account for if getmem is called on an amount
            //larger than LARGE_BLOCK_SIZE
            return chooseBlock(mallocData(block, size), NULL ,size); //errr might need to link things
        }
    }
    else if (root->size > maxOveragePercent*size) {
        splitBlock(block, size);
    }
    if (prevBlock) {
        prevBlock->next = block->next; //remove block from linked list
    }
    else {
        root = (memNode *) block->next;
    }
    return block;
}

void removeFromFree(memNode * block) {
    //remove a memNode wheee
}

memNode * mallocData(memNode * block, uintptr_t size) {
    if (size > LARGE_BLOCK_SIZE) {
        block = malloc(size);
        block->size = LARGE_BLOCK_SIZE-sizeof(memNode);
    }
    else {
        block = malloc(LARGE_BLOCK_SIZE);
        block->size = LARGE_BLOCK_SIZE-sizeof(memNode); //should be 16 less
    }
    printf("%d \n ", LARGE_BLOCK_SIZE);
    return block;
}