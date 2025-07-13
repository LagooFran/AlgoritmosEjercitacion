#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
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
int InsertarEnArbol(tArbol *, void *, size_t, int(cmp)(void *, void *));
void RecorrerEnOrden(tArbol *, void (mostrar)(void *));
int EliminarElemento(tArbol *, void *, int (cmp)(void *, void *));
void VaciarArbol(tArbol *);
tArbol *BuscarRegistroPorClave(tArbol *, void *,  int (cmp)(void *, void *));

#endif // ARBOL_H_INCLUDED
