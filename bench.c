//
//  bench.c
//  hw6
//
//  Created by Max Golub on 2/25/15.
//  Copyright (c) 2015 Max Golub. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include <unistd.h> //command line parsing
//small and large block limits
#define def_ntrial 10000
#define def_pctget 50
#define def_pctlarge 10
#define def_small_limit 200
#define def_large_limit 20000
#define randomSize 4

extern memNode * root;

//function prototypes
int getRandomSeed(); //reads from /dev/urandom for size
void runRandomOp(); //run ethier a getmem or freemem op
void freeRandom(int allocs[], int * size); //free a random block
//Command line argument globals
int ntrials = 0;
int pctget = 0;
int pctlarge = 0;
int small_limit = 0;
int large_limit = 0;
int random_seed = 0;

int main(int argc, const char * argv[]) {
    // run the main memory testing code
    //create a array of ntrial size to keep track of allocs
    //as well as inc numbe rof allocs
    switch(argc) {
        case 7:
            random_seed = atoi(argv[6]);
        case 6:
            large_limit = atoi(argv[5]);
        case 5:
            small_limit = atoi(argv[4]);
        case 4:
            pctlarge = atoi(argv[3]);
        case 3:
            pctget = atoi(argv[2]);
        case 2:
            ntrials = atoi(argv[1]);
    }
    ntrials = ntrials ? ntrials : def_ntrial;
    pctget = pctget ? pctget : def_pctget;
    pctlarge = pctlarge ? pctlarge : def_pctlarge;
    small_limit = small_limit ? small_limit : def_small_limit;
    large_limit = large_limit ? large_limit : def_large_limit;
    random_seed = random_seed ? random_seed : getRandomSeed();
    uintptr_t *usedBlocks;
    usedBlocks = (uintptr_t *) malloc(sizeof(uintptr_t)*ntrials);
    srand(random_seed); //setup random seed
    for (int i = 0; i < ntrials; i++) {
        runRandomOp(usedBlocks);
    }
    return 0;
}

int getRandomSeed() {
    char data[randomSize];
    FILE *fp;
    fp = fopen("/dev/urandom", "r");
    fread(&data, 1, randomSize, fp);
    fclose(fp);
    return (int) data;
}

void runRandomOp(uintptr_t usedBlocks) {
    if (rand() % 100 > pctget) {
        freeRandom(usedBlocks);
    }
    else {
        getRandom(usedBlocks);
    }
}

void freeRandom(uintptr_t usedBlocks) {
    
}