#include "arbol.h"

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

int InsertarEnArbol(tArbol *arbol, void *data, size_t dataSize, int(cmp)(void *, void *)){
    tNodo *nuevoNodo;
    void *nuevaData;
    int comparacion;

    if((nuevoNodo = (tNodo *)malloc(sizeof(tNodo))) == NULL){
        return -1;
    }
    if((nuevaData = malloc(dataSize)) == NULL){
        free(nuevoNodo);
        return -1;
    }

    ///creo el nodo que voy a insertar
    nuevoNodo->der = NULL;
    nuevoNodo->izq = NULL;
    nuevoNodo->dataSize = dataSize;
    memcpy(nuevaData, data, dataSize);
    nuevoNodo->data = nuevaData;

    if(ArbolVacio(arbol)){
        *arbol = nuevoNodo;
        return 1;
    }

    while(*arbol != NULL){
        comparacion = cmp(nuevoNodo->data, (*arbol)->data);
        if(comparacion == 1){
            ///me muevo hacia la derecha
            arbol = &(*arbol)->der;
        }
        else if(comparacion == -1){
            ///me muevo hacia la izquierda
            arbol = &(*arbol)->izq;
        }
        else{
            ///Duplicado
            free(nuevaData);
            free(nuevoNodo);
            return 0;
        }
    }

    ///una vez estoy donde voy a insertar el nodo
    *arbol = nuevoNodo; ///lo inserto
    return 1;
}

void RecorrerEnOrden(tArbol *arbol, void (mostrar)(void *)){
    if(ArbolVacio(arbol)){
        return;
    }
    RecorrerEnOrden(&(*arbol)->izq, mostrar);
    mostrar((*arbol)->data);
    RecorrerEnOrden(&(*arbol)->der, mostrar);

}

tArbol *BuscarRegistroPorClave(tArbol *arbol, void *dataBsc,  int (cmp)(void *, void *)){
    int comparacion;
    while(*arbol != NULL){
        comparacion = cmp(dataBsc, (*arbol)->data);
        if(comparacion == 1){
            arbol = &(*arbol)->der;
        }
        else if(comparacion == -1){
            arbol = &(*arbol)->izq;
        }
        else{
            return arbol;
        }
    }
    return NULL; ///No encontrado.
}

tArbol *BuscarMasChicoSubArbol(tArbol *arbol){
    tArbol *anterior;
    while(*arbol != NULL){
        anterior = arbol;
        arbol = &(*arbol)->izq;
    }
    if(*anterior == NULL){
        return NULL;
    }
    else{
        return anterior;
    }
}

int EsHoja(tArbol *arbol){
    if((*arbol)->izq == NULL && (*arbol)->der == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int EliminarElemento(tArbol *arbol, void *dataElm, int (cmp)(void *, void *)){

    ///busco el elemento a eliminar
    tArbol *elim = BuscarRegistroPorClave(arbol, dataElm, cmp);
    tArbol *aux;
    tArbol *aux2;
    void *dataCopiada;
    if(*elim == NULL){
        return -1; ///elemento no existe.
    }
    if(EsHoja(elim)){
        ///Si es hoja tengo que eliminar el nodo directamente
        free((*elim)->data);
        free(*elim);
        *elim = NULL;
        return 1;
    }
    ///si no es hoja tengo 2 casos. Tiene 1 hijo o tiene 2

    if((*elim)->izq == NULL && (*elim)->der != NULL){
        ///si solo tiene un hijo derecho
        ///reemplazo el nodo que voy a borrar por su hijo derecho
        aux = &(*elim)->der;
        free((*elim)->data);
        free(*elim);
        *elim = NULL;
        *elim = *aux;
    }
    else if((*elim)->izq != NULL && (*elim)->der == NULL){
        ///si solo tiene hijo izquierdo
        ///lo mismo pero cambio el reemplazo
        aux = &(*elim)->izq;
        free((*elim)->data);
        free(*elim);
        *elim = NULL;
        *elim = *aux;
    }
    else{
        ///si tiene 2 hijos tengo que buscar el hijo mas pequeño del subarbol derecho y reemplazar el eliminado por ese.
        aux = BuscarMasChicoSubArbol(elim); ///busco el mas chico
        ///si es hoja
        if(EsHoja(aux)){
            ///borro el nodo a eliminar y lo reemplazo por el nodo deseado cambiando la memoria
            dataCopiada = malloc((*aux)->dataSize);
            if(dataCopiada == NULL){
                return -1; ///error de memoria
            }
            memcpy(dataCopiada, (*aux)->data, (*aux)->dataSize); ///copio la data
            free((*elim)->data);
            (*elim)->data = dataCopiada;
            (*elim)->dataSize = (*aux)->dataSize;
            ///copio los datos y el tamanio de aux a el nodo que iba a eliminar.
            ///borro aux
            free((*aux)->data);
            free(*aux);
            *aux = NULL;
            return 1;
        }
        else{
            ///si el nodo encontrado para reemplazar tuviera solo un hijo derecho tendria que reemplazar el nodo aux por su hijo derecho y despues reemplazar elim por aux
            ///borro el nodo a eliminar y lo reemplazo por el nodo deseado cambiando la memoria
            dataCopiada = malloc((*aux)->dataSize);
            if(dataCopiada == NULL){
                return -1; ///error de memoria
            }
            memcpy(dataCopiada, (*aux)->data, (*aux)->dataSize); ///copio la data
            free((*elim)->data);
            (*elim)->data = dataCopiada;
            (*elim)->dataSize = (*aux)->dataSize;
            ///copio los datos y el tamanio de aux a el nodo que iba a eliminar.
            ///borro aux
            aux2 = &(*aux)->der;
            free((*aux)->data);
            free(*aux);
            *aux = NULL;
            *aux = *aux2;
            return 1;
        }

    }
    return -2; ///error no definido?
}

void VaciarArbol(tArbol *arbol){
    if(ArbolVacio(arbol)){
        return;
    }
    VaciarArbol(&(*arbol)->izq);
    VaciarArbol(&(*arbol)->der);
    free((*arbol)->data);
    free(*arbol);
    *arbol == NULL;

}
