#ifndef _COD_LINEAL_H
#define _COD_LINEAL_H

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

bool decodeFlag = false, verboseFlag = false;

//TODO: esto es temporal, obtener r talvez como argumento y calcular
// las demas variables en funcion de r.
const int r = 3; // paridad
const int n = (1 << r) - 1; // 2^r - 1
const int k = n-r; // 2^r - 1 - r

bool CodificadorLineal(const char*, const char*);
bool DecodificadorLineal(const char*, const char*);

#endif
