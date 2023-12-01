#include"codlineal.h"

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
	
	if(decodeFlag){
		if(verboseFlag)
			printf("Decodificador\n");
		//TODO: Aqui la parte de decodificacion
	}
	else{
		if(verboseFlag)	
			printf("Codificador\n");
		//TODO: Aqui la parte de codificacion
		// la salida del codificador es un archivo "Entrada.bin"
	}
	
	return EXIT_SUCCESS;
}
