//
//  bench.c
//  hw6 CSE 374
//
//  Runs a benchmark program agaisnt our freemem and getmem implementations.
//  Usage : bench [ntrials [pctget [pctlarge [small_limit [large_limit [random_seed ]]]]]]
//  ntrials : Number of trials to run, default 10000
//  pctget : percetage of total freemem/getmem calls that go to getmem, default 50
//  pctlarge : percetage of total getmems that are large blocks. default 10
//  small_limit : largest small block, default 200
//  large_limit : largest large block, default 20000
//  random_seed : Random seed for use with rand() default is pulled from urandom
//
//  Created by Max Golub and Alex Gingras on 2/25/15.
//  Copyright (c) 2015 Max Golub. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

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
int runRandomOp(uintptr_t * usedBlocks, int numberOfGottenBlocks);
void getRandom(uintptr_t *usedBlocks, int numberOfGottenBlocks);
void freeRandom(uintptr_t * usedBlocks, int numberOfGottenBlocks);
void printData(uintptr_t totalSize, uintptr_t totalFree, uintptr_t nFreeBlocks);

//Command line argument globals
int ntrials = 0;
int pctget = -1;
int pctlarge = -1;
int small_limit = -1;
int large_limit = -1;
int random_seed = 0;

/*
 Main program, which parses arguments passed in by the user and
 then calls a for loop to run ntraisl worth of tests on freemem and getmem.
 */
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
    printf("%d\n", argc);
    //set the arguments to default if they are not currently set.
    ntrials = ntrials ? ntrials : def_ntrial;
    pctget = pctget != -1 ? pctget : def_pctget;
    pctlarge = pctlarge != -1 ? pctlarge : def_pctlarge;
    small_limit = small_limit != -1 ? small_limit : def_small_limit;
    large_limit = large_limit != -1 ? large_limit : def_large_limit;
    char data[randomSize];
    random_seed = random_seed ? random_seed : getRandomSeed(data);
    uintptr_t *usedBlocks = (uintptr_t *) malloc(sizeof(uintptr_t)*ntrials);
    uintptr_t totalSize;
    uintptr_t totalFree;
    uintptr_t nFreeBlocks;
    int numberOfGottenBlocks = 0;
    srand(random_seed); //setup random seed
    for (int i = 0; i < ntrials; i++) {
        numberOfGottenBlocks = runRandomOp(usedBlocks, numberOfGottenBlocks);
        if (ntrials > 10) {
            if (i % (ntrials/10) == 0) {
                get_mem_stats(&totalSize, &totalFree, &nFreeBlocks);
                printData(totalSize, totalFree, nFreeBlocks);
            }
        }
        //if ntrials is less than 10, print out the stats per run
        else {
            get_mem_stats(&totalSize, &totalFree, &nFreeBlocks);
            printData(totalSize, totalFree, nFreeBlocks);
        }
    }
    return 0;
}

/*
 Open up /dev/urandom and get an ints worth of random data from it.
 */
int getRandomSeed(char * data) {
    FILE *fp;
    fp = fopen("/dev/urandom", "r");
    fread(&data, 1, randomSize, fp);
    fclose(fp);
    printf("%d", (int) data);
    return (int) data;
}

/*
 Run a random operation, either free or get mem.
 */
int runRandomOp(uintptr_t * usedBlocks, int numberOfGottenBlocks) {
    int ran = rand() % 100;
    if (ran >= pctget) {
        freeRandom(usedBlocks, numberOfGottenBlocks);
		if(numberOfGottenBlocks > 0) {
			return numberOfGottenBlocks - 1;
		} else {
			return numberOfGottenBlocks;
		}
    }
    else {
        getRandom(usedBlocks, numberOfGottenBlocks);
		return numberOfGottenBlocks + 1;
    }
}

/*
 get a random amount of data based on the percentage pctlarge and
 the large and small limits.
 */
void getRandom(uintptr_t *usedBlocks, int numberOfGottenBlocks) {
    uintptr_t num;
    if(rand() % 100 >= pctlarge) {
        num = (rand() % small_limit) + 1;
    }
    else {
        num = (rand()%(large_limit-small_limit))+small_limit;
    }
    usedBlocks[numberOfGottenBlocks] = (uintptr_t) getmem(num);  //seg fault
}
/*
 Free a random block by selecting usedBlocks[randomnumber] and attempting
 to call freemem on that pointer.
 */
void freeRandom(uintptr_t * usedBlocks, int numberOfGottenBlocks) {
	if (numberOfGottenBlocks > 0) {
        int index = rand() % numberOfGottenBlocks;
        uintptr_t nodeAtlastIndex = usedBlocks[numberOfGottenBlocks - 1];
        freemem((void *)usedBlocks[index]);
        usedBlocks[index] = nodeAtlastIndex;
    }
}

/*
 Prints information to stdout
 */
void printData(uintptr_t totalSize, uintptr_t totalFree, uintptr_t nFreeBlocks){
    printf("Total size: %lu, total free: %lu, free blocks: %lu\n",
           totalSize, totalFree, nFreeBlocks);
    
}