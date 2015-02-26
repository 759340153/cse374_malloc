//
//  mem_impl.h
//  hw6
//
//  Created by Max Golub on 2/25/15.
//  Copyright (c) 2015 Max Golub. All rights reserved.
//
#include <intypes.h>
#ifndef hw6_mem_impl_h
#define hw6_mem_impl_h

//memNode struct, used to create linked list of free memory
typedef struct mem {
    uintptr_t size;
    uintptr_t next;
    uintptr_t data;
} memNode;

//Globals for interally keeping track of stats
extern int totalFree;
extern int usedMem;
extern int freeMem;

#endif