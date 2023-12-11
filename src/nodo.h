#ifndef _NODO_H
#define _NODO_H   

#include <stdlib.h>
#include <string.h>

typedef struct nodo nodo;

struct nodo{
    nodo *ant, *izq, *der;
    void *datos;
};

nodo* crear_nodo(void*);
void free_nodo(nodo*, void(*free_datos)(void*));

#endif
