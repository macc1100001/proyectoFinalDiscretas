#include "huffman.h"
#include "heap.h"
#include "nodo.h"

char* Buscar(nodo* padre, unsigned char key, char* codificado)
{	
	if (padre == NULL)
		return NULL;
	
	if ( (*(frecuencia*)padre->datos).byte == key)
		{//return codificado;
		printf("Byte %d == KEY %d\n", (*(frecuencia*)padre->datos).byte, key);
		return "HEO";
		}
	else
	{
		char subcod[256];
		char *is_null;
		strcpy(subcod, codificado);
	
		is_null = Buscar(padre->der, key, codificado);
		
		if (is_null != NULL)
			return Buscar(padre->der, key, strncat(subcod, "1", 2));
		else
			return Buscar(padre->izq, key, strncat(subcod, "0", 2));
	}
	
	/*while (padre->der != NULL)
	{
		strncat(codificado, "1", 2);
	}	*/
}

bool CrearArbol(void)
{
	nodo* array[256];
	nodo* n;
	frecuencia freqs[256];
	
	FILE* freqsFile = fopen("freqs.txt", "r");
	if(!freqsFile){
		fprintf(stderr, "Error al leer el archivo de frecuencias\n");
		return false;
	}
	
	int heap_size = 0, fr;
	unsigned int byte;
   
  	while (fscanf(freqsFile, "%x %u", &byte, &fr) == 2)
  	{
   		if (fr>0)
   	  	{
   	  		freqs[heap_size].num = fr;
   	  		freqs[heap_size].byte = byte;
   	  		printf("byte: %d\n",byte);
			n = crear_nodo(freqs+heap_size);
  			insert(array, n, &heap_size);
   	  	} 
    }
	fclose(freqsFile);

	/*
	//VISUALIZACION DE LA COLA DE PRIORIDAD
	printf("Max-Heap array: ");
	printArray(array, heap_size);
  
  
	  //EXTRACCION DEL PRIMER ELEMENTO
	  nodo* min;
	  int a = heap_size;
	  for (int i = 0; i<a-1; i++)
	  {
		  min = extract_min(array, &heap_size);
		  printf("After extracting element (%d): ", *((int*)min->datos));
		  printArray(array, heap_size);
	  }

	  min = extract_min(array, &heap_size);
	  frecuencia prueba = *(frecuencia*)min->datos;
	  printf("%u\n", prueba.byte);
	  */
	  
	  
	//ALGORITMO DE HUFFMAN
	  
	int variables[256];  
	int iterations = heap_size-1; //new variable because heap_size changes dinamically
	for (int i = 0; i<iterations; i++)
	{	
		nodo* z = crear_nodo(NULL);
		z->izq = extract_min(array, &heap_size);
  		(z->izq)->ant = z;
  		//printf("(IZQ Byte %d)\n", (*(frecuencia*)(z->izq)->datos).byte);
  		//if (z->izq == NULL)
  		
  		z->der = extract_min(array, &heap_size);
  		(z->der)->ant = z;
  		//printf("(DER Byte %d)\n", (*(frecuencia*)(z->der)->datos).byte);
  		
  		//int x = *(long int*)((z->izq)->datos) + *(long int*)((z->der)->datos);
  		variables[i] = *(int*)((z->izq)->datos) + *(int*)((z->der)->datos);
  		printf("%d\n",variables[i]);
  		
  		z->datos = variables+i; //HAY QUE PASARLE LA DIRECCION DE UNA VARIABLE (CHECAR DESPUES)
  		
  		printf("(PADRE byte %d)\n", (*(frecuencia*)z->datos).byte);
  		//printf("(Frec %d)\n", (*(frecuencia*)z->datos).num);
  		//printf("hehe\n");
  		insert(array, z, &heap_size);
  	}
  	nodo* raiz = extract_min(array, &heap_size);
  	
  	//BUSQUEDA, O SEA, CODIFICACION
  	
  	unsigned char key = 1; //ejemplo
  	char codificado[256] = {0};
  	printf("EL CODIGO DE %x ES: ", key);
  	printf("%s\n", Buscar(raiz, key, codificado));
  	
  	strncat(codificado, "1", 2);
  	strncat(codificado, "", 2);
  	printf("%s\n", codificado);
  	
  	/*unsigned char key = 32 //ejemplo
  	while(n_vis->der!=NULL || n_vis->izq!=NULL)
  	{
  		
  	}*/
  	
  	printArray(array, heap_size);
  
  
  for (int i = 0; i<heap_size; i++)
  {
  	free_nodo(array[i], NULL);
  }
  
		
	return true;
}

