#include "pila.h"

void CrearPila(tPila *pila){
    *pila = NULL;
}

int PilaVacia(tPila *pila){
    if(*pila == NULL){
        return 1;
    }
    return 0;
}

void InsertarEnPila(tPila *pila, void *data, size_t dataSize){

    tNodo *pNuevoNodo = (tNodo *)malloc(sizeof(tNodo));
    tNodo *nodoActual = *pila;
    if(pNuevoNodo == NULL){
        printf("Error de memoria");
        return;
    }
    void *nuevaData = malloc(dataSize);
    if(nuevaData == NULL){
        printf("Error de memoria");
        free(pNuevoNodo);
        return;
    }

    memcpy(nuevaData, data, dataSize);
    pNuevoNodo->data = nuevaData;
    pNuevoNodo->dataSize = dataSize;
    pNuevoNodo->sig = NULL;

    if(PilaVacia(pila)){
        *pila = pNuevoNodo;
    }
    else{
        pNuevoNodo->sig = nodoActual;
        *pila = pNuevoNodo;
    }
}

void Desapilar(tPila *pila, void *bufferSalida){

    tNodo *nodoActual = *pila;
    if(PilaVacia(pila)){
        return;
    }

    memcpy(bufferSalida, nodoActual->data, nodoActual->dataSize);
    if(nodoActual->sig == NULL){
        free(nodoActual->data);
        free(nodoActual);
        *pila = NULL;
    }
    else{
        *pila = nodoActual->sig;
        free(nodoActual->data);
        free(nodoActual);
    }
}

void VaciarPila(tPila *pila){

    tNodo *nodoActual = *pila;
    tNodo *nodoAnterior = *pila;

    while(nodoActual != NULL){
        nodoAnterior = nodoActual;
        nodoActual = nodoAnterior->sig;
        free(nodoAnterior->data);
        free(nodoAnterior);
    }

    *pila = NULL;
}



