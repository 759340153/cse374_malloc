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
void removeBlock(memNode *block, memNode *prevBlock);
uintptr_t align16(uintptr_t num);

//globals
memNode * root;
//used for get stats
int totalSize = 0;
int totalFree = 0;
int nFreeBlocks = 0;

/*
 gives a user at least size amount of memory to work with as a void pointer.
 If size is 0 or less than 0, then the method will return null.
 */
void* getmem(uintptr_t size) {
    if (size > 0) {
        if (!root) {
            root = mallocData(root, LARGE_BLOCK_SIZE);
            nFreeBlocks += 1;
        }
        memNode * choosenBlock = chooseBlock(root, NULL, size);
        nFreeBlocks -= 1;
        totalFree -= choosenBlock-> size;
        return (void *) choosenBlock+sizeof(memNode); //should be start of data
    }
    else {
        return NULL;
    }
}

/*
 Split a block into a block the size of splitsize and a block with 
 the remaining amount of space. returns the newley split block, which
 should be linked into the freelist.
 */
memNode * splitBlock(memNode * block, uintptr_t splitSize) {
    splitSize = align16(splitSize);
    uintptr_t oldSize = block->size;
    uintptr_t oldBlockNext = block->next;
    block->size = splitSize;
    block->next = (uintptr_t) block+splitSize+sizeof(memNode);
    memNode newBlock;
    newBlock.size = oldSize-splitSize-sizeof(memNode); // set the new size.
    newBlock.next = oldBlockNext;
    //set the value of the next to newBlock
    *(memNode *)(block->next) = newBlock;
    nFreeBlocks += 1;
    totalFree -= sizeof(memNode);
    return block;
}

/*
 Remove a block from the free list if there is a preceding block.
 If there is not a preceding block, the block is the root block
 and we need to set the root node to the blocks next pointer.
 */
void removeBlock(memNode *block, memNode *prevBlock) {
    if (prevBlock) {
        prevBlock->next = block->next; //remove block from linked list
    }
    else {
        root = (memNode *) block->next; //block->next points to not free memory
    }
}

/*
 Choose a block from the free list, creating a new node/root node as required.
 Called recursivley, this will search for a block that is above the user 
 spec'd size and split that block if required. Finally, the block is returned
 to getmem after being removed from the freelist.
 */
memNode * chooseBlock(memNode * block, memNode * prevBlock, uintptr_t size) {
    if (block->size < size) {
        if (block->next) {
           return chooseBlock((memNode *) block->next, block, size);
        }
        else {
            memNode * newBlock = mallocData((memNode *)block->next, size);
            block->next = (uintptr_t) newBlock; //link the new block
            return chooseBlock(newBlock, block ,size);
        }
    }
    else if (block->size > size + maxOveragePercent*size && block->size > size + (16 - size % 16) + 16) {
        block = splitBlock(block, size);
    }
    removeBlock(block, prevBlock);
	block->next = (uintptr_t) NULL;
    return block;
}

/*
 Align a number to a number divisible by 16.
 Returns 16 if the number is less than 16.
 */
uintptr_t align16(uintptr_t num) {
    int alignment = num % ALIGN_VAL;
    if(num < ALIGN_VAL) {
        num = ALIGN_VAL;
    }
    else if (alignment) {
        num = num + ALIGN_VAL - alignment;
    }
    return num;
}

/*
 Malloc data for a new node object. Aligns the call beforehand,
 to insure that the block gets the same size as malloc.
 */
memNode * mallocData(memNode * block, uintptr_t size) {
    //although malloc does this, the exact size will not be known
    size = align16(size);
    block = malloc(size+sizeof(memNode));
    block->size = size;
    totalSize += size;
    totalFree += size;
    nFreeBlocks += 1;
    return block;
}