#include "cola.h"

void CrearCola(tCola *cola){
    *cola = NULL;
}

int ColaVacia(tCola *cola){
    if(*cola == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int InsertarEnCola(tCola *cola, void *data, size_t dataSize){

    tNodo *nodoActual = *cola;
    tNodo *nodoAnterior = *cola;
    tNodo *nuevoNodo;
    void *nuevaData;

    if((nuevoNodo = (tNodo *)malloc(sizeof(tNodo))) == NULL){
        return -1; ///no hay espacio
    }
    if((nuevaData = malloc(dataSize)) == NULL){
        free(nuevoNodo);
        return -1; ///no hay espacio
    }

    nuevoNodo->sig = NULL;
    nuevoNodo->dataSize = dataSize;
    memcpy(nuevaData, data, dataSize);
    nuevoNodo->data = nuevaData;

    if(ColaVacia(cola)){
        ///si la cola esta vacia inserto primer elemento
        *cola = nuevoNodo;
        return 1;
    }
    else{
        ///si ya hay elementos en la cola.
        while(nodoActual != NULL){
            ///voy hasta el final
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->sig;
        }
        ///inserto al final
        nodoAnterior->sig = nuevoNodo;
        return 1;
    }

    free(nuevoNodo);
    free(nuevaData);
    return -2; ///error no definido
}

int CantDeElementosEnCola(tCola *cola){
    int cont = 0;
    while(*cola != NULL){
        cont++;
        cola = &(*cola)->sig;
    }
    return cont;
}

void VaciarCola(tCola *cola){
    tCola *aux;
    while(*cola != NULL){
        aux = &(*cola)->sig;
        free((*cola)->data);
        free(*cola);
        *cola = NULL;
        cola = aux;
    }
}

void SacarElemento(tCola *cola, void *dataDest){
    tNodo *nodoAux;

    if(ColaVacia(cola)){
        return;
    }
    else{
        nodoAux = (*cola)->sig;
        memcpy(dataDest, (*cola)->data, (*cola)->dataSize);
        free((*cola)->data);
        free(*cola);
        if(nodoAux!= NULL){
            *cola = nodoAux;
        }
        else{
            *cola = NULL;
        }
    }
}
