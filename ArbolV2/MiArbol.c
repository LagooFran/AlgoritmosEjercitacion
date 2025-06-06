#include "MiArbol.h"

void CrearArbol(tArbol *arbol){
    *arbol = NULL;
}

int ArbolVacio(tArbol *arbol){
    if(*arbol == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int ArbolLleno(size_t dataSize){
    ///retorna -1 si esta lleno 0 si tiene espacio
    tNodo *nuevoNodo;
    void *data;
    nuevoNodo = (tNodo*)malloc(sizeof(nuevoNodo));
    if(nuevoNodo == NULL){
        return -1;
    }
    else{
        data = malloc(dataSize);
        if(data == NULL){
            free(nuevoNodo);
            return -1;
        }
    }
    free(nuevoNodo);
    free(data);
    return 0;
}


int InsertarEnArbol(tArbol *arbol, void *data, size_t dataSize, int (*cmp)(const void*, const void*)){
    ///retorno -1 si fallo retorno 0 si cargo el nodo correctamente 1 si ya existe el nodo.
    int resCmp;
    tNodo *nuevoNodo;
    while(*arbol){
        ///mientras este parado sobre un nodo existente.
        resCmp = cmp(data, (*arbol)->data);
        if(resCmp == 1){
            arbol = &(*arbol)->der;
        }
        else if(resCmp == -1){
            arbol = &(*arbol)->izq;
        }
        else{
            return 1;  ///nodo repetido
        }

        if(ArbolLleno(dataSize)<0){
            return -1; ///arbol lleno fallo la carga
        }

    }

    ///cuando llego a un nodo nulo ya puedo insertar mi info
    nuevoNodo = (tNodo*)malloc(sizeof(nuevoNodo));
    nuevoNodo->data = malloc(dataSize);
    memcpy(nuevoNodo->data, data, dataSize);
    nuevoNodo->der = NULL;
    nuevoNodo->izq = NULL;
    *arbol = nuevoNodo;

    return 0;
}

void RecorrerEnOrden(tArbol *arbol, void (*mostrar)(const void*)) {
    if (*arbol) {
        RecorrerEnOrden(&(*arbol)->izq, mostrar);
        mostrar((*arbol)->data);
        RecorrerEnOrden(&(*arbol)->der, mostrar);
    }
}

void RecorrerEnPreOrden(tArbol *arbol, void (*mostrar)(const void*)) {
    if (*arbol) {
        mostrar((*arbol)->data);
        RecorrerEnPreOrden(&(*arbol)->izq, mostrar);
        RecorrerEnPreOrden(&(*arbol)->der, mostrar);
    }
}

void RecorrerEnPosOrden(tArbol *arbol, void (*mostrar)(const void*)) {
    if (*arbol) {
        RecorrerEnPosOrden(&(*arbol)->izq, mostrar);
        RecorrerEnPosOrden(&(*arbol)->der, mostrar);
        mostrar((*arbol)->data);
    }
}
