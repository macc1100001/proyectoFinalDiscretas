// Priority Queue implementation in C

#include <stdio.h>
#include "heap.h"

// Driver code
int main() {
  int array[10];
  int heap_size = 0;
  
  insert(array, 3, &heap_size);
  insert(array, 4, &heap_size);
  insert(array, 9, &heap_size);
  insert(array, 5, &heap_size);
  insert(array, 2, &heap_size);
  insert(array, 5, &heap_size);
	
  //printf("%d\n", heap_size);
  printf("Max-Heap array: ");
  printArray(array, heap_size);

  int min = extract_min(array, &heap_size);

  /*printf("After extracting element (%d): ", min);
  printArray(array, heap_size);
  
  min = extract_min(array, &heap_size);

  printf("After extracting element (%d): ", min);
  printArray(array, heap_size);
  
  min = extract_min(array, &heap_size);

  printf("After extracting element (%d): ", min);
  printArray(array, heap_size);
  
  min = extract_min(array, &heap_size);

  printf("After extracting element (%d): ", min);
  printArray(array, heap_size);
  
  min = extract_min(array, &heap_size);
  printf("After extracting element (%d): ", min);
  printArray(array, heap_size);
  
   min = extract_min(array, &heap_size);
  printf("After extracting element (%d): ", min);
  printArray(array, heap_size);*/
}
