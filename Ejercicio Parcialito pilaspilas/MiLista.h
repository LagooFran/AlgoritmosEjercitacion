#ifndef MILISTA_H_INCLUDED
#define MILISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo{

    void *data;
    size_t dataSize;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tLista;
int CrearLista(tLista *);
int SacarDelFinal(tLista *, void *);
int PonerAlFinal(tLista *, void *, size_t);


#endif // MILISTA_H_INCLUDED
