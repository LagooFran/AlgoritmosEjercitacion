#include "miArbol.h"

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

    ///asigno lugar para los nuevos datos
    if((nuevoNodo = (tNodo *)malloc(sizeof(tNodo))) == NULL){
        return -1; ///no hay espacio
    }
    if((nuevaData = malloc(dataSize)) == NULL){
        free(nuevoNodo);
        return -1; ///no hay espacio
    }

    ///asigno todo
    nuevoNodo->dataSize = dataSize;
    memcpy(nuevaData, data, dataSize);
    nuevoNodo->data = nuevaData;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;

    if(ArbolVacio(arbol)){
        *arbol = nuevoNodo;
        return 1;
    }

    while(*arbol != NULL){
        comparacion = cmp(nuevoNodo->data, (*arbol)->data);
        if(comparacion == 1){
            arbol = &(*arbol)->der;
        }
        else if(comparacion == -1){
            arbol = &(*arbol)->izq;
        }
        else{
            free(nuevoNodo->data);
            free(nuevoNodo);
            return 0; ///repetido
        }
    }

    ///llego a null e inserto ahi
    *arbol = nuevoNodo;
    return 1;

}

void RecorrerInOrden(tArbol *arbol, void (mostrar)(void *)){
    if(*arbol == NULL){
        return;
    }
    RecorrerInOrden(&(*arbol)->izq, mostrar);
    mostrar((*arbol)->data);
    RecorrerInOrden(&(*arbol)->der, mostrar);
}

int EstaEnArbol(tArbol *arbol, void *dataBsc, int (cmp)(void *, void *)){
    int comparacion;

    ///retorna 1 si el dato existe en el arbol
    if(ArbolVacio(arbol)){
        return 0;
    }

    while(*arbol != NULL){
        comparacion = cmp(dataBsc, (*arbol)->data);
        if(comparacion == 1){
            arbol = &(*arbol)->der;
        }
        else if(comparacion == -1){
            arbol = &(*arbol)->izq;
        }
        else{
            return 1; ///repetido
        }
    }

    return 0;
}

void Diferencia(tArbol *arbolA, tArbol *arbolB, int (cmp)(void *, void *), void (mostrar)(void *)){
    ///recorro todo el arbol A y me fijo si los elementos de A existen en B
    if(*arbolA == NULL){
        return;
    }
    Diferencia(&(*arbolA)->izq, arbolB, cmp, mostrar);
    if(EstaEnArbol(arbolB, (*arbolA)->data, cmp) == 0){
        ///si esta en el arbol B entonces no lo muestro si no esta lo muestro porque saco la diferencia
        mostrar((*arbolA)->data);
    }
    Diferencia(&(*arbolA)->der, arbolB, cmp, mostrar);

}


