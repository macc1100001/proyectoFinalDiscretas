#ifndef _COD_LINEAL_H
#define _COD_LINEAL_H

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>

bool decodeFlag = false, verboseFlag = false;

bool CodificadorLineal(const char*, char*);
bool DecodificadorLineal(const char*);

#endif
