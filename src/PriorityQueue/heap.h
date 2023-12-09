#ifndef _HEAP_H
#define _HEAP_H   

#include <stdlib.h>
#include <string.h>

void min_heapify(int A[], int i, int size);
int extract_min(int A[], int* size);
void insert(int A[], int key, int* size);
void decrease_key(int A[], int i, int key);
void printArray(int array[], int size);

#endif
