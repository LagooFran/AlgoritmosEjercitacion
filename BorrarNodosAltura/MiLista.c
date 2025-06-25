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

void OrdenarLista(tLista *lista, int (cmp)(void *, void *)){

    tNodo2 *nodoActual;
    tNodo2 *nodoSiguiente;
    tNodo2 *nodoPrevio = NULL;
    int huboCambios = 0;

    if(ListaVacia(lista)){
        return; ///la lista esta vacia. Que voy a ordenar!!!
    }


    do{
        huboCambios = 0;
        nodoPrevio = NULL;
        nodoActual = *lista;
        while(nodoActual != NULL && nodoActual->sig != NULL){
            nodoSiguiente = nodoActual->sig;
            printf("cmp %d\n", cmp(nodoActual->data, nodoSiguiente->data));
            if(cmp(nodoActual->data, nodoSiguiente->data) == 1){
                ///si el nodo actual es mas grande que el siguiente lo tengo que mover hacia adelante
                if(nodoPrevio == NULL){
                    *lista = nodoSiguiente;
                }
                else{
                    nodoPrevio->sig = nodoSiguiente;
                }
                nodoActual->sig = nodoSiguiente->sig;
                nodoSiguiente->sig = nodoActual;
                nodoActual = nodoSiguiente;
                huboCambios = 1;
            }

            nodoPrevio = nodoActual;
            nodoActual = nodoActual->sig;
        }
    }while(huboCambios);
}

void MostrarLista(tLista *lista, void (mostrar)(void *)){
    tNodo2 *nodoActual = *lista;
    while(nodoActual != NULL){
        mostrar(nodoActual->data);
        nodoActual = nodoActual->sig;
    }
}
