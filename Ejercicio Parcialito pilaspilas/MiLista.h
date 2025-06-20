#ifndef MILISTA_H_INCLUDED
#define MILISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MiPila.h"

typedef struct sNodo{

    void *data;
    size_t dataSize;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tLista;


void CrearLista(tLista *lista);
int ListaVacia(tLista *lista);
int AgregarAlFinal(tLista *lista, void *data, size_t dataSize);
int SacarDelFinal(tLista *lista, void *dataDest);
void DestruirLista(tLista *lista);


#endif // MILISTA_H_INCLUDED
