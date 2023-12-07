#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include<unistd.h>

int* calcularFilas(int r, int n){
	int *numt, k;
	numt = calloc(r, sizeof(int));
	for(int j = 0; j < r; ++j){
		k = 0;
		for(int i = n; i > 0; --i){
			numt[j] |= ((i >> j) & 1) << k++;
		}
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
	int r = atoi(argv[1]);
	int n = atoi(argv[2]);
	int p = atoi(argv[3]);
	int res = 0;
	int *filas;

	printf("n = %d, r = %d\n", n , r);
	printf("p = %x\n", p);
	filas = calcularFilas(r, n);
	for(int i = 0; i < r; ++i){
		printf("%d ", filas[i]);
		printf("peso = %d\n", peso(filas[i] & p) % 2);
		res |= (peso(filas[i] & p) % 2) << i;
	}
	printf("res = %d\n", res);
	if(res)
		printf("Corregido = %x\n", p ^ (1 << (n-res)));
	else
		printf("No errores\n");
	free(filas);
	return 0;
}
