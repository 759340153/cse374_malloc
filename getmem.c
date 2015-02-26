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
#define LARGE_BLOCK_SIZE 1024 //size of initial block
//sizes to split into
#define LARGE_BUCKET 128
#define MED_BUCKET 64
#define SMALL_BUCKET 32

//funtion protos
memNode * splitBlock(memNode * block, int Splitsize); //split a block into many blocks
int checkBlockToBig(memNode * block); //check if a block is over SPLIT_SIZE
void removeFromFree(memNode * block); //remove a memnode from the freelist
uintptr_t mallocData(memNode * block); //give memory to a block

//grab at least size amount of mem and return a void pointer to the user
void* getmem(uintptr_t size) {
    return NULL;
}

//return
memNode * splitBlock(memNode * block, int splitSize) {
    //something splitty.
    return NULL;
}

int checkBlockToBig (memNode * block) {
    if (block->size > SPLIT_SIZE) {
        return 1;
    }
    else {
        return 0;
    }
}

void removeFromFree(memNode * block) {
    //remove a memNode wheee
}

uintptr_t mallocData(memNode * block) {
    block->data = (uintptr_t) malloc(block->size); //something like this
    return block->data ; //or something like that
}