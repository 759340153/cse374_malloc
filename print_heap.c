//
//  print_heap.c
//  hw6
//
//  Prints out a representation of the heap, with the currentNode,
//  the size value of the current node, and then the decimal representation
//  of the size, the next node after current node, and then the alignment
//  of those nodes.
//
//  Created by Max Golub and Alex Gingras on 2/25/15.
//

#include <stdio.h>
#include <stdlib.h>
#include "mem_impl.h"
#define ALIGN_VAL 16 //move into mem-impl.h
extern memNode * root; //figure out a way to put this in mem_impl.h
//function prototype
void print_heap(FILE * f);

/*
 Prints a representation of the heap to a file, which could be 
 stdout, stderr, or a normal file. The format is specified above. 
 The funciton assumes f is already open. 
 */
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
