//
//  main.c
//  Assignment 3 Heap Sort
//
//  Created by Hunter Antal on 2023-11-17.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


struct Heap{
    unsigned long *arr;
    unsigned int heapsize, length;
};

void swap(unsigned long int *a, unsigned long int *b) { // SWAPS TWO ELEMENTS OF AN ARRAY
    unsigned long int temp = *a;
    *a = *b;
    *b = temp;
}


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
        swap(&h->arr[i], &h->arr[largest]);
        MAX_HEAPIFY(h, largest);
    }
}


void Build_Max_Heap(struct Heap *h){
    h->heapsize = h->length; // SET HEAPSIZE TO LENGTH
    
    for(unsigned int i = (h->length/2); i >= 1; i--){ // ITERATE THROUGH TREE
        MAX_HEAPIFY(h, i);
    }
}


void Heap_Sort(struct Heap *h){ // SORTS AN ARRAY IN PLACE
    Build_Max_Heap(h);
    
    for(unsigned int i = h->length; i >= 2; i--){
        swap(&h->arr[1], &h->arr[i]);
        h->heapsize--;
        MAX_HEAPIFY(h, 1);
    }
}


void insertion_sort(unsigned long *arr, unsigned int length) {
    unsigned long temporaryVal;

    // goes through the array
    for (int i = 1; i < length + 1; i++) {
        // checks through the partial sorted list to see if current value hits in anywhere
        for (int k = 0; k < i; k++) {
            if (arr[i] < arr[k]) {

                // moves all values up as needed and places the new value into its correct posistion
                temporaryVal = arr[i];
                for (int l = i-1; l >= k; l--) {
                    if (l != k) {
                        arr[l + 1] = arr[l];
                    }
                    else {
                        arr[l] = temporaryVal;
                    }
                }
            }
        }
    }
    return;
}

void merge(unsigned long *a, unsigned long left, unsigned long mid, unsigned long right) {
    unsigned long n1 = mid - left + 1;
    unsigned long n2 = right - mid;
    unsigned long leftarr[n1], rightarr[n2]; // THIS LIKE THROWS AN ERROR WHEN SIZE = 2^20
    for (unsigned long i = 0; i < n1; i++) {
        leftarr[i] = a[left + i]; // SHOULD THIS BE [LEFT + i] NOT [LEFT + 1]?
    }
    for (unsigned long i = 0; i < n2; i++) {
        rightarr[i] = a[mid + 1 + i];
    }

    unsigned long i = 0, j = 0;
    unsigned long k = left;
    while (i < n1 && j < n2) {
        if (leftarr[i] <= rightarr[j]) {
            a[k] = leftarr[i];
            i++;
        }
        else {
            a[k] = rightarr[j];
            j++;
        }
        k++;
    }
    while (i < n1) { //SHOULD IT BE (i < n1) NOT (i < n2)?
        a[k] = leftarr[i];
        i++;
        k++;
    }
    while (j < n2) {
        a[k] = rightarr[j];
        j++;
        k++;
    }
}

void merge_sort(unsigned long *a, unsigned long left, unsigned long right) {

    // implementatio of merge sort following the lectures 7-9 slideshow
    if (left < right) {
        unsigned long mid = left+(right-left)/2;
        merge_sort(a, left, mid);
        merge_sort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}


int main(int argc, const char * argv[]) {

    int SIZE = (int) pow(2,20);

    // opens csv file called "data.csv"
    FILE *file;
    file = fopen("data.csv", "w");

    if (file == NULL) {
        printf("ERROR cant open file\n");
        return 0;
    }

    // initialising each array
    unsigned long *f = malloc(sizeof(unsigned long) * SIZE);
    unsigned long *g = malloc(sizeof(unsigned long) * SIZE);
    struct Heap *h = malloc(sizeof(struct Heap));
    
    // CHECK MEMORY ALLOCATION
    if (!h) {
        printf("\nMemory Allocation for h Faild\n");
        return 0;
    }
    if (!f) {
        printf("\nMemory Allocation for f Faild\n");
        return 0;
    }
    if (!g) {
        printf("\nMemory Allocation for g Faild\n");
        return 0;
    }
    
    h->arr = malloc(sizeof(unsigned long) * (SIZE+1)); // (SIZE+1) BEACUSE 1-BASED INDEXING

    // loading random values into the array
    unsigned long temp;
    for (unsigned long int i=1; i <= SIZE; i++) {
        temp = rand()%__INT16_MAX__;
        f[i] = (unsigned long) temp;
        g[i] = (unsigned long) temp;
        h->arr[i] = (unsigned long) temp;
    }

    // putting the times ran into another array (0 for heap, 1 for insertion, 2 for merge)
    double *times = malloc(sizeof(double) * 3);
    if (!times) {
        printf("\nMemory Allocation for times Faild\n");
        return 0;
    }
    
    
    // TESTCASE ----
    // Test case for Heap Sort
    unsigned long testArray[] = {5, 3, 8, 4, 1, 9, 7, 2, 27, 18, 50, 100, 0};
    unsigned int testSize = sizeof(testArray) / sizeof(testArray[0]);

    // Allocate memory for the heap and set the test array
    struct Heap *testHeap = malloc(sizeof(struct Heap));
    testHeap->arr = malloc(sizeof(unsigned long) * (testSize + 1));
    testHeap->length = testSize;
    testHeap->heapsize = testSize;

    // Copy the test array to the heap's array, starting from index 1
    for (unsigned int i = 1; i <= testSize; i++) {
        testHeap->arr[i] = testArray[i - 1];
    }

    // Print the array before sorting
    printf("Before Heap Sort: ");
    for (unsigned int i = 1; i <= testSize; i++) {
        printf("%lu ", testHeap->arr[i]);
    }
    printf("\n");

    // Perform Heap Sort
    Heap_Sort(testHeap);

    // Print the array after sorting
    printf("After Heap Sort: ");
    for (unsigned int i = 1; i <= testSize; i++) {
        printf("%lu ", testHeap->arr[i]);
    }
    printf("\n");

    // Free the memory
    free(testHeap->arr);
    free(testHeap);
    // TESTCASE ENDS ----
    
    // WRITE HEADERS
    fprintf(file, "Insertion Sort, Merge Sort, Heap Sort\n");
    
    // TIME MEASUREMENTS
    double t1 =  clock();
    insertion_sort(f, SIZE);
    times[0] = (double) (clock() - t1) / CLOCKS_PER_SEC;

    t1 = clock();
    merge_sort(g, 0, SIZE - 1);
    times[1] = (double) (clock() - t1) / CLOCKS_PER_SEC;

    t1 = clock();
    Heap_Sort(h);
    times[2] = (double) (clock() - t1) / CLOCKS_PER_SEC;

    // printing results into csv file "data.csv"
    fprintf(file, "%f, %f, %f",times[0], times[1], times[2]);

    // close csv file "data.csv"
    fclose(file);
    file = 0;
    
    // AVOIDING MEMORY LEAKS
    free(f);
    free(g);
    free(h->arr);
    free(h);
    free(times);
    
    return 0;
}
