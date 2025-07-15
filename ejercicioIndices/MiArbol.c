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

int InsertarEnArbol(tArbol *arbol, void *data, size_t dataSize, int(cmp)(void *, void *)){

    int comparacion;
    ///creo el nuevo nodo y data
    tNodo *nuevoNodo;
    void *nuevaData;

    if((nuevoNodo = (tNodo *)malloc(sizeof(tNodo))) == NULL){
        return -1; ///No hay memoria
    }
    if((nuevaData = malloc(dataSize)) == NULL){
        free(nuevoNodo);
        return -1; ///No hay memoria
    }

    memcpy(nuevaData, data, dataSize);
    nuevoNodo->dataSize = dataSize;
    nuevoNodo->data = nuevaData;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    ///una vez creado el nodo me fijo donde ponerlo.
    if(ArbolVacio(arbol)){
        *arbol = nuevoNodo;
        return 1;
    }
    else{
        while(*arbol != NULL){
            comparacion = cmp(data, (*arbol)->data);
            if(comparacion == 1){
                arbol = &(*arbol)->der;
            }
            else if(comparacion == -1){
                arbol = &(*arbol)->izq;
            }
            else{
                return 0; ///ya existe el nodo
            }
        }
        ///una vez llegue a donde quiero insertar pongo el nuevo nodo
        *arbol = nuevoNodo;
        return 1;
    }
}

void RecorrerInOrden(tArbol *arbol, void(mostrar)(void *)){
    if(ArbolVacio(arbol)){
        return;
    }
    RecorrerInOrden(&(*arbol)->izq, mostrar);
    mostrar((*arbol)->data);
    RecorrerInOrden(&(*arbol)->der, mostrar);
}

int ContarOcurrenciasNoClave(tArbol *arbol, void *data, int cmpdato(void *, void *)){
    if(ArbolVacio(arbol)){
        return 0;
    }
    if(cmpdato(data, (*arbol)->data) == 0){
            return 1+ContarOcurrenciasNoClave(&(*arbol)->izq, data, cmpdato) + ContarOcurrenciasNoClave(&(*arbol)->der, data, cmpdato);
    }
    return ContarOcurrenciasNoClave(&(*arbol)->izq, data, cmpdato) + ContarOcurrenciasNoClave(&(*arbol)->der, data, cmpdato);
}

void EspejarArbol(tArbol *arbol){
    tNodo *aux;
    if(ArbolVacio(arbol)){
        return;
    }
    EspejarArbol(&(*arbol)->izq);
    EspejarArbol(&(*arbol)->der);
    ///invierto el arbol
    aux = (*arbol)->izq;
    (*arbol)->izq = (*arbol)->der;
    (*arbol)->der = aux;

}

int CantidadDeNodos(tArbol *arbol){
    if(*arbol == NULL){
        return 0;
    }
    return 1 + CantidadDeNodos(&(*arbol)->izq) + CantidadDeNodos(&(*arbol)->der);
}

int AlturaArbol(tArbol *arbol){
    int izq, der;
    if(*arbol == NULL){
        return -1;
    }

    izq = AlturaArbol(&(*arbol)->izq);
    der = AlturaArbol(&(*arbol)->der);

    if(izq > der){
        return 1+izq;
    }
    else{
        return 1+der;
    }
}

//int EsBalanceado(tArbol *arbol){
  //  return CantidadDeNodosHastaNivel(arbol, AlturaArbol(arbol)-1) == pow(2, AlturaArbol(arbol)-1)-1;
//}

int CantidadDeNodosHastaNivel(tArbol *arbol, int nivel){
    if(*arbol == NULL){
        return 0;
    }
    if(nivel < 0){
        return 0;
    }

    return 1 + CantidadDeNodosHastaNivel(&(*arbol)->izq, nivel-1) + CantidadDeNodosHastaNivel(&(*arbol)->der, nivel-1);

}

int NivelNodo(tArbol *arbol, void *data, int (cmp)(void *, void *)){
    int cont=0, comparacion;

    ///devuelve el nivel del nodo buscado
     while(*arbol != NULL){
        comparacion = cmp(data, (*arbol)->data);
        if(comparacion > 0){
            arbol = &(*arbol)->der;
            cont++;
        }
        else if(comparacion < 0){
            arbol = &(*arbol)->izq;
            cont++;
        }
        else{
            return cont; ///ya existe el nodo
        }
    }
    return -1; ///no existe el nodo
}

void PodarHastaNivel(tArbol *arbolEntero, tArbol *arbol, int nivel, int (cmp)(void *, void *)){
    ///poda todos los nodos que esten en niveles mas altos que "nivel"
    if(*arbol == NULL){
        return;
    }
    PodarHastaNivel(arbolEntero, &(*arbol)->izq, nivel, cmp);
    PodarHastaNivel(arbolEntero, &(*arbol)->der, nivel, cmp);
    if(NivelNodo(arbolEntero, (*arbol)->data, cmp) > nivel){
        free((*arbol)->data);
        free(*arbol);
        *arbol = NULL;
    }
}
