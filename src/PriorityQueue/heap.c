#include "heap.h"
#include<stdio.h>
#define parent(i) ( (i - 1) / 2) //minus one because index start in 0
#define left(i) (2 * i + 1)
#define right(i) (2 * i + 2)


void swap(int *a, int *b) 
{
  int temp = *b;
  *b = *a;
  *a = temp;
}

void min_heapify(int A[], int i, int size)
{	
	int smallest;
	int l = left(i);
	int r = right(i);
	
	if (l < size && A[l] < A[i])
		smallest = l;
	else
		smallest = i;
		
	if (r < size && A[r] < A[smallest])
		smallest = r;
		
	if (smallest != i)
	{
		swap(&A[i], &A[smallest]);
		min_heapify(A, smallest, size);
	}
}

int extract_min(int A[], int* size)
{
	int max;

	if (*size < 1)
	{
		fprintf(stderr, "heap underflow\n");
		exit(0);
	}
	max = A[0];
	A[0] = A[(*size)-1];
	(*size)--;
	min_heapify(A, 0, *size);

	return max;
}

void insert(int A[], int key, int* size)
{	
	//printf("%d\n", *size);
	//int* size = &heap_size;	
	
	if (*size == 0)
	{
		A[0] = key;
		*size = (*size)+1;
	}
	else
	{
		//*size = (*size)+1;
		A[*size] = -1;
		decrease_key(A, (*size)++, key);
	}
	
}


void decrease_key(int A[], int i, int key)
{	
	if (key < A[i])
	{
		fprintf(stderr, "new key is smaller than current key\n");
		exit(0);
	}
	A[i] = key;
	//printf("i: %d \t", i);
	//printf("key: %d\n", key);
	//printf("(%d, %d)\n", A[parent(i)],A[i]);
	while (i > 0 && A[parent(i)] > A[i])
	{	
		//printf("swap\n");
		swap(&A[i], &A[parent(i)]);
		i = parent(i);
	}

}

//AUXILIAR BORRAR DESPUES
void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i)
    printf("%d ", array[i]);
  printf("\n");
}
