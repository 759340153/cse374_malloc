//
//  print_heap.c
//  hw6
//
//  Created by Max Golub on 2/25/15.
//  Copyright (c) 2015 Max Golub. All rights reserved.
//

#include <stdio.h>
#include "mem_impl.h"
extern memNode * root; //figure out a way to put this in mem_impl.h

void print_heap(FILE * f);

void print_heap(FILE * f)  {
    if (!f) {
        fprintf(stderr, "Error writing to file!");
        exit(1);
    }
    memNode * currentNode = root;
    while(currentNode->next) {
        fprintf(f, "%lu %lu, ", currentNode, currentNode->size);
        currentNode = (memNode *) currentNode->next;
    }
}
