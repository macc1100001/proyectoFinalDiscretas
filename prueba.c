#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include<unistd.h>

// calcula el valor entero correspondiente a la fila de la matriz H en binario
int* calcularFilas(int r, int n){
	int *numt, k;
	numt = calloc(r, sizeof(int));
	for(int j = 0; j < r; ++j){
		k = 0;
		for(int i = n; i > 0; --i)
			numt[j] |= ((i >> j) & 1) << k++;
	}
	return numt;
}

unsigned char peso(unsigned char a){
	unsigned char peso = 0, tmp = a;
	while(tmp > 0){
		if(tmp & 1) ++peso;
		tmp = tmp >> 1;
	}
	return peso;
}

int main(int argc, char** argv){
	int r = atoi(argv[1]); // delta
	//int n = atoi(argv[2]);
	int n = (1 << r) - 1; // 2^r - 1
	int k = n-r; // 2^r - 1 - r
	int p = atoi(argv[2]); // z, mensaje
	int res = 0;
	int *filas;

	printf("n = %d, k = %d, r = %d\n", n , k, r);
	printf("p = %x\n", p);
	filas = calcularFilas(r, n);
	for(int i = 0; i < r; ++i){
		printf("%d ", filas[i]);
		printf("peso = %d\n", peso(filas[i] & p) % 2);
		// multiplicacion por cada fila de la matriz y se suman los 1's
		// Hz' = res
		res |= (peso(filas[i] & p) % 2) << i; // se forma el entero correspondiente al bit a corregir
	}
	printf("res = %d\n", res);
	if(res)
		printf("Corregido = %x\n", p ^ (1 << (n-res)));
	else
		printf("No errores\n");
	free(filas);
	return 0;
}
