#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>

bool verboseFlag = false;

void HuffmanCodificador();
void HuffmanDecodificador();
bool CrearFrecuencias(const char*);


#endif
