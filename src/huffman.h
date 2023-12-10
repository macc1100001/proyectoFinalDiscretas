#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include "nodo.h"

typedef struct frecuencia frecuencia;
struct frecuencia{
    int num;
    unsigned char byte;
};

bool verboseFlag = false, decompressFlag = false;

char* Buscar(nodo* padre, unsigned char key, char* codificado);
bool CrearArbol(void);
bool HuffmanCodificador(const char*);
bool HuffmanDecodificador(const char*);
bool CrearFrecuencias(const char*);


#endif
