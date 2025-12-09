#include "lista.h"


void CrearLista(tLista *l){
    *l = NULL;
}

int ListaVacia(tLista *l){

    if(*l == NULL){
        return 1;
    }
    return 0;
}

void AgregarTerminoOrd(tLista *l, void *data, size_t dataSize){

    ///agrego un nodo ordenado por termino

    ///creo el nodo y el lugar para alojar la info

    tNodo *nuevoNodo;
    void *nuevaData;
    tNodo *aux = *l;
    tNodo *ant = NULL;
    termino valor1;
    termino valor2;
    termino *pValor1 = &valor1;
    termino *pValor2 = &valor2;


    nuevoNodo = (tNodo *)malloc(sizeof(tNodo));

    if(nuevoNodo == NULL){
        printf("Error de memoria");
        return;
    }

    nuevaData = malloc(dataSize);

    if(nuevaData == NULL){
        printf("Error de memoria");
        free(nuevoNodo);
        return;
    }

    ///creo el nuevo nodo
    memcpy(nuevaData, data, dataSize);
    nuevoNodo->data = nuevaData;
    nuevoNodo->datasize = dataSize;
    nuevoNodo->sig = NULL;

    if(ListaVacia(l)){
        *l = nuevoNodo;
    }
    else{
        while(aux != NULL){
            memcpy(pValor1, data, sizeof(termino));
            memcpy(pValor2, aux->data, sizeof(termino));
            if(pValor1->potencia < pValor2->potencia){
                ant = aux;
                aux = aux->sig;
                continue;
            }
            break;
        }

        if(ant == NULL){
             nuevoNodo->sig = aux;
             aux->sig = NULL;
             *l = nuevoNodo;
        }
        else{
            ant->sig = nuevoNodo;
            nuevoNodo->sig = aux;
        }
    }

}

void MostrarTodosLosDatos(tLista *l){

    tNodo *aux = *l;
    ///no necesario si fuera generico
    termino t;
    termino *pT = &t;


    while(aux != NULL){
        ///aca iria la parte generica que no llego...
        memcpy(pT, aux->data, sizeof(termino));
        printf("%dX**%d\n", pT->base, pT->potencia);
        aux = aux->sig;
    }

}
