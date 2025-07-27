#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo{

    void *data;
    size_t dataSize;
    struct sNodo *sig;

}tNodo;

typedef tNodo *tPila;

void CrearPila(tPila *);
int PilaVacia(tPila *);
int InsertarEnPila(tPila *, void *, size_t );
void VerTope(tPila *, void *);
int DesapilarSinLectura(tPila *);



#endif // PILA_H_INCLUDED