bool HuffmanCodificador(const char* nombreArchivo){
	// TODO: aqui se hace la parte codificadora, que es la opcion por defecto
	// Esta funcion tiene que devolver false, si falla
	// y true al final si todo se ejecuto de manera correcta, como ejemplo 
	// esta la funcion CrearFrecuencias
	
}

bool HuffmanDecodificador(const char* nombreArchivo){
	// TODO: parte decodificadora se hace aqui
	// Lo mismo que la funcion de arriba, se debe de devolver un booleano
	// indicando si se pudo ejecutar de manera correcta el programa
}

bool CrearFrecuencias(const char* nombreArchivo){
	FILE* fd = fopen(nombreArchivo, "r");
	if(!fd){
		fprintf(stderr, "Error al intentar abrir archivo\n");
		return false;
	}
	unsigned int freqs[256] = {0};
	unsigned char buff;
	size_t ret;
	// contamos todos los caracteres
	while((ret = fread(&buff, 1, 1, fd)) == 1)
		++freqs[buff];
	fclose(fd);
	// por defecto el nombre del archivo de frecuencias es "freqs.txt"
	FILE* freqsFile = fopen("freqs.txt", "w+");
	if(!freqsFile){
		fprintf(stderr, "Error al crear el archivo de frecuencias\n");
		return false;
	}
	// contamos el numero total de bytes
	unsigned int totalBytes = 0;
	for(int i = 0; i < 256; ++i){
		if(verboseFlag)
			printf("%x = %u\n", i, freqs[i]);
		fprintf(freqsFile, "%x %u\n", i, freqs[i]);
		totalBytes += freqs[i];
	}
	if(verboseFlag)
		printf("total %u\n", totalBytes);
	fprintf(freqsFile, "total %u\n", totalBytes);
	fclose(freqsFile);
	return true;
}

int main(int argc, char** argv){	
	int c;
	while((c = getopt(argc, argv, "dv")) != -1){
		switch(c){
			case 'v':
				verboseFlag = true;
				break;
			case 'd':
				decompressFlag = true;
				break;
			default:
		}
	}
		
	if(!argv[optind]){
		fprintf(stderr,"Uso: %s [OPCIONES] ARCHIVO\n\
El argumento ARCHIVO es el archivo a comprimir. \
El programa por defecto funciona en modo compresion\n\
Opciones:\n\
-d	El programa se ejecuta en modo de descompresion. \
En este caso el argumento ARCHIVO es el nombre del archivo a descomprimir.\n\
-v	El programa escupe mas informacion en la consola\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	
	if(decompressFlag){
		if(verboseFlag)
			printf("Descompresion\n");
		// Aplicamos la compresion Huffman
		if(!HuffmanDecodificador(argv[optind]))
			return EXIT_FAILURE;
	}
	else{
		if(verboseFlag)
			printf("Compresion\n");
		// Solamente creamos el archivo de frecuencias si el programa
		// se ejecuta en modo compresion
		// procesamos el archivo para contar los bytes y crear un archivo de frecuencias
		if(!CrearFrecuencias(argv[optind]))
			return EXIT_FAILURE;
		if (!CrearArbol())
			return EXIT_FAILURE;
		// Aplicamos la compresion Huffman
		if(!HuffmanCodificador(argv[optind]))
			return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

