#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "lista.h"
#include <string.h>

int ListaVacia(lista *l){
    if(*l == NULL){return 1;}
    else{ return 0; }
}

void CrearLista(lista *l){
    *l = NULL;
}

void InsertarAlFinal(lista *l, void *data, size_t dataSize){

    tNodo *lecturaActual=*l, *lecturaAnterior;
    tNodo *nuevoNodo;
    nuevoNodo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevoNodo){
        return;
    }
    void *nuevaData;
    nuevaData = malloc(dataSize);
    if(!nuevaData){
        free(nuevoNodo);
        return;
    }

    nuevoNodo->dataSize = dataSize;
    nuevoNodo->data = nuevaData;
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = NULL;

    if(ListaVacia(l)){
        *l = nuevoNodo;
    }
    else{
        ///recorro hasta el final e inserto
        while(lecturaActual!=NULL){
            lecturaAnterior = lecturaActual;
            lecturaActual = lecturaActual->sig;
        }

        nuevoNodo->ant = lecturaAnterior;
        lecturaAnterior->sig = nuevoNodo;

    }
}

void ExtraerUltimo(lista *l, void *dataSalida){
    tNodo *nodoActual = *l;
    tNodo *nodoAnterior;
    if(ListaVacia(l)){
        return;
    }
    if(nodoActual->ant == NULL && nodoActual->sig == NULL){
        memcpy(dataSalida, nodoActual->data, nodoActual->dataSize);
        free(nodoActual->data);
        free(nodoActual);
        *l = NULL;
    }
    else{
        while(nodoActual != NULL){
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->sig;
        }
        nodoActual = nodoAnterior;
        nodoAnterior = nodoActual->ant;
        memcpy(dataSalida, nodoAnterior->data, nodoAnterior->dataSize);
        free(nodoActual->data);
        free(nodoActual);
        nodoAnterior->sig = NULL;
    }
}

void VaciarLista(lista *l){
    tNodo *nodoActual = *l;
    tNodo *sig;
    while(nodoActual != NULL){
        free(nodoActual->data);
        sig = nodoActual->sig;
        free(nodoActual);
        nodoActual = sig;
    }
    *l = NULL;
}
