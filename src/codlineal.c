#include"codlineal.h"

/*
	TODO: En la descodificacion y correccion de errores
	no se recupera del todo el archivo si el error ocurre endif
	el bit 7 de cada codeword, porque no es parte de ella y no se sabe como interpretarla.
	Idea para solucionarlo, no incluir el bit mas significativo del byte.
*/

/*	
	TODO:
	Construir L, el arreglo que contiene todos los codewords
	por ahora el arreglo es fijo, pero se quiere que este arreglo
	se genere de manera dinamica , utilizando manipulaciones
	de los bits de las filas de H.
	
	Las entradas de L aparecen en orden ascendente,
	correspondiendo con su numero en binario.
	Por ahora, esta hardcodeada...
*/
static unsigned char L[] = { 0, 105, 42, 67,
						 	76, 37, 102, 15,
						 	112, 25, 90, 51,
						 	60, 85, 22, 127 
						 	};

int decodificarDato(int t, int tam){
	for(int i = 0; i < tam; ++i)
		if(L[i] == t)
			return i;
	return -1;
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

/* Inecesaria
void construirH(unsigned char* h, int n, int k){
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

int decodificarNibble(int r, int n, int p){
	#ifdef DEBUG
	printf("Recibido: %d = 0x%x\n", p, p);
	#endif
	int filas[r], res = 0, corregido = 0;
	calcularFilas(filas, r, n);
	for(int i = 0; i < r; ++i){
		#ifdef DEBUG
		printf("%d ", filas[i]);
		printf("peso = %d\n", peso(filas[i] & p) % 2);
		printf("res = %d\n", res);
		#endif
		// multiplicacion por cada fila de la matriz y se suman los 1's
		// Hz' = res
		res |= (peso(filas[i] & p) % 2) << i; // se forma el entero correspondiente al bit a corregir
	}
	if(res){
		if(verboseFlag)
			printf("Hay un error en el bit %d\n", res);
		corregido = p ^ (1 << (n-res));
		if(verboseFlag)
			printf("Corregido = %d\n", corregido);
		int decodificado = decodificarDato(corregido, (r << k));
		if(decodificado == -1)
			return corregido;
		return decodificado;
	}
	if(verboseFlag)
		printf("No errores\n");
	return decodificarDato(p, (r << k));
}

bool CodificadorLineal(const char* nombreArchivoEntrada, const char* nombreArchivoSalida){
	// El archivo que esta funcion saca, siempre se llama "Entrada.bin"
	FILE* archivoEntrada = fopen(nombreArchivoEntrada, "r");
	if(!archivoEntrada){
		fprintf(stderr, "¡Error al intentar abrir el archivo!\n");
		return false;
	}
	// Abrirmos un nuevo archivo en modo escritura
	FILE* archivoSalida = fopen(nombreArchivoSalida, "w+");
	if(!archivoSalida){
		fprintf(stderr, "¡Error al intentar crear el archivo!\n");
		fclose(archivoEntrada);
		return false;
	}
	
	/*	Suponemos que z es un vector que contiene la representacion
		del arbol que reconstruye el archivo que comprimimos con huffman.
		
		Recibimos un mensaje de 4 bits, por lo tanto, n = 7 y necesitamos poder corregir minimo 1 error.
		
	*/
	// Construimos H, la matriz verificadora y construimos los codewords
	// Representamos H mediante la representacion en enteros de sus filas
	// llamando a la funcion calcularFilas, obtenemos la representacion de H
	
	
	if(verboseFlag)
		printf("Enviando %d bits de datos, codificados con %d bits y %d bits de paridad\n", k, n, r);
	
	// leemos el archivo 1 byte a la vez
	unsigned char buff;
	size_t ret;
	while((ret = fread(&buff, 1, 1, archivoEntrada)) == 1){
	
		if(verboseFlag)
			printf("Codificacion:\n");
	
		int parteBaja = (buff & 0x0f);
		int parteAlta = (buff & 0xf0) >> 4;
		
		if(verboseFlag){
			printf("parte baja = %d = 0x%x\n", parteBaja, parteBaja);
			printf("parte alta = %d = 0x%x\n", parteAlta, parteAlta);
		}
		
		int codigo1 = L[parteBaja];
		int codigo2 = L[parteAlta];
		
		if(verboseFlag){
			printf("Codeword 1 = %d = 0x%x\n", codigo1, codigo1);
			printf("Codeword 2 = %d = 0x%x\n", codigo2, codigo2);
		}
		
		int codificado = (codigo2 << 8) | codigo1; // este es el codigo que se escribe en el archivo
		if(verboseFlag)
			printf("codificado = %d = 0x%x\n", codificado, codificado);
		fwrite(&codificado, 1, 2, archivoSalida);
	}
	
	//operaciones de lectura para operar sobre el archivo
	
	fclose(archivoEntrada);
	fclose(archivoSalida);
	return true;
}
bool DecodificadorLineal(const char* nombreArchivoEntrada, const char* nombreArchivoSalida){
	FILE *archivoEntrada = fopen(nombreArchivoEntrada, "r");
	if(!archivoEntrada){
		fprintf(stderr, "¡Error, no se pudo abrir el archivo!\n");
		return false;
	}
	
	FILE *archivoSalida = fopen(nombreArchivoSalida, "w+");
	if(!archivoSalida){
		fprintf(stderr, "¡Error!, no se pudo abrir el archivo\n");
		fclose(archivoEntrada);
		return false;
	}
	
	/*
	Nuestra palabra recibida es el archivo "comprimido" resultante del
	programa huffman. Si le llamamos z a nuestro mensaje recibido
	Los pasos son:
		1. Calcular Hz'
		2. Si Hz' = 0', z es una palabra-codigo
		3. Si Hz' != 0', buscamos la columna h(i) de H tal que,
		Hz' = h(i), y cambiar el i-esimo bit de z.
	*/
	unsigned char buff[2];
	size_t ret;
	while((ret = fread(&buff, 1, 2, archivoEntrada)) > 0){
		if(verboseFlag)
			printf("Decodificando:\n");
			
		//int parteBaja = (buff & 0x00ff);
		//int parteAlta = (buff & 0xff00) >> 8;
		int parteBaja = buff[0];
		int parteAlta = buff[1];
		
		/*
			Se ignora el bit mas significativo de cada byte porque
			solo usamos 7 bits para la codificacion. En caso de que
			el error se introduzca en ese bit.
			
		*/
		int dato1 = decodificarNibble(r, n, parteBaja & ~0x80);
		int dato2 = decodificarNibble(r, n, parteAlta & ~0x80);
		
		int corregido = (dato2 << 4) | dato1;
		if(verboseFlag)
			printf("Corregido final: %d = 0x%x\n", corregido, corregido);
		fwrite(&corregido, 1, 1, archivoSalida);
	}
	
	fclose(archivoEntrada);
	fclose(archivoSalida);
	return true;
}

int main(int argc, char** argv){
	int c;
	char* archivoSalida = "decodificado";
	while((c = getopt(argc, argv, "dvf:")) != -1){
		switch(c){
			case 'v':
				verboseFlag = true;
				break;
			case 'd':
				decodeFlag = true;
				break;
			case 'f':
				archivoSalida = optarg;
			default:
		}
	}
	
	if(!argv[optind]){
		fprintf(stderr,"Uso: %s [OPCIONES] ARCHIVO\n\
El argumento ARCHIVO es el archivo a codificar. \
El programa por defecto funciona en modo codificacion\n\
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
	//return EXIT_SUCCESS;
	#endif
	
	
	if(decodeFlag){
		if(verboseFlag)
			printf("Decodificador\n");
		if(!DecodificadorLineal(argv[optind], archivoSalida))
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
