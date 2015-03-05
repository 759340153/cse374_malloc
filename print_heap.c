//
//  print_heap.c
//  hw6
//
//  Created by Max Golub on 2/25/15.
//  Copyright (c) 2015 Max Golub. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "mem_impl.h"
#define ALIGN_VAL 16 //move into mem-impl.h
extern memNode * root; //figure out a way to put this in mem_impl.h

void print_heap(FILE * f);

void print_heap(FILE * f)  {
    if (!f) {
        fprintf(stderr, "Error writing to file!");
        exit(1);
    }
    memNode * currentNode = root;
    while(currentNode) {
        fprintf(f, "0x%08lx 0x%08lx %lu 0x%08lx %lu %lu\n",
                (long) currentNode,
                (long) currentNode->size,
                currentNode->size,
                (long) currentNode->next,
                (uintptr_t) currentNode % ALIGN_VAL,
                currentNode->size % ALIGN_VAL);
        currentNode = (memNode *) currentNode->next;
    }
}
