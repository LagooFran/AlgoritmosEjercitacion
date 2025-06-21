#include "MiListaDE.h"


void CrearListaDE(tListaDE *lista){
    *lista = NULL;
}

int ListaVaciaDE(tListaDE *lista){
    if(*lista == NULL){
        return 1;
    }
    return 0;
}

int AgregarAlFinal(tListaDE *lista, void *data, size_t dataSize){

    tNodo *pNuevoNodo;
    void *pNuevaData;
    tNodo *nodoActual = *lista;

    if((pNuevoNodo = (tNodo *)malloc(sizeof(tNodo))) == NULL){
        return -1; ///no se pudo asignar memoria
    }
    if((pNuevaData = malloc(dataSize)) == NULL){
        free(pNuevoNodo);
        return -1;
    }

    memcpy(pNuevaData, data, dataSize);
    pNuevoNodo->data = pNuevaData;
    pNuevoNodo->dataSize = dataSize;
    pNuevoNodo->sig = NULL;

    if(ListaVaciaDE(lista)){
        pNuevoNodo->ant = NULL;
        *lista = pNuevoNodo;
        return 0;
    }
    else{
        while(nodoActual->sig != NULL){
            nodoActual = nodoActual->sig;
        }
        pNuevoNodo->ant = nodoActual;
        nodoActual->sig = pNuevoNodo;
        return 0;
    }
}


int AgregarAlInicio(tListaDE *lista, void *data, size_t dataSize){

    tNodo *pNuevoNodo;
    void *pNuevaData;
    tNodo *nodoActual = *lista;

    if((pNuevoNodo = (tNodo *)malloc(sizeof(tNodo))) == NULL){
        return -1; ///no se pudo asignar memoria
    }
    if((pNuevaData = malloc(dataSize)) == NULL){
        free(pNuevoNodo);
        return -1;
    }

    memcpy(pNuevaData, data, dataSize);
    pNuevoNodo->data = pNuevaData;
    pNuevoNodo->dataSize = dataSize;

    pNuevoNodo->ant = NULL;

    if(ListaVaciaDE(lista)){
        pNuevoNodo->sig = NULL;
        *lista = pNuevoNodo;
        return 0;
    }
    else{
        pNuevoNodo->sig = nodoActual;
        nodoActual->ant = pNuevoNodo;
        *lista = pNuevoNodo;
        return 0;
    }
}

int SacarDelFinal(tListaDE *lista, void *dataDest){
    tNodo *nodoActual = *lista;

    if(ListaVaciaDE(lista)){
        return -1; ///no hay nada que sacar
    }

    while(nodoActual->sig != NULL){
        nodoActual = nodoActual->sig;
    }

    memcpy(dataDest, nodoActual->data, nodoActual->dataSize);
    if(nodoActual->ant == NULL){
        *lista = NULL; ///unico nodo en la lista
    }
    else{
        nodoActual->ant->sig = NULL;
    }
    free(nodoActual->data);
    free(nodoActual);
    return 0;
}

int SacarDelInicio(tListaDE *lista, void *dataDest){
    tNodo *nodoActual = *lista;

    if(ListaVaciaDE(lista)){
        return -1; ///no hay nada que sacar
    }

    memcpy(dataDest, nodoActual->data, nodoActual->dataSize);
    if(nodoActual->sig == NULL){
        *lista = NULL; ///unico nodo en la lista
    }
    else{
        nodoActual->sig->ant = NULL;
        *lista = nodoActual->sig;
    }
    free(nodoActual->data);
    free(nodoActual);
    return 0;
}

int BuscarNodo(tListaDE *lista, void *dataDest, void *dataBsc, int (cmp)(void *, void *)){

    tNodo *nodoActual = *lista;
    int comparacion;

    if(ListaVaciaDE(lista)){
        return -1; ///lista vacia
    }

    while(nodoActual != NULL){
        comparacion = cmp(dataBsc, nodoActual->data);
        if(comparacion != 0){
            nodoActual = nodoActual->sig;
        }
        else{
            memcpy(dataDest, nodoActual->data, nodoActual->dataSize);
            return 0;
        }
    }
    return -1;
}

