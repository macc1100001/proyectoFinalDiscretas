#include"codlineal.h"

unsigned char peso(unsigned char a){
	unsigned char peso = 0, tmp = a;
	while(tmp > 0){
		if(tmp & 1) ++peso;
		tmp = tmp >> 1;
	}
	return peso;
}

/*void construirH(unsigned char* h, int n, int k){
	for(int i = 0; i < n; ++i){
		h[i] = i+1;
	}
}
*/

// calcula el valor entero correspondiente a la fila de la matriz H en binario
void calcularFilas(int* numt, int r, int n){
	int k;
	memset(numt, 0, sizeof(int)*r);
	for(int j = 0; j < r; ++j){
		k = 0;
		for(int i = n; i > 0; --i)
			numt[j] |= ((i >> j) & 1) << k++;
	}
}

bool CodificadorLineal(const char* nombreArchivoEntrada, char* nombreArchivoSalida){
	//TODO: Aqui la parte de codificacion
	// El archivo que esta funcion saca, siempre se llama "Entrada.bin"
	FILE* archivoEntrada = fopen(nombreArchivoEntrada, "r");
	if(!archivoEntrada){
		fprintf(stderr, "¡Error al intentar abrir el archivo!\n");
		return false;
	}
	/*	Suponemos que z es un vector que contiene la representacion
		del arbol que reconstruye el archivo que comprimimos con huffman.
		
		Recibimos un mensaje de 8 bits, por lo tanto, n = 8+8 y necesitamos poder corregir minimo 1 error.
		Necesitamos que delta >= 3.
	*/
	// Construimos H, la matriz verificadora y construimos los codewords
	
	//operaciones de lectura para operar sobre el archivo
	
	// Abrirmos un nuevo archivo en modo escritura
	FILE* archivoSalida = fopen(nombreArchivoSalida, "w+");
	if(!archivoSalida){
		fprintf(stderr, "¡Error al intentar crear el archivo!\n");
		return false;
	}
	
	//operaciones de escritura para operar sobre el archivo de salida
	
	fclose(archivoEntrada);
	fclose(archivoSalida);
	return true;
	
}
bool DecodificadorLineal(const char* nombreArchivoEntrada){
	//TODO: Aqui la parte de decodificacion
		/*
		Nuestra palabra recibida es el archivo "comprimido" resultante del
		programa huffman. Si le llamamos z a nuestro mensaje recibido
		Los pasos son:
			1. Calcular Hz'
			2. Si Hz' = 0', z es una palabra-codigo
			3. Si Hz' != 0', buscamos la columna h(i) de H tal que,
			Hz' = h(i), y cambiar el i-esimo bit de z.
		
	*/
}

int main(int argc, char** argv){
	int c;
	while((c = getopt(argc, argv, "dv")) != -1){
		switch(c){
			case 'v':
				verboseFlag = true;
				break;
			case 'd':
				decodeFlag = true;
				break;
			default:
		}
	}
	
	if(!argv[optind]){
		fprintf(stderr,"Uso: %s [OPCIONES] ARCHIVO\n\
Opciones:\n\
-d	El programa se ejecuta en modo de decodificacion\n\
-v	El programa escupe mas informacion en la consola\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	char* nombreArchivoSalida = "Entrada.bin";
	
	#ifdef DEBUG
	printf("peso de %d: %d\n", 3, peso(3));
	printf("peso de %d: %d\n", 4, peso(4));
	printf("peso de %d: %d\n", 5, peso(5));
	printf("peso de %d: %d\n", 7, peso(7));
	printf("peso de %d: %d\n", 8, peso(8));
	printf("peso de %d: %d\n", 252, peso(252));
	return EXIT_SUCCESS;
	
	#endif
	
	if(decodeFlag){
		if(verboseFlag)
			printf("Decodificador\n");
		if(!DecodificadorLineal(argv[optind]))
			return EXIT_FAILURE;
	}
	else{
		if(verboseFlag)	
			printf("Codificador\n");
		// la salida del codificador es un archivo "Entrada.bin"
		if(!CodificadorLineal(argv[optind], nombreArchivoSalida))
			return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
