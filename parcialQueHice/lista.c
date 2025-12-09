#include "lista.h"

void CrearLista(t_lista *l){
    *l = NULL;
}

int ListaVacia(t_lista *l){
    if(*l == NULL){
        return 1;
    }
    return 0;
}

void AgregarOrdenadoConLimite(t_lista *l, void *data, int cantMax, size_t dataSize){

    ///agregar elementos a la lista preservando el orden y una cantidad maxima de elementos.
    ///En este caso de podria hacer generica para que funcione con otros tipos de datos y no solo puntajes.

    t_nodo *nuevoNodo;
    void *nuevaData;
    t_puntaje punt1;
    t_puntaje *pPunt1 = &punt1;
    t_puntaje punt2;
    t_puntaje *pPunt2 = &punt2;
    t_nodo *nodoActual = *l;
    t_nodo *nodoAnterior = NULL;
    int cantElem;

    nuevoNodo = (t_nodo *)malloc(sizeof(t_nodo));
    if(nuevoNodo == NULL){
        return;
    }
    nuevaData = malloc(dataSize);
    if(nuevaData == NULL){
        free(nuevoNodo);
        return;
    }

    memcpy(nuevaData, data, dataSize);
    nuevoNodo->data = nuevaData;
    nuevoNodo->sig = NULL;
    nuevoNodo->tam = dataSize;

    ///encuentro la cantidad de elementos de la lista.
    cantElem = CantidadDeElementos(l);

    if(cantElem == 0){
        ///lista vacia cargo al inicio
        *l = nuevoNodo;
        return;
    }

    ///si cantidad elementos no es 0 busco donde cargar el elemento
    while(nodoActual != NULL){
        ///me voy moviendo para saber donde tengo que poner el nuevo registro
        memcpy(pPunt1, data, dataSize);
        memcpy(pPunt2, nodoActual->data, dataSize);
        if(pPunt1->puntaje < pPunt2->puntaje){
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->sig;
            continue;
        }
        break;
    }

    ///una vez llegue a donde tengo que insertar
    if(nodoAnterior == NULL){
        ///si no hay nodo anterior tengo que insertar al inicio
        nuevoNodo->sig = nodoActual;
        *l = nuevoNodo;
    }
    else{
        ///inserto donde corresponda
        nodoAnterior->sig = nuevoNodo;
        nuevoNodo->sig = nodoActual;
    }

    ///si la cantidad de elementos supera el maximo debe eliminar el ultimo.
    if(cantElem + 1 > cantMax){
        nodoActual = *l;
        nodoAnterior = NULL;
        while(nodoActual->sig != NULL){
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->sig;
        }
        ///llego al ultimo nodo y luego lo elimino
        free(nodoActual->data);
        free(nodoActual);
        nodoAnterior->sig = NULL;
    }

    return;
}

int CantidadDeElementos(t_lista *l){

    int cant = 0;
    t_nodo *leido = *l;
    while(leido != NULL){
        cant++;
        leido = leido->sig;
    }

    return cant;
}
