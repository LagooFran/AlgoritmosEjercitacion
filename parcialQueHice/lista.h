#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char iniciales[4];
    unsigned puntaje;
}t_puntaje;


typedef struct s_nodo{
    void *data;
    size_t tam;
    struct s_nodo *sig;
}t_nodo;

typedef t_nodo *t_lista;

void CrearLista(t_lista *);
int ListaVacia(t_lista *l);
void AgregarOrdenadoConLimite(t_lista *, void *, int , size_t);
int CantidadDeElementos(t_lista *l);


#endif // LISTA_H_INCLUDED
