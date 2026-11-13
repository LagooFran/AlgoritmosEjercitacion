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
void Desapilar(tPila *, void *);
void InsertarEnPila(tPila *, void *, size_t);
int PilaVacia(tPila *);




#endif // PILA_H_INCLUDED
