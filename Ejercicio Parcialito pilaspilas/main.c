#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MiPila.h"
#include "MiLista.h"

void ProcesarPilas(tPila *, tPila *);

int main()
{
    tPila pilaT1;
    tPila pilaT2;
    tPila pilaT3;
    tPila pilaPilas;
    tPila pilaRes;

    tPila *pPilaT1 = &pilaT1;
    tPila *pPilaT2 = &pilaT2;
    tPila *pPilaT3 = &pilaT3;
    tPila *pPilaPilas = &pilaPilas;
    tPila *pPilaRes = &pilaRes;

    CrearPila(pPilaT1);
    CrearPila(pPilaT2);
    CrearPila(pPilaT3);
    CrearPila(pPilaPilas);
    CrearPila(pPilaRes);

    int auxEntero = 1;

    Apilar(pPilaT1, (void*)&auxEntero, sizeof(int));
    auxEntero = 2;
    Apilar(pPilaT1, (void*)&auxEntero, sizeof(int));
    auxEntero = 3;
    Apilar(pPilaT1, (void*)&auxEntero, sizeof(int));

    auxEntero = 4;
    Apilar(pPilaT2, (void*)&auxEntero, sizeof(int));
    auxEntero = 5;
    Apilar(pPilaT2, (void*)&auxEntero, sizeof(int));
    auxEntero = 6;
    Apilar(pPilaT2, (void*)&auxEntero, sizeof(int));

    auxEntero = 7;
    Apilar(pPilaT3, (void*)&auxEntero, sizeof(int));
    auxEntero = 8;
    Apilar(pPilaT3, (void*)&auxEntero, sizeof(int));
    auxEntero = 9;
    Apilar(pPilaT3, (void*)&auxEntero, sizeof(int));

    ///orden de salida de la pila deberia ser 9,8,7,6,5,4,3,2,1

    Apilar(pPilaPilas, pPilaT1, sizeof(tPila));
    Apilar(pPilaPilas, pPilaT2, sizeof(tPila));
    Apilar(pPilaPilas, pPilaT3, sizeof(tPila));

    ///apilo las pilas para hacer la prueba
    ///ahora tengo que hacer una funcion que ponga todas las pilas en una sola
    /*
    Desapilar(pPilaPilas, pPilaRes);
    Desapilar(pPilaRes, &auxEntero);
    printf("%d", auxEntero);
    Desapilar(pPilaRes, &auxEntero);
    printf("%d", auxEntero);
    Desapilar(pPilaRes, &auxEntero);
    printf("%d", auxEntero);
    */
    ProcesarPilas(pPilaPilas, pPilaRes);
}

void ProcesarPilas(tPila *pilasPilas, tPila *pilaResultante){

    tLista listaPilas;
    tLista listaEnteros;
    tLista *pListaPilas = &listaPilas;
    tLista *pListaEnteros = &listaEnteros;
    tPila pPilaAux;
    int auxEntero;

    CrearLista(pListaEnteros);
    CrearLista(pListaPilas);

    while(!PilaVacia(pilasPilas)){
        Desapilar(pilasPilas, &pPilaAux);
        Desapilar(&pPilaAux, &auxEntero);
        printf("%d\n", auxEntero);
        Desapilar(&pPilaAux, &auxEntero);
        printf("%d\n", auxEntero);
        Desapilar(&pPilaAux, &auxEntero);
        printf("%d\n", auxEntero);
    } ///agrego todas las pilas a la lista.

}
