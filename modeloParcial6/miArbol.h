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
void RecorrerInOrden(tArbol *, void (mostrar)(void *));
int InsertarEnArbol(tArbol *, void *, size_t, int(cmp)(void *, void *));
int ArbolVacio(tArbol *);
void CrearArbol(tArbol *);
void Diferencia(tArbol *, tArbol *, int (cmp)(void *, void *),  void (mostrar)(void *));

#endif // MIARBOL_H_INCLUDED
