#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

/*	Construir L, el arreglo que contiene todos los codewords
	por ahora el arreglo es fijo, pero se quiere que este arreglo
	se genere de manera dinamica , utilizando manipulaciones
	de los bits de las filas de H.
	
	Las entradas de L aparecen en orden ascendente,
	correspondiendo con su numero en binario.
*/
static unsigned char L[] = { 0, 105, 42, 67,
						 	76, 37, 102, 15,
						 	112, 25, 90, 51,
						 	60, 85, 22, 127 };

// calcula el valor entero correspondiente a la fila de la matriz H en binario
void calcularFilas(int* numt, int r, int n){
	//int *numt, k;
	int k;
	memset(numt, 0, sizeof(int)*r);
	//numt = calloc(r, sizeof(int));
	for(int j = 0; j < r; ++j){
		k = 0;
		for(int i = n; i > 0; --i)
			numt[j] |= ((i >> j) & 1) << k++;
	}
	//return numt;
}

// calcula el peso w(z) de una palabra z
// en otras palbras, esto cuenta el numero de 1's en la palabra z
unsigned char peso(unsigned char z){
	unsigned char peso = 0, tmp = z;
	while(tmp > 0){
		if(tmp & 1) ++peso;
		tmp = tmp >> 1;
	}
	return peso;
}

int main(int argc, char** argv){
	int r = atoi(argv[1]); // delta
	int n = (1 << r) - 1; // 2^r - 1
	int k = n-r; // 2^r - 1 - r
	int p = atoi(argv[2]); // z, mensaje
	int res = 0;
	//int *filas;
	int filas[r];

	printf("n = %d, k = %d, r = %d\n", n , k, r);
	printf("p = %x\n", p);
	//filas = calcularFilas(r, n);
	calcularFilas(filas, r, n);
	for(int i = 0; i < r; ++i){
		printf("%d ", filas[i]);
		printf("peso = %d\n", peso(filas[i] & p) % 2);
		// multiplicacion por cada fila de la matriz y se suman los 1's
		// Hz' = res
		res |= (peso(filas[i] & p) % 2) << i; // se forma el entero correspondiente al bit a corregir
	}
	printf("res = %d\n", res);
	if(res)
		printf("Corregido = %d\n", p ^ (1 << (n-res)));
	else
		printf("No errores\n");
		
	//free(filas);
	return 0;
}
