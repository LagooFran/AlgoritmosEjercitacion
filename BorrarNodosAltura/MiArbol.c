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
    nuevoNodo = (tNodo*)malloc(sizeof(tNodo));
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


int InsertarEnArbol(tArbol *arbol, void *data, size_t dataSize, int (*cmp)(void*, void*)){
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
    nuevoNodo->dataSize = dataSize;
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

tArbol *BuscarEnArbolPtr(tArbol  *arbol, void *data, int (*cmp)(void*, void*)){
    int resCmp;
    if(*arbol){
        resCmp = cmp(data, (*arbol)->data);
        if(resCmp == 1){
            ///si lo que comparo es mas grande que el nodo en el que estoy me muevo hacia la derecha y busco en subarbol
            return BuscarEnArbolPtr(&(*arbol)->der, data, cmp);
        }
        else if(resCmp == -1){
            ///si lo que comparo es mas chico que el nodo en el que estoy me muevo hacia la izquierda y busco en subarbol
            return BuscarEnArbolPtr(&(*arbol)->izq, data, cmp);
        }
        else{
            ///si son iguales retorno el puntero al nodo encontrado
            return arbol;
        }

    }
    return NULL; ///no existe el nodo buscado
}

tArbol *BuscarMenorSubArbol(tArbol *arbol){
    if(ArbolVacio(arbol)){
        return NULL;
    }
    if((*arbol)->izq != NULL){
        return BuscarMenorSubArbol(&(*arbol)->izq);
    }
    else{
        return arbol;
    }
}

/*
int EliminarNodo(tArbol *arbol, void *data, int (*cmp)(const void*, const void*)){

    tArbol *nodoABorrar;

    ///para la parte cuando se tienen 2 hijos
    tArbol *nodoReemplazo;
    tNodo *ptrReemplazo;
    ///-----

    tNodo *ptrNodoABorrar;
    tNodo *ptrReubicar; ///el nodo que voy a poner donde esta estaba ptrNodoABorrar

    if(ArbolVacio(arbol)){
        ///arbol vacio
        return -1;
    }
    nodoABorrar = BuscarEnArbolPtr(arbol, data, cmp);
    if(nodoABorrar != NULL){
        ptrNodoABorrar = *nodoABorrar;
        if(EsHoja(nodoABorrar)){
            free(ptrNodoABorrar->data);
            free(ptrNodoABorrar);
            *nodoABorrar = NULL;
            return 0;
        }
        else if(ptrNodoABorrar->der == NULL){
            ptrReubicar = ptrNodoABorrar->izq;
            free(ptrNodoABorrar->data);
            free(ptrNodoABorrar);
            *nodoABorrar = ptrReubicar;
            return 0;
        }
        else if(ptrNodoABorrar->izq == NULL){
            ptrReubicar = ptrNodoABorrar->der;
            free(ptrNodoABorrar->data);
            free(ptrNodoABorrar);
            *nodoABorrar = ptrReubicar;
            return 0;
        }
        else{
            ///los dos nodos hijos existen
            nodoReemplazo = BuscarMenorSubArbol(&(ptrNodoABorrar->der));
            ptrReemplazo = *nodoReemplazo;

            free(ptrNodoABorrar->data);

            ptrNodoABorrar->data = ptrReemplazo->data;
            ptrNodoABorrar->dataSize = ptrReemplazo->dataSize;

            *nodoReemplazo = ptrReemplazo->der;
            free(ptrReemplazo);

            return 0;
        }

    }
    else{
        ///No existe el nodo a borrar
        return -1;
    }

}
*/

int EncontrarAlturaNodo(tArbol *arbol, void *dataBsc, int (cmp)(void *, void *)){
    ///bajar en el arbol buscando el nodo e ir contando la cantidad de bajadas.
    tNodo *nodoActual = *arbol;
    int comparacion, altura = 0;
    while(nodoActual != NULL){
        comparacion = cmp(nodoActual->data, dataBsc);
        if(comparacion == 0){
            return altura;
        }
        else{
            altura++;
            if(comparacion == 1){
                nodoActual = nodoActual->izq;
            }
            else{
                nodoActual = nodoActual->der;
            }
        }
    }
    return -1; ///nodo no encontrado.

}

int AlturaArbolV2(tArbol *arbol){
    tNodo *nodoActual = *arbol;
    int der;
    int izq;

    if(nodoActual == NULL){
        return 0;
    }
    else{
        der = AlturaArbolV2(&(nodoActual)->der);
        izq = AlturaArbolV2(&(nodoActual)->izq);
        if(der>izq){
            return 1+der;
        }
        else{
            return 1+izq;
        }
    }
}

int EliminarNodo(tArbol *arbol, void *dataElm, int (cmp)(void *, void *)){
    tArbol *nodoAReemplazar;
    tNodo *nodoReemplazo;

    tArbol *pNodoReemplazo;

    void *dataCopiada;

    ///busco el nodo a que tengo que reemplazar
    nodoAReemplazar = BuscarEnArbolPtr(arbol, dataElm, cmp);
    if(nodoAReemplazar == NULL){
        return -1; ///no se encontro un nodo a borrar
    }

    ///una vez tengo ese nodo busco el nodo por el cual lo voy a reemplazar.
    if(EsHoja(nodoAReemplazar)){
        ///si el nodo es hoja lo borro
        free((*nodoAReemplazar)->data);
        free(*nodoAReemplazar);
        *nodoAReemplazar = NULL;
        return 0;
    }

    ///en casos donde no sea hoja busco el nodo candidato a reemplazar el nodo que voy a borrar para mantener la estructura.
    if((*nodoAReemplazar)->izq == NULL){
        ///si no tiene nodo izquierdo
        ///reemplazo por el siguiente derecho.
        nodoReemplazo = (*nodoAReemplazar)->der;
        free((*nodoAReemplazar)->data);
        free(*nodoAReemplazar);
        *nodoAReemplazar = nodoReemplazo;
        return 0;
    }
    else if((*nodoAReemplazar)->der == NULL){
        ///si no tiene nodo derecho
        ///reemplazo por el siguiente izquierdo.
        nodoReemplazo = (*nodoAReemplazar)->izq;
        free((*nodoAReemplazar)->data);
        free(*nodoAReemplazar);
        *nodoAReemplazar = nodoReemplazo;
        return 0;

    }
    else{
        ///busco un nodo para reemplazar el nodo que voy a eliminar en su subarbol derecho (el mas chico del derecho que dejaria el arbol preservando su estructura)
        pNodoReemplazo = BuscarMenorSubArbol(&(*nodoAReemplazar)->der);
        ///hay dos chances. 1. Que el menor sea una hoja o que solo tenga un hijo derecho (izquierdo no puede tener porque para encontrar el mas chico ya recorri todo hacia la izquierda)

        ///si es hoja
        nodoReemplazo = *pNodoReemplazo;
        ///copio datos de un nodo al otro
        dataCopiada = malloc(nodoReemplazo->dataSize);
        memcpy(dataCopiada, nodoReemplazo->data, nodoReemplazo->dataSize);
        ///una vez copiada la data borro la data del nodo original y le asigno la nueva.
        free((*nodoAReemplazar)->data);
        (*nodoAReemplazar)->data = dataCopiada;
        (*nodoAReemplazar)->dataSize = nodoReemplazo->dataSize;
        ///borro el nodo que movi los datos.
        *pNodoReemplazo = nodoReemplazo->der;
        free(nodoReemplazo->data);
        free(nodoReemplazo);
        return 0;
    }
}

