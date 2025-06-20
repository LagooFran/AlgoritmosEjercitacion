#ifndef MIPILA_H_INCLUDED
#define MIPILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo2{
    void *data;
    size_t dataSize;
    struct sNodo2 *sig;
}tNodo2;

typedef tNodo2 *tPila;

void DestruirPila(tPila *);
int Desapilar(tPila *, void *);
int Apilar(tPila *, void *, size_t );
int PilaVacia(tPila *);
void CrearPila(tPila *);

#endif // MIPILA_H_INCLUDED
