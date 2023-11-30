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
	if(verboseFlag)
		printf("\n");
	unsigned int totalBytes = 0;
	for(int i = 0; i < 256; ++i){
		if(verboseFlag)
			printf("%x = %u\n", i, freqs[i]);
		fprintf(freqsFile, "%x %u\n", i, freqs[i]);
		totalBytes += freqs[i];
	}
	fprintf(freqsFile, "total %u\n", totalBytes);
	fclose(freqsFile);
	return true;
}

int main(int argc, char** argv){	
	int c;
	while((c = getopt(argc, argv, "v")) != -1){
		switch(c){
			case 'v':
				verboseFlag = true;
				break;
			default:
				break;
		}
	}
	//if(verboseFlag)
	//	printf("verbose...\n");
		
	if(!argv[optind]){
		fprintf(stderr,"Uso: %s [OPCIONES] ARCHIVO\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	//printf("argumento sin -: %s\n", argv[optind]);
	// procesamos el archivo para contar los bytes y crear un archivo de frecuencias
	if(!CrearFrecuencias(argv[optind])){
		fprintf(stderr, "Error\n");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

