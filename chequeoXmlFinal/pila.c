#include "pila.h"

void CrearPila(tPila *pila){
    *pila = NULL;
}

int PilaVacia(tPila *pila){
    if(*pila == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int InsertarEnPila(tPila *pila, void *data, size_t dataSize){
    ///inserto el contenido de data dentro de la pila

    tNodo *nuevoNodo;
    void *nuevaData;

    if((nuevoNodo = (tNodo *)malloc(sizeof(tNodo))) == NULL){
        return -1; ///no hay memoria para crear el nodo
    }
    if((nuevaData = malloc(dataSize)) == NULL){
        free(nuevoNodo);
        return -1; ///no hay memoria para crear el nodo
    }

    ///preparo el nuevo nodo
    memcpy(nuevaData, data, dataSize);
    nuevoNodo->data = nuevaData;
    nuevoNodo->dataSize = dataSize;

    ///si hay memoria
    if(PilaVacia(pila)){
        ///si la pila esta vacia asigno el nuevo nodo al principio de la pila con sig = NULL
        nuevoNodo->sig = NULL;
        *pila = nuevoNodo;
        return 0;
    }
    ///si la pila no esta vacia asingo como siguiente el que estaba antes primero
    nuevoNodo->sig = *pila;
    *pila = nuevoNodo;
    return 0;
}

void VerTope(tPila *pila, void *dataDest){
    ///pongo la data del tope de la pila en dataDest
    if(PilaVacia(pila)){
        ///si la pila esta vacia
        return;
    }
    ///si la pila no esta vacia
    memcpy(dataDest, (*pila)->data, (*pila)->dataSize);
}

int DesapilarSinLectura(tPila *pila){
    tNodo *nodoAux;
    ///saco el primer elemento de la pila
    if(PilaVacia(pila)){
        ///si la pila esta vacia
        return 0;
    }
    ///sino..
    nodoAux = (*pila)->sig;
    free((*pila)->data);
    free(*pila);
    *pila = nodoAux;
    return 1;
}