int BuscarNodoYSacar(tListaDE *lista, void *dataDest, void *dataBsc, int (cmp)(void *, void *)){

    tNodo *nodoActual = *lista;
    int comparacion;

    if(ListaVaciaDE(lista)){
        return -1; ///lista vacia
    }

    while(nodoActual != NULL){
        comparacion = cmp(dataBsc, nodoActual->data);
        if(comparacion != 0){
            nodoActual = nodoActual->sig;
        }
        else{
            memcpy(dataDest, nodoActual->data, nodoActual->dataSize);
            if(nodoActual->ant == NULL && nodoActual->sig == NULL){
                *lista = NULL;
            }
            else if(nodoActual->sig == NULL){
                nodoActual->ant->sig = NULL;
            }
            else if(nodoActual->ant == NULL){
                nodoActual->sig->ant = NULL;
                *lista = nodoActual->sig;
            }
            else{
                nodoActual->ant->sig = nodoActual->sig;
            }
            free(nodoActual->data);
            free(nodoActual);
            return 0;
        }
    }
    return -1;
}

int InsertarOrdenado(tListaDE *lista, void *data, size_t dataSize, int(cmp)(void *, void *)){

    tNodo *pNuevoNodo;
    void *pNuevaData;
    tNodo *nodoActual = *lista;
    int comparacion;

    if((pNuevoNodo = (tNodo *)malloc(sizeof(tNodo))) == NULL){
        return -1; ///no se pudo asignar memoria
    }
    if((pNuevaData = malloc(dataSize)) == NULL){
        free(pNuevoNodo);
        return -1;
    }

    memcpy(pNuevaData, data, dataSize);
    pNuevoNodo->data = pNuevaData;
    pNuevoNodo->dataSize = dataSize;

    if(ListaVaciaDE(lista)){
        ///no hay nodos iguales
        pNuevoNodo->ant = NULL;
        pNuevoNodo->sig = NULL;
        *lista = pNuevoNodo;
        return 0;
    }

    comparacion = cmp(pNuevaData, nodoActual->data);
    if(comparacion == -1){
        ///nuevo nodo va antes del primero
        pNuevoNodo->ant = NULL;
        nodoActual->ant = pNuevoNodo;
        pNuevoNodo->sig = nodoActual;
        *lista = pNuevoNodo;
        return 0;
    }
    while(nodoActual->sig != NULL){
        comparacion = cmp(pNuevaData, nodoActual->data);
        if(comparacion == 0){
            free(pNuevaData);
            free(pNuevoNodo);
            return -1; ///Nodo ya existe
        }
        else if(comparacion == -1){
            ///el nodo a insertar va detras del nodo actual.
            pNuevoNodo->ant = nodoActual->ant;
            pNuevoNodo->sig = nodoActual;
            nodoActual->ant->sig = pNuevoNodo;
            nodoActual->ant = pNuevoNodo;
            return 0;
        }
    }

    ///si no se encontro nada en el bucle signfica que el nodo debe ser insertado al final o antes
    comparacion = cmp(pNuevaData, nodoActual->data);
    if(comparacion == 0){
        free(pNuevaData);
        free(pNuevoNodo);
        return -1; ///nodo repetido
    }
    else if(comparacion == -1){
        ///debe ser insertado antes
        pNuevoNodo->ant = nodoActual->ant;
        pNuevoNodo->sig = nodoActual;
        nodoActual->ant->sig = pNuevoNodo;
        nodoActual->ant = pNuevoNodo;
    }
    else{
        ///debe ser insertado despues
        pNuevoNodo->ant = nodoActual;
        pNuevoNodo->sig = NULL;
        nodoActual->sig = pNuevoNodo;
    }

    return 0;

}


