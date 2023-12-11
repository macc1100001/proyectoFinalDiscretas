#include "huffman.h"
#include "heap.h"
#include "nodo.h"

char* Buscar(nodo* padre, unsigned char key, char* temp, char* codificado)
{	
	if (padre == NULL)
		return NULL;
	
	if ( (*(frecuencia*)padre->datos).byte == key && padre->der == NULL && padre->izq == NULL)
			return strcpy(codificado, temp);

	else
	{
		char subcod1[256]={0}, subcod2[256]={0};
		char *aux;
		strcpy(subcod1, temp);
		strcpy(subcod2, temp);

		aux = Buscar(padre->der, key, strncat(subcod1, "1", 2), codificado);
		
		if (aux != NULL)
			return aux;
		else
			return Buscar(padre->izq, key, strncat(subcod2, "0", 2), codificado);
	}
}


nodo* CrearArbol(void)
{
	nodo* cola_prio[256];
	nodo* n;
	//frecuencia freqs_cola[256];
	
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
   	  		freqs_cola[heap_size].num = fr;
   	  		freqs_cola[heap_size].byte = byte;
   	  		//printf("byte: %x %d\n",byte, fr);
			n = crear_nodo(freqs_cola+heap_size);
  			insert(cola_prio, n, &heap_size);
   	  	} 
    }
	fclose(freqsFile);

	/*
	//VISUALIZACION DE LA COLA DE PRIORIDAD
	printf("Max-Heap cola_prio: ");
	printcola_prio(cola_prio, heap_size);
  
  
	  //EXTRACCION DEL PRIMER ELEMENTO
	  nodo* min;
	  int a = heap_size;
	  for (int i = 0; i<a-1; i++)
	  {
		  min = extract_min(cola_prio, &heap_size);
		  printf("After extracting element (%d): ", *((int*)min->datos));
		  printcola_prio(cola_prio, heap_size);
	  }

	  min = extract_min(cola_prio, &heap_size);
	  frecuencia prueba = *(frecuencia*)min->datos;
	  printf("%u\n", prueba.byte);
	  */
	  
	  
	//ALGORITMO DE HUFFMAN
	  
	//int datos_arbol[256];  
	int iterations = heap_size-1; //new variable because heap_size changes dinamically
	for (int i = 0; i<iterations; i++)
	{	
		nodo* z = crear_nodo(NULL);
		z->izq = extract_min(cola_prio, &heap_size);
  		(z->izq)->ant = z;
  		//printf("(IZQ Byte %d)\n", (*(frecuencia*)(z->izq)->datos).byte);
  		
  		z->der = extract_min(cola_prio, &heap_size);
  		(z->der)->ant = z;
  		//printf("(DER Byte %d)\n", (*(frecuencia*)(z->der)->datos).byte);
  		
  		//int x = *(long int*)((z->izq)->datos) + *(long int*)((z->der)->datos);
  		datos_arbol[i] = *(int*)((z->izq)->datos) + *(int*)((z->der)->datos);
  		//printf("%d\n",datos_arbol[i]);
  		
  		z->datos = datos_arbol+i; //HAY QUE PASARLE LA DIRECCION DE UNA VARIABLE (CHECAR DESPUES)
  		
  		//printf("(PADRE byte %d)\n", (*(frecuencia*)z->datos).byte);
  		//printf("(Frec %d)\n", (*(frecuencia*)z->datos).num);
  		//printf("hehe\n");
  		insert(cola_prio, z, &heap_size);
  	}
  	nodo* raiz = extract_min(cola_prio, &heap_size);
  	
  	/*for (int i = 0; i<heap_size; i++)
  	{
  		free_nodo(cola_prio[i], NULL);
  		printf("hola\n");
  	}*/
  	
  	//printf("(Byte %d)\n", (*(frecuencia*)(raiz->der->der->izq)->datos).byte);
  	//printf("(Frec %d)\n", (*(frecuencia*)(raiz->der->der->izq)->datos).num);
  	
  	/*
  	for (unsigned char c = 0; c<255; c++)
	{
		char aux[256] = {0};
		char codificado[256] = {0};
		char* cod = Buscar(raiz, c, aux, codificado);
		printf("EL CODIGO DE %x ES %s\n", c, codificado);
	}
  	
	*/
	
	return raiz;
}

