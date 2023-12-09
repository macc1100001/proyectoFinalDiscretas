#include "heap.h"
#include<stdio.h>
#define parent(i) ( (i - 1) / 2) //minus one because index start in 0 but size cannot be lesser than 2
#define left(i) (2 * i + 1)
#define right(i) (2 * i + 2)

void swap(nodo **a, nodo **b)
{
	nodo* temp = *b;
	
	*b = *a;
	*a = temp;
}

void min_heapify(nodo** A, int i, int size)
{	
	int smallest;
	int l = left(i);
	int r = right(i);
	
	if (l < size && *(int*)A[l]->datos < *(int*)A[i]->datos)
		smallest = l;
	else
		smallest = i;
		
	if (r < size && *(int*)A[r]->datos < *(int*)A[smallest]->datos)
		smallest = r;
		
	if (smallest != i)
	{
		swap(&A[i], &A[smallest]);
		min_heapify(A, smallest, size);
	}
}

nodo* extract_min(nodo** A, int* size)
{
	nodo* min;

	if (*size < 1)
	{
		fprintf(stderr, "heap underflow\n");
		exit(0);
	}
	min = A[0];
	A[0] = A[(*size)-1];
	(*size)--;
	min_heapify(A, 0, *size);

	return min;
}

void insert(nodo** A, nodo* key, int* size)
{		
	if (*size == 0)
	{
		A[0] = key;
		(*size)++;
	}
	else
	{
		int i = (*size)++;
		A[i] = key;
		
		while (i > 0 && *(int*)A[parent(i)]->datos > *(int*)A[i]->datos)
		{		
			swap(&A[i], &A[parent(i)]);
			i = parent(i);
		}
	}
}

//AUXILIAR BORRAR DESPUES (O USARLA PARA VERBOOSE)
void printArray(nodo** array, int size) {
  for (int i = 0; i < size; ++i)
    printf("%d ", *((int*)array[i]->datos));
  printf("\n");
}
