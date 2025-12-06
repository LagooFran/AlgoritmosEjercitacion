#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo{

    void *data;
    size_t datasize;
    struct sNodo *sig;

}tNodo;

typedef tNodo *tLista;

typedef struct{
    int base;
    int potencia;
}termino;


void CrearLista(tLista *);
void AgregarTerminoOrd(tLista *, void *, size_t);
int ListaVacia(tLista *);

#endif // LISTA_H_INCLUDED
