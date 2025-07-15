#ifndef MIARBOL_H_INCLUDED
#define MIARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct sNodo{
    void *data;
    size_t dataSize;
    struct sNodo *izq;
    struct sNodo *der;
}tNodo;

typedef tNodo *tArbol;

void CrearArbol(tArbol *);
int InsertarEnArbol(tArbol *, void *, size_t, int(cmp)(void *, void *));
void RecorrerInOrden(tArbol *, void(mostrar)(void *));
int ContarOcurrenciasNoClave(tArbol *, void *, int cmpdato(void *, void *));
void EspejarArbol(tArbol *);
int CantidadDeNodos(tArbol *);
int AlturaArbol(tArbol *);
int CantidadDeNodosHastaNivel(tArbol *, int);
int EsBalanceado(tArbol *);
void PodarHastaNivel(tArbol *, tArbol *, int, int (cmp)(void *, void *));
int NivelNodo(tArbol *, void *, int (cmp)(void *, void *));

#endif // MIARBOL_H_INCLUDED
