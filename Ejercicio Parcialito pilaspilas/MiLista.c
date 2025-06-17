#include "MiLista.h"

int CrearLista(tLista * lista){
    *lista = NULL;
    return 0;
}

int ListaVacia(tLista *lista){
    if(*lista == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int PonerAlFinal(tLista *lista, void *data, size_t dataSize){

    tNodo *pNodoActual;
    tNodo *pNuevoNodo;
    void *pNuevaData;

    if((pNuevoNodo = malloc(sizeof(tNodo))) == NULL){
        return -1; ///No hay espacio para crear el nodo
    }
    else if((pNuevaData = malloc(dataSize)) == NULL){
        free(pNuevoNodo);
        return -1; ///No hay espacio para alojar la data
    }

    ///copio la data
    memcpy(pNuevaData, data, dataSize);
    pNuevoNodo->data = pNuevaData;
    pNuevoNodo->dataSize = dataSize;
    pNuevoNodo->sig = NULL;

    if(ListaVacia(lista)){
        *lista = pNuevoNodo;
    }
    else{
        ///Creo una variable aux
        pNodoActual = *lista;
        while(pNodoActual->sig != NULL){
            pNodoActual = pNodoActual->sig;
        }
        ///llego al ultimo entonces ahora agrego el nuevo nodo al final
        pNodoActual->sig = pNuevoNodo;
    }

    return 0;
}

int SacarDelFinal(tLista *lista, void *dataDest){
    tNodo *pNodoActual;
    tNodo *pNodoAnterior = NULL;
    pNodoActual = *lista;

    ///busco el ultimo elemento de la lista y lo devuelvo.
    if(ListaVacia(lista)){
        return -1; ///lista vacia
    }

    ///busco el utlimo elemento
    while(pNodoActual->sig != NULL){
        pNodoAnterior = pNodoActual;
        pNodoActual = pNodoActual->sig;
    }

    memcpy(dataDest, pNodoActual->data, pNodoActual->dataSize);
    free(pNodoActual->data);
    free(pNodoActual);

    if(pNodoAnterior == NULL){
        *lista = NULL;
    }
    else{
        pNodoAnterior->sig = NULL;
    }

    return 0;
}
