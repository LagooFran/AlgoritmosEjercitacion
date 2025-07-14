#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo{

    void *data;
    size_t dataSize;
    struct sNodo *sig;

}tNodo;

typedef tNodo *tCola;
int InsertarEnCola(tCola *, void *, size_t );
void CrearCola(tCola *);
int CantDeElementosEnCola(tCola *);
void VaciarCola(tCola *);
void SacarElemento(tCola *, void *);
int ColaVacia(tCola *);

#endif // COLA_H_INCLUDED
