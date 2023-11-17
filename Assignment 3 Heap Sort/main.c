//
//  main.c
//  Assignment 3 Heap Sort
//
//  Created by Hunter Antal on 2023-11-17.
//

#include <stdio.h>


struct Heap{
    unsigned long *arr;
    unsigned int heapsize, length;
};

// FIND RIGHT CHILD NODE PASS BY REFERANCE
void RightChild(unsigned int *node){
    *node = (*node*2) + 1; //MULTILPY BY 2 AND ADD 1 TO FIND RIGHT CHILD
}

void MAX_HEAPIFY(struct Heap *h, unsigned int i){
    RightChild(&i); // PASS NODE TO FIND RIGHT CHILD
}





int main(int argc, const char * argv[]) {
    return 0;
}
