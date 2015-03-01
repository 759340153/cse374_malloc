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
#define LARGE_BLOCK_SIZE 1024 * 16//size of initial block
//sizes to split into
#define LARGE_BUCKET 128
#define MED_BUCKET 64
#define SMALL_BUCKET 32
#define maxOveragePercent .20

//funtion protos
memNode * splitBlock(memNode * block, int Splitsize); //split a block into many blocks
//int checkBlockSize(memNode * block, uintptr_t size); //check if a block is over SPLIT_SIZE
void removeFromFree(memNode * block); //remove a memnode from the freelist
uintptr_t mallocData(memNode * block); //give memory to a block
memNode * chooseBlock(memNode * block, uintptr_t size);

//grab at least size amount of mem and return a void pointer to the user
void* getmem(uintptr_t size) {
    if (root) {
        mallocData(root);
    }
    memNode * choosenBlock = chooseBlock(root, size);
    return (void *) &choosenBlock->next+1; //should be start of data
    //if (root->size > maxOveragePercent*size) {
    //    splitBlock(<#memNode *block#>, <#int splitSize#>)
    //}
}

//return
memNode * splitBlock(memNode * block, int splitSize) {
    //something splitty.
    return NULL;
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

uintptr_t mallocData(memNode * block) {
    root = malloc(LARGE_BLOCK_SIZE);
    root->size = LARGE_BLOCK_SIZE-sizeof(root); //should be 16 less
    return root;
}