#include "MiPila.h"

void CrearPila(tPila *pila){
    *pila = NULL;
}

int PilaVacia(tPila *pila){
    if(*pila == NULL){
        return 1;
    }
    return 0;
}

int Apilar(tPila *pila, void *data, size_t dataSize){

    tNodo2 *nuevoNodo;
    void *nuevaData;

    if((nuevoNodo = (tNodo2*)malloc(sizeof(tNodo2))) == NULL){
        return -1; ///malloc fallido
    }
    if((nuevaData = malloc(dataSize)) == NULL){
        free(nuevoNodo);
        return -1; ///malloc fallido
    }

    memcpy(nuevaData, data, dataSize);
    nuevoNodo->data = nuevaData;
    nuevoNodo->dataSize = dataSize;

    if(PilaVacia(pila)){
        nuevoNodo->sig = NULL;
        *pila = nuevoNodo;
        return 0;
    }
    else{
        nuevoNodo->sig = *pila;
        *pila = nuevoNodo;
        return 0;
    }

}

int Desapilar(tPila *pila, void *dataDest){

    tNodo2 *nodoActual = *pila;
    tNodo2 *nodoSiguiente;

    if(PilaVacia(pila)){
        return -1; ///la pila esta vacia
    }

    memcpy(dataDest, nodoActual->data, nodoActual->dataSize);
    nodoSiguiente = nodoActual->sig;
    free(nodoActual->data);
    free(nodoActual);
    nodoActual = NULL;
    *pila = nodoSiguiente;
    return 0;

}

void DestruirPila(tPila *pila){

    tNodo2 *nodoActual = *pila;
    tNodo2 *nodoSiguiente;

    while(nodoActual != NULL){
        nodoSiguiente = nodoActual->sig;
        free(nodoActual->data);
        free(nodoActual);
        nodoActual = NULL;
        nodoActual = nodoSiguiente;
    }

    *pila = NULL;
}

