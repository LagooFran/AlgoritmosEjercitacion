#include "MiPila.h"

int CrearPila(tPila *pila){
    *pila = NULL;
    return 0;
}

int PilaVacia(tPila *pila){
    if(*pila == NULL){
        return 1;
    }
    return 0;
}

int PilaLlena(size_t dataSize){
    tNodo *nuevoNodo = malloc(sizeof(tNodo));
    void *nuevaData;
    if(nuevoNodo == NULL){
        return 1;
    }
    else{
        nuevaData = malloc(dataSize);
        if(nuevaData == NULL){
            free(nuevoNodo);
            return 1;
        }
        free(nuevaData);
        free(nuevoNodo);
        return 0;
    }

}

int Apilar(tPila *pila, void *data, size_t dataSize){

    void *nuevaData;
    tNodo *pNuevoNodo;

    if((pNuevoNodo = (tNodo *)malloc(sizeof(tNodo))) == NULL){
        return -1;
    }
    if((nuevaData = malloc(dataSize)) == NULL){
        free(pNuevoNodo);
        return -1;
    }
    memcpy(nuevaData, data, dataSize);
    pNuevoNodo->data = nuevaData;
    pNuevoNodo->dataSize = dataSize;

    if(PilaVacia(pila)){
        pNuevoNodo->sig = NULL;
        *pila = pNuevoNodo;
        return 1;
    }
    else{
        pNuevoNodo->sig = *pila;
        *pila = pNuevoNodo;
        return 1;
    }

}

int DesApilar(tPila *pila, void *dataDest){
    tNodo *auxNodo;

    if(PilaVacia(pila)){
        return -1; ///pila vacia
    }
    else{
        auxNodo = *pila;
        memcpy(dataDest, auxNodo->data, auxNodo->dataSize);
        *pila = auxNodo->sig;
        free(auxNodo->data);
        free(auxNodo);
        return 0;
    }
}
