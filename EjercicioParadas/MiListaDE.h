#ifndef MILISTADE_H_INCLUDED
#define MILISTADE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo{
    void *data;
    size_t dataSize;
    struct sNodo *sig;
    struct sNodo *ant;
}tNodo;

typedef tNodo *tListaDE;

void CrearListaDE(tListaDE *);
int ListaVaciaDE(tListaDE *);
int AgregarAlFinal(tListaDE *, void *, size_t);
int AgregarAlInicio(tListaDE *, void *, size_t);
int SacarDelFinal(tListaDE *, void *);
int SacarDelInicio(tListaDE *, void *);
int BuscarNodo(tListaDE *, void *, void *, int (cmp)(void *, void *));
int BuscarNodoYSacar(tListaDE *, void *, void *, int (cmp)(void *, void *));
int InsertarOrdenado(tListaDE *, void *, size_t, int(cmp)(void *, void *));
void DestruirLista(tListaDE *);
int CantidadElementos(tListaDE *);
int CantidadDeApariciones(tListaDE *, void *, int (cmp)(void *, void *));


#endif // MILISTADE_H_INCLUDED
