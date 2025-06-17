#ifndef MIPILA_H_INCLUDED
#define MIPILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo{
    void *data;
    size_t dataSize;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tPila;
int CrearPila(tPila *);
int Apilar(tPila *, void *, size_t);
int DesApilar(tPila *, void *);

#endif // MIPILA_H_INCLUDED