bool HuffmanCodificador(const char* nombreArchivo){
	// TODO: aqui se hace la parte codificadora, que es la opcion por defecto
	// Esta funcion tiene que devolver false, si falla
	// y true al final si todo se ejecuto de manera correcta, como ejemplo 
	// esta la funcion CrearFrecuencias
	
  	
//CODIFICACION
  	
  	nodo* raiz = CrearArbol();
  	
  	//strcpy(codificado, cod);
  	//strncat(cod, codificado, 256);
  	//strncat(cod, codificado, 256);
  	
  	//cadena = (unsigned char *)malloc(filelen*sizeof(char));
  	//int newsize;
  	
  	
  	for (unsigned char c = 0; c<255; c++)
	{
		char aux[256] = {0};
		char codificado[256] = {0};
		char* cod = Buscar(raiz, c, aux, codificado);
		if (cod != NULL)
		{
			int ln = strlen(cod);
			printf("%x es: %s de longitud %d\n", c, cod, ln);
		}
	}
	
	FILE* fd = fopen(nombreArchivo, "r");
	if(!fd){
		fprintf(stderr, "Error al intentar abrir archivo\n");
		return false;
	}
		
	unsigned char* buffer;
	long filelen;
	
	//calcular longitud del archivo
	fseek(fd, 0, SEEK_END);
	filelen = ftell(fd);
	rewind(fd);
	
	buffer = (unsigned char *)calloc(filelen+1,sizeof(char));
	fread(buffer, 1, filelen, fd);
	
	fclose(fd);
	
	
	FILE* comprFILE = fopen("comprimido", "w+");
	if(!comprFILE){
		fprintf(stderr, "Error al crear el archivo de frecuencias\n");
		return false;
	}
	
	//filelen = 2;
	
	char aux[256] = {0};
	char codificado[256] = {0};
	char* all_cods = (char*)calloc(1, sizeof(char));
	int cod_len;
	char* cod;
	
	for (long i = 0; i<filelen; i++)
	{
		cod = Buscar(raiz, buffer[i], aux, codificado);
		//printf("%ld\n",strlen(cod));
		cod_len += strlen(cod);
		all_cods = (char*)realloc(all_cods,cod_len);
		if (cod == NULL)
	  	{
	  		fprintf(stderr, "Error al comprimir el archivo\n");
	  		return false;
	  	}
	  	strncat(all_cods, cod, cod_len);
		//fwrite(cod , 1 , strlen(cod), comprFILE);
		//printf("[%s]\n",cod);
		//printf("%d\n",cod_len);
	}
	
	//printf("(%s)\n",all_cods[all_cods]);
	//printf("%s\n", all_cods);
	//printf("total length in bits %ld\n", strlen(all_cods));
	
	unsigned char byte = 0;
	int x, k;
	
	//strlen(all_cods)
	for (unsigned long int i = 0; i < strlen(all_cods);i+=8)
	{
		k = 0;
		for (unsigned long int j = i; j<i+8; j++)
		{
			x = all_cods[j] - '0';
			//printf("%c, %d, ", cod[j], cod[j]);
			//printf("%d %x\n",x, x);
			byte |= (x&1) << k++;
		}
		//printf("%d %x\n", byte, byte);
		fwrite(&byte, 1, 1, comprFILE);
		byte = 0;
		//printf("%x\n",byte);
		//x = all_cods[i] - '0';
		//printf("%d %x\n", x, x);
	}
	
	//fwrite(cod , 1 , strlen(cod), comprFILE);
	
	free(buffer);

  	fclose(comprFILE);
  	
  	return true;
}

bool HuffmanDecodificador(const char* nombreArchivo){
	// TODO: parte decodificadora se hace aqui
	// Lo mismo que la funcion de arriba, se debe de devolver un booleano
	// indicando si se pudo ejecutar de manera correcta el programa
	//CODIFICACION
  
   	nodo* raiz = CrearArbol();
  	
  	
  	FILE* comprFILE = fopen(nombreArchivo, "r");
	if(!comprFILE){
		fprintf(stderr, "Error al intentar abrir archivo\n");
		return false;
	}
		
	unsigned char* buffer;
	long filelen;

	
	//calcular longitud del archivo
	fseek(comprFILE, 0, SEEK_END);
	filelen = ftell(comprFILE);
	rewind(comprFILE);
	
	buffer = (unsigned char *)calloc(filelen+1,sizeof(char));
	fread(buffer, filelen, 1, comprFILE);
	fclose(comprFILE);
	
	//printf("%s",buffer);
	
	//filelen = 40;

	FILE* descFILE = fopen("descomprimido", "w+");
	if(!descFILE){
		fprintf(stderr, "Error al crear el archivo de frecuencias\n");
		return false;
	}
  		
	nodo* temp;
	unsigned char byte;
	temp = raiz;
	char compara;
	int k;
	//filelen = 10;
	//printf("filelen = %ld\n", filelen);
	//printf("buffer = %x\n", buffer, buffer);
	//unsigned long int t = 0;
	for (unsigned long i = 0; i<filelen; i++)
	{
		//byte |= (x&1) << k++;
		//compara |= (buffer[i]&1) >> k++;
		//printf("%c\n", buffer[i]);
		
		k = 0;
		//int t = 7;
		for ( int j = 0; j<8; j++)
		{
			//t += j;
			//printf("buff = %d %x\n", buffer[j], buffer[j]);
			compara = ( (buffer[i] >> k++)  & 1 );
			
			//printf("%d %x\n", compara, compara);
			
			if (compara == 1)
			{
				temp = temp->der;
				if (temp->der == NULL && temp->izq == NULL)
				{
					byte = (*(frecuencia*)temp->datos).byte;
					//buffer[i] = byte;
					//printf("(Byte 0x%x)\n", byte);
					fwrite(&byte , 1 , 1, descFILE);
					temp = raiz;
				}
			}
			
			else
			{
				if (compara == 0)
				{
					temp = temp->izq;
					if (temp->der == NULL && temp->izq == NULL)
					{
						byte = (*(frecuencia*)temp->datos).byte;
						//buffer[i] = byte;
						//printf("(Byte %d)\n", byte);
						fwrite(&byte , 1 , 1, descFILE);
						temp = raiz;
					}
				}
				
				else
					break;
			}
		
		}
	
	
		//char aux[256] = {0};
		//*char codificado[256] = {0};
		//*cod = Buscar(raiz, buffer[i], aux, codificado);
		//*fwrite(cod , 1 , strlen(cod), comprFILE);
	}
	//printf("t = %ld\n", t);
	
	//fwrite(buffer , 1 , filelen, descFILE);
	
	fclose(descFILE);
	
	free(buffer);
  	return true;
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
		// Aplicamos la compresion Huffman
		if(!HuffmanCodificador(argv[optind]))
			return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

