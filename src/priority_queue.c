// IMPLEMENTACION DE LA COLA DE PRIORIDAD. ESTE ES UN ARCHIVO DE PRUEBA ------- QUITAR DESPUES

#include <stdio.h>
#include "heap.h"

// DRIVER CODE
int main() {
  
  //ELEMENTOS DE LA COLA DE PRIORIDAD
  nodo* array[5];
  nodo* n;
  int heap_size = 0;
  	
  //VALORES DE EJEMPLO PARA INSERTAR EN LA COLA
  int queue_values[5] = {3,4,9,5,2};
  
  
  //INSERCCION DE ELEMENTOS EN LA COLA DE PRIORIDAD
  for (int i = 0; i<5; i++)
  {
  	n = crear_nodo(queue_values+i);
  	insert(array, n, &heap_size);
  }
  
  //VISUALIZACION DE LA COLA DE PRIORIDAD
  printf("Max-Heap array: ");
  printArray(array, heap_size);
  

  //EXTRACCION DEL PRIMER ELEMENTO
  nodo* min = extract_min(array, &heap_size);
  printf("After extracting element (%d): ", *((int*)min->datos));
  printArray(array, heap_size);

  //EXTRACCION DEL SEGUNDO ELEMENTO
  min = extract_min(array, &heap_size);
  printf("After extracting element (%d): ", *((int*)min->datos));
  printArray(array, heap_size);
  
  //NOTA IMPORTANTE, ES RESPONSABILIDAD DEL MODULO QUE EXTRAE LOS NODOS (i.e., HUFFMAN) LIBERAR LA MEMORIA DE ESTOS
  
  //LIBERACION DE MEMORIA DINAMICA DE LOS ELEMENTOS QUE HAYAN QUEDADO EN LA COLA
  for (int i = 0; i<heap_size; i++)
  {
  	free_nodo(array[i], NULL);
  }
}
