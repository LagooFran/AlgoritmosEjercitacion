#ifndef MIARBOL_H_INCLUDED
#define MIARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo{
    void *data;
    size_t dataSize;
    struct sNodo *izq;
    struct sNodo *der;
}tNodo;

typedef tNodo *tArbol;

void CrearArbol(tArbol *);
int ArbolVacio(tArbol *);
int InsertarEnArbol(tArbol *, void *, size_t, int (*cmp)(const void*, const void*));
int ArbolLleno(size_t);
void RecorrerEnOrden(tArbol *arbol, void (*mostrar)(const void*));
void RecorrerEnPreOrden(tArbol *arbol, void (*mostrar)(const void*));
void RecorrerEnPosOrden(tArbol *arbol, void (*mostrar)(const void*));

#endif // MIARBOL_H_INCLUDED
