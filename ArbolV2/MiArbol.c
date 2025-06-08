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

    if(ArbolLleno(dataSize)<0){
        return -1; ///arbol lleno fallo la carga
    }


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
    }


    ///cuando llego a un nodo nulo ya puedo insertar mi info
    nuevoNodo = (tNodo*)malloc(sizeof(tNodo));
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

int BuscarEnArbol(tArbol  *arbol, void *data, void  *dataDest, size_t dataSize, int (*cmp)(const void*, const void*)){
    int resCmp;
    if(*arbol){
        resCmp = cmp(data, (*arbol)->data);
        if(resCmp == 1){
            ///si lo que comparo es mas grande que el nodo en el que estoy me muevo hacia la derecha y busco en subarbol
            BuscarEnArbol(&(*arbol)->der, data, dataDest, dataSize, cmp);
        }
        else if(resCmp == -1){
            ///si lo que comparo es mas chico que el nodo en el que estoy me muevo hacia la izquierda y busco en subarbol
            BuscarEnArbol(&(*arbol)->izq, data, dataDest, dataSize, cmp);
        }
        else{
            memcpy(dataDest, (*arbol)->data, dataSize);  ///si son iguales copio la data del nodo en dataDest
            return 0; ///todo ok
        }

    }
    return -1; ///no existe el nodo buscado
}

int BuscarEnArbolPuntero(tArbol  *arbol, void *data, void  *dataDest, size_t dataSize, int (*cmp)(const void*, const void*)){
    int resCmp;
    if(*arbol){
        resCmp = cmp(data, (*arbol)->data);
        if(resCmp == 1){
            ///si lo que comparo es mas grande que el nodo en el que estoy me muevo hacia la derecha y busco en subarbol
            BuscarEnArbol(&(*arbol)->der, data, dataDest, dataSize, cmp);
        }
        else if(resCmp == -1){
            ///si lo que comparo es mas chico que el nodo en el que estoy me muevo hacia la izquierda y busco en subarbol
            BuscarEnArbol(&(*arbol)->izq, data, dataDest, dataSize, cmp);
        }
        else{
            *dataDest = *arbol;  ///si son iguales copio la data del nodo en dataDest
            return 0; ///todo ok
        }

    }
    return -1; ///no existe el nodo buscado
}


int BuscarNodoMasGrande(tArbol *arbol){
    int cont = 0;
    ///retorna -1 si el arbol esta vacio
    if(ArbolVacio(arbol)){
        return -1;
    }
    ///retorna la cantidad de niveles que tuvo que bajar para encontrar el nodo
    while(*arbol){
        cont++;
        arbol = &(*arbol)->der;
    }

    return cont;
}

int BuscarAltura(tArbol *arbol){
    int izq, der;
    if(ArbolVacio(arbol)){
        return -1;
    }else{
        izq = BuscarAltura(&(*arbol)->izq);
        der = BuscarAltura(&(*arbol)->der);

        if(der > izq){
            return 1+der;
        }
        else{
            return 1+izq;
        }
    }
}

int EsHoja(tArbol *arbol){
    if((*arbol)->izq == NULL && (*arbol)->der == NULL){
        return 1; /// el subarbol comenzado en el nodo es completo
    }
    return 0;
}

int EsCompleto(tArbol *arbol){
    if(ArbolVacio(arbol)){
        return 1; ///esta vacio por lo tanto es completo
    }
    else{
        ///si el nodo no tiene subarboles
        if(EsHoja(arbol)){
            return 1; ///es completo el subarbol
        }
        else{
            if((*arbol)->izq != NULL && (*arbol)->der != NULL){
                ///si tiene 2 nodos izq y derecha compruebo que los subarboles izq y derecha sean completos
                if(EsCompleto(&(*arbol)->izq) && EsCompleto(&(*arbol)->der)){
                    return 1;
                }
                else{
                    return 0; ///los subarboles estan pero no son completos
                }
            }

            return 0; ///tiene uno solo nodo de los 2

        }

    }

}

int EsBalanceado(tArbol *arbol){

    int altIzq, altDer, comp;
    ///la diferencia entre la altura de los nodos izquierdo y derecho deben ser de no mas de 1
    if(ArbolVacio(arbol)){
        return 1; ///si esta vacio es balanceado
    }
    if(EsHoja(arbol)){
        return 1; ///Un subarbol formado por una hoja esta balanceado
    }
    else{
        altIzq = BuscarAltura(&(*arbol)->izq);
        altDer = BuscarAltura(&(*arbol)->der);
        comp = altDer - altIzq;
        if(comp < 0){
            comp = comp * -1;
        }

        if(comp <= 1){
            ///los subarboles izquierdo y no tienen diferencia mayor a 1 de altura. Ahora tengo que comprobar recursivamente que los que forman izq y der sean balanceados.
            if(EsBalanceado(&(*arbol)->izq) == 1 && EsBalanceado(&(*arbol)->der) == 1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
}

///hay que arreglar esto...

void BuscarMenorSubArbol(tArbol *arbol, void *dataDest){
    if((*arbol)->izq != NULL){
        BuscarMenorSubArbol((*arbol)->izq, dataDest)
    }
    else{
        dataDest = *arbol;
    }
}


int EliminarNodo(tArbol *arbol, void *data, size_t dataSize, int (*cmp)(const void*, const void*)){
    ///busco la ubicacion del nodo a borrar
    tNodo *nodoABorrar;
    tNodo *nodoAReUbicar;
    if(BuscarEnArbolPuntero(arbol, data, nodoABorrar, dataSize, cmp) == 0){
        ///si encuentro el nodo a borrar
        BuscarMenorSubArbol(arbol, nodoAReUbicar)
        free((*nodoABorrar)->data);
        free(nodoABorrar);
        nodoABorrar = nodoAReUbicar;

    }
    else{
        ///el nodo a borrar no exite
        return -1;
    }


}


