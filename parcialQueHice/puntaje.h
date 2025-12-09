#ifndef PUNTAJE_H_INCLUDED
#define PUNTAJE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

typedef struct{
    t_lista tabla;
    unsigned tam;
}t_tabla_puntos;

void crear_tabla_puntos(t_tabla_puntos*, unsigned );
int agregar_puntaje(t_tabla_puntos*, void *);
void imprimir_tabla_puntos(t_tabla_puntos* );
void vaciar_tabla_puntos(t_tabla_puntos* );

#endif // PUNTAJE_H_INCLUDED
