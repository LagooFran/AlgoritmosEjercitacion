#ifndef MILISTA_H_INCLUDED
#define MILISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo2{

    void *data;
    size_t dataSize;
    struct sNodo2 *sig;
}tNodo2;

typedef tNodo2 *tLista;


void CrearLista(tLista *lista);
int ListaVacia(tLista *lista);
int AgregarAlFinal(tLista *lista, void *data, size_t dataSize);
int SacarDelFinal(tLista *lista, void *dataDest);
void DestruirLista(tLista *lista);
void InsertarSinDuplicados(tLista *, void *, size_t , int cmp(void*, void*), void acumular(void *, void *));
void InsertarSinDuplicadosOrdenado(tLista *, void *, size_t , int cmp(void*, void*), void acumular(void *, void *));

#endif // MILISTA_H_INCLUDED
