#include "puntaje.h"


void crear_tabla_puntos(t_tabla_puntos* p, unsigned tam){
    p->tam = tam;
    t_lista listaPtos;
    CrearLista(&listaPtos);

    p->tabla = listaPtos;
}


int agregar_puntaje(t_tabla_puntos* p, void *data){
    AgregarOrdenadoConLimite(&p->tabla, data, p->tam, sizeof(t_puntaje));
    return 1;
}


void imprimir_tabla_puntos(t_tabla_puntos* p){
    t_nodo *leido = p->tabla;
    t_puntaje pLeido;
    t_puntaje *pPLeido = &pLeido;

    while(leido != NULL){
        memcpy(pPLeido, leido->data, sizeof(t_puntaje));
        printf("Puntaje: %s, %d\n\n", pPLeido->iniciales, pPLeido->puntaje);
        leido = leido->sig;
    }
}

void vaciar_tabla_puntos(t_tabla_puntos* p);
