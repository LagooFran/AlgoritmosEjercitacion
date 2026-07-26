#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"


void CrearLista(lista *l){
    *l = NULL;
}

int ListaVacia(lista *l){
    if(*l == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void AgregarAlFinal(lista *l, void *data, size_t dataSize){
    tNodo *pNuevoNodo;
    void *pNuevaData;
    tNodo *nodoRecorrer = *l;

    pNuevaData = malloc(dataSize);
    if(!pNuevaData){
        //error de memoria
        return;
    }
    pNuevoNodo = (tNodo *)malloc(sizeof(tNodo));
    if(!pNuevoNodo){
        //error de memoria
        free(pNuevaData);
        return;
    }
    memcpy(pNuevaData, data, dataSize);
    //pongo los datos en el nuevo nodo
    pNuevoNodo->ant = NULL;
    pNuevoNodo->sig = NULL;
    pNuevoNodo->data = pNuevaData;
    pNuevoNodo->dataSize = dataSize;
    //una vez creado el nodo me fijo donde guardarlo
    if(ListaVacia(l)){
        *l = pNuevoNodo;
    }
    else{
        while(nodoRecorrer->sig != NULL){
            nodoRecorrer = nodoRecorrer->sig;
        }
        //cuando llego al final agrego el nodo que quiero
        pNuevoNodo->ant = nodoRecorrer;
        nodoRecorrer->sig = pNuevoNodo;
    }

}

void MostrarLista(lista *l, void (*mostrar)(void *)){
    tNodo *nodoRecorrer = *l;
        while(nodoRecorrer != NULL){
            mostrar(nodoRecorrer->data);
            nodoRecorrer = nodoRecorrer->sig;
        }
}

void BorrarLista(lista *l){
    tNodo *nodoRecorrer = *l;
    tNodo *siguiente;
        while(nodoRecorrer != NULL){
            siguiente = nodoRecorrer->sig;
            free(nodoRecorrer->data);
            free(nodoRecorrer);
            nodoRecorrer = siguiente;
        }
    *l = NULL;
}

int CantidadElementos(lista *l){
    tNodo *nodoRecorrer = *l;
    int cant=0;
    while(nodoRecorrer != NULL){
        cant++;
        nodoRecorrer = nodoRecorrer->sig;
    }
    return cant;
}

void BorrarUltimoElemento(lista *l){
    tNodo *nodoRecorrer = *l;
    tNodo *nodoAnterior;
    if(ListaVacia(l)){
        return;
    }
    if(CantidadElementos(l) == 1){
        //unico elemento en lista
        free(nodoRecorrer->data);
        free(nodoRecorrer);
        *l = NULL;
    }
    else{
     while(nodoRecorrer->sig != NULL){
            nodoAnterior = nodoRecorrer;
            nodoRecorrer = nodoRecorrer->sig;
        }
        free(nodoRecorrer->data);
        free(nodoRecorrer);
        nodoAnterior->sig = NULL;
    }

}
