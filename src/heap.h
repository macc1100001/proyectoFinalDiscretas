#ifndef _HEAP_H
#define _HEAP_H   

#include <stdlib.h>
#include "nodo.h"

void min_heapify(nodo** A, int i, int size);
nodo* extract_min(nodo** A, int* size);
void insert(nodo** A, nodo* key, int* size);
void printArray(nodo** array, int size);

#endif
