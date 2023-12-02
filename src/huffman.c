#include "huffman.h"

void HuffmanCodificador(){}
void HuffmanDecodificador(){}
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
	for(;(ret = fread(&buff, 1, 1, fd) == 1);){
		if(verboseFlag)
			printf("buff = %x\n", buff);
		++freqs[buff];
	}
	fclose(fd);
	// por defecto el nombre del archivo de frecuencias es "freqs.txt"
	FILE* freqsFile = fopen("freqs.txt", "a+");
	if(!freqsFile){
		fprintf(stderr, "Error al crear el archivo de frecuencias\n");
		return false;
	}
	if(verboseFlag)
		printf("\n");
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
-d	El programa se ejecuta en modo de descompresion\n\
-v	El programa escupe mas informacion en la consola\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	// procesamos el archivo para contar los bytes y crear un archivo de frecuencias
	if(!CrearFrecuencias(argv[optind]))
		return EXIT_FAILURE;
	
	if(decompressFlag){
		if(verboseFlag)
			printf("Descompresion\n");
		// TODO: parte decodificadora se hace aqui
		
	}
	else{
		if(verboseFlag)
			printf("Compresion\n");
		// TODO: aqui se hace la parte codificadora, que es la opcion por defecto
	
	}
	
	return EXIT_SUCCESS;
}

