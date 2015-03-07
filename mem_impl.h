//
//  mem_impl.h
//
// Internal implementation of the memNode structure.
//
//  hw6
//
//  Created by Max Golub and Alex Gingras on 2/25/15.
//
#include <inttypes.h>
#ifndef hw6_mem_impl_h
#define hw6_mem_impl_h

//memNode struct, used to create linked list of free memory
typedef struct mem {
    uintptr_t size;
    uintptr_t next;
} memNode;

#endif
