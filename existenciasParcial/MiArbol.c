#include "MiArbol.h"

void CrearArbol(tArbol *arbol){
    *arbol = NULL;
}

int ArbolVacio(tArbol *arbol){
    if(*arbol == NULL){
        return 1;
    }
    return 0;
}

int InsertarEnArbol(tArbol *arbol, void *data, size_t dataSize, int (cmp)(void*, void*)){
    int comparacion;
    tNodo *nuevoNodo;
    void *nuevaData;
    tNodo *nodoActual = *arbol;
    tNodo *nodoAnterior = NULL;

    if((nuevoNodo = (tNodo *)malloc(sizeof(tNodo))) == NULL){
        return -1;
    }
    if((nuevaData = malloc(dataSize)) == NULL){
        free(nuevoNodo);
        return -1;
    }
    memcpy(nuevaData, data, dataSize);
    nuevoNodo->data = nuevaData;
    nuevoNodo->dataSize = dataSize;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;

    if(ArbolVacio(arbol)){
        *arbol = nuevoNodo;
        return 0;
    }

    while(nodoActual != NULL){
        comparacion = cmp(nuevoNodo->data, nodoActual->data);
        nodoAnterior = nodoActual;
        if(comparacion == 1){
            nodoActual = nodoActual->der;
        }
        else if(comparacion == -1){
            nodoActual = nodoActual->izq;
        }
        else{
            return -1; ///nodo repetido
        }
    }

    ///en nodo anterior tengo el lugar donde ira el nuevo nodo.
    comparacion = cmp(nuevoNodo->data, nodoAnterior->data);
    if(comparacion == 1){
        nodoAnterior->der = nuevoNodo;
    }
    else{
        nodoAnterior->izq = nuevoNodo;
    }
    return 0;
}

void RecorrerInOrden(tArbol *arbol, void (mostrar)(void*)){
    if(ArbolVacio(arbol)){
        return;
    }
    RecorrerInOrden(&(*arbol)->izq, mostrar);
    mostrar((*arbol)->data);
    RecorrerInOrden(&(*arbol)->der, mostrar);
}

int BuscarEnArbol(tArbol *arbol, void *dataDest, void *dataBsc, int (cmp)(void*, void*)){
    int comparacion;
    tNodo *nodoActual = *arbol;
    if(ArbolVacio(arbol)){
        return -1;
    }

    while(nodoActual != NULL){
        comparacion = cmp(dataBsc, nodoActual->data);
        if(comparacion == 1){
            nodoActual = nodoActual->der;
        }
        else if(comparacion == -1){
            nodoActual = nodoActual->izq;
        }
        else{
            ///nodo encontrado
            memcpy(dataDest, nodoActual->data, nodoActual->dataSize);
            return 0;
        }
    }

    ///nodo no encontrado
    return -1;
}
