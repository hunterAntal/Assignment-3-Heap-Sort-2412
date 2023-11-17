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


void MAX_HEAPIFY(struct Heap *h, unsigned int i){
    unsigned int rightChild = i*2 + 1;
    unsigned int leftChild = i*2;
    unsigned int largest = 0;
    
    
    if(leftChild <= h->heapsize && h->arr[leftChild] > h->arr[i]){ // IF LEFT CHILD IS GREATER THEN PARENT
        largest = leftChild;
    }
    else{
        largest = i;
    }
    if(rightChild <= h->heapsize && h->arr[rightChild] > h->arr[largest]){ // IF RIGHT CHILD IS GREATER THEN LARGEST
        largest = rightChild;
    }
    if(largest != i){ // IF PARENT ISN'T LARGEST THEN SWAP THEM
        unsigned long int a,b;
        a = h->arr[i]; // PARENT
        b = h->arr[largest]; // LARGEST NODE
        h->arr[i] = b;
        h->arr[largest] = a;
        MAX_HEAPIFY(h, largest);
    }
}





int main(int argc, const char * argv[]) {
    return 0;
}
