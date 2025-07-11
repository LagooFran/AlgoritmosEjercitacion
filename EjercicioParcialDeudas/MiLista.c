#include "MiLista.h"

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

    tNodo2 *nodoActual = *lista;
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
    tNodo2 *nodoActual = *lista;
    tNodo2 *nodoAnterior = NULL;

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

    tNodo2 *nodoActual = *lista;
    tNodo2 *nodoSiguiente;

    while(nodoActual != NULL){
        nodoSiguiente = nodoActual->sig;
        free(nodoActual->data);
        free(nodoActual);
        nodoActual = nodoSiguiente;
    }

    *lista = NULL;

}

void InsertarSinDuplicados(tLista *lista, void *data, size_t dataSize, int cmp(void*, void*), void acumular(void *, void *)){

    tNodo2 *nodoActual = *lista;
    int comparacion;

    while(nodoActual != NULL){
        comparacion = cmp(data, nodoActual->data);
        if(comparacion == 0){
            acumular(nodoActual->data, data);
            return;
        }
        nodoActual = nodoActual->sig;
    }

    ///si no encontre el nodo repetido.
    AgregarAlFinal(lista, data, dataSize);
    return;

}

void InsertarSinDuplicadosOrdenado(tLista *lista, void *data, size_t dataSize, int cmp(void*, void*), void acumular(void *, void *)){

    tNodo2 *nodoActual = *lista;
    tNodo2 *nodoAnterior = *lista;
    tNodo2 *nuevoNodo;
    void *nuevaData;

    if((nuevoNodo = (tNodo2*)malloc(sizeof(tNodo2))) == NULL){
        return; ///malloc fallido
    }
    if((nuevaData = malloc(dataSize)) == NULL){
        free(nuevoNodo);
        return; ///malloc fallido
    }

    memcpy(nuevaData, data, dataSize);
    nuevoNodo->data = nuevaData;
    nuevoNodo->dataSize = dataSize;
    nuevoNodo->sig = NULL;
    int comparacion;

    if(ListaVacia(lista)){
        *lista = nuevoNodo;
        return;
    }

    comparacion = cmp(data, nodoActual->data);
    if(comparacion == 1){
        ///debo insertar nodo antes del primero;
        nuevoNodo->sig = nodoActual;
        *lista = nuevoNodo;
        return;
    }

    while(nodoActual != NULL){
        comparacion = cmp(data, nodoActual->data);
        if(comparacion == 0){
            acumular(nodoActual->data, data);
            free(nuevaData);
            free(nuevoNodo);
            return;
        }
        else if(comparacion == -1){
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->sig;
        }
        else{
            ///debo insertar el nodo antes del que estoy actualmente
            nuevoNodo->sig = nodoActual;
            nodoAnterior->sig = nuevoNodo;
            return;
        }
    }

    ///si el nodo va al final.
    nodoAnterior->sig = nuevoNodo;
    return;

}
