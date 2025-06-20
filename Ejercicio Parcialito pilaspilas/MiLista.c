#include "MiLista.h"
#include "MiPila.h"

void CrearLista(tLista *lista){
    *lista = NULL;
}

int ListaVacia(tLista *lista){

    if(*lista == NULL){
        return 1;
    }
    return 0;
}


int AgregarAlFinal(tLista *lista, void *data, size_t dataSize){

    tNodo *nodoActual = *lista;
    tNodo *nuevoNodo;
    void *nuevaData;

    if((nuevoNodo = (tNodo*)malloc(sizeof(tNodo))) == NULL){
        return -1; ///malloc fallido
    }
    if((nuevaData = malloc(dataSize)) == NULL){
        free(nuevoNodo);
        return -1; ///malloc fallido
    }

    memcpy(nuevaData, data, dataSize);
    nuevoNodo->data = nuevaData;
    nuevoNodo->dataSize = dataSize;
    nuevoNodo->sig = NULL;

    if(ListaVacia(lista)){
        *lista = nuevoNodo;
        return 0;
    }
    else{
        while(nodoActual->sig != NULL){
            nodoActual = nodoActual->sig; ///voy hasta el ultimo nodo
        }
        nodoActual->sig = nuevoNodo;
        return 0;
    }

}

int SacarDelFinal(tLista *lista, void *dataDest){
    tNodo *nodoActual = *lista;
    tNodo *nodoAnterior = NULL;

    if(ListaVacia(lista)){
        return -1; ///lista vacia no hay nodos que sacar
    }
    else{
        while(nodoActual->sig != NULL){
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->sig; ///voy hasta el ultimo nodo
        }

        memcpy(dataDest, nodoActual->data, nodoActual->dataSize);
        free(nodoActual->data);
        free(nodoActual);
        if(nodoAnterior != NULL){
            nodoAnterior->sig = NULL;
        }
        else{
            *lista = NULL;
        }
        return 0;
    }
}

void DestruirLista(tLista *lista){

    tNodo *nodoActual = *lista;
    tNodo *nodoSiguiente;

    while(nodoActual != NULL){
        nodoSiguiente = nodoActual->sig;
        free(nodoActual->data);
        free(nodoActual);
        nodoActual = nodoSiguiente;
    }

    *lista = NULL;

}
