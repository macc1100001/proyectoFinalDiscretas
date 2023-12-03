#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>

bool verboseFlag = false, decompressFlag = false;

void HuffmanCodificador(const char*);
void HuffmanDecodificador(const char*);
bool CrearFrecuencias(const char*);


#endif
