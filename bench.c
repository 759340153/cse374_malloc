//
//  bench.c
//  hw6
//
//  Created by Max Golub on 2/25/15.
//  Copyright (c) 2015 Max Golub. All rights reserved.
//

#include <stdio.h>
#include "mem.h"
#include "mem_impl.h"
#include <unistd.h> //command line parsing
//small and large block limits
#define def_ntrial 10000
#define def_pctget 50
#define def_pctlarge 10
#define def_small_limit 200
#define def_large_limit 20000

extern memNode * root;

//function prototypes
int getRandom(int size); //reads from urandom for size
void runRandomOp(); //run ethier a getmem or freemem op
void freeRandom(int allocs[], int * size); //free a random block


int main(int argc, const char * argv[]) {
    // run the main memory testing code
    //create a array of ntrial size to keep track of allocs
    //as well as inc numbe rof allocs
    int ntrials = 0;
    int pctget = 0;
    int pctlarge = 0;
    int small_limit = 0;
    int large_limit = 0;
    int random_seed = 0;
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
    return 0;
    ntrials = ntrials ? ntrials : def_ntrial;
    printf("%d", ntrials);
}

int getRandom(int size) {
    return 0;
}

void runRandomOp() {
    //do something random
}


void freeRandom(int allocs[], int * size) {
    //do something like freeing. But random!
}