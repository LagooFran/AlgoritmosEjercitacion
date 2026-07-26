#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo{
    void *data;
    size_t dataSize;
    struct sNodo *ant;
    struct sNodo *sig;
}tNodo;

typedef tNodo *lista;
void CrearLista(lista *);
int ListaVacia(lista *);
void AgregarAlFinal(lista *, void *, size_t);
void MostrarLista(lista *, void (*mostrar)(void *));
void BorrarLista(lista *);
void BorrarUltimoElemento(lista *l);
int CantidadElementos(lista *);
#endif // LISTA_H_INCLUDED
