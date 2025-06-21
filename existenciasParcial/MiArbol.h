#ifndef MIARBOL_H_INCLUDED
#define MIARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///estructura arbol para armar el indice
typedef struct sNodo{
    void *data;
    size_t dataSize;
    struct sNodo *izq;
    struct sNodo *der;
}tNodo;

typedef tNodo *tArbol;

typedef struct{
    int id;
    long offset;
}indice;

int InsertarEnArbol(tArbol *, void *, size_t , int (cmp)(void*, void*));
int ArbolVacio(tArbol *);
void CrearArbol(tArbol *);
void RecorrerInOrden(tArbol *, void (mostrar)(void*));
int BuscarEnArbol(tArbol *, void *, void *, int (cmp)(void*, void*));

#endif // MIARBOL_H_INCLUDED
