#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MiListaDE.h"
#define CHARLNGTH 100

typedef struct{
    char nombre[CHARLNGTH];
    int id;
}parada;

typedef struct{
    int dni;
    char paradaAscenso[CHARLNGTH];
}pasajero;

int CmpNombreBajada(void *data1, void *data2){
    char *dataCast1 = (char *)data1;
    pasajero *dataCast2 = (pasajero *)data2;

    return strcmp(dataCast1, dataCast2->paradaAscenso);
}

int main()
{
    tListaDE listaParadas;
    tListaDE *pListaParadas = &listaParadas;
    CrearListaDE(pListaParadas);
    tListaDE listaPasajeros;
    tListaDE *pListaPasajeros = &listaPasajeros;
    CrearListaDE(pListaPasajeros);
    tNodo *paradaActual;
    parada paradaAux;
    parada *pParadaAux = &paradaAux;
    pasajero pasajeroAux;
    pasajero *pPasajeroAux = &pasajeroAux;
    int direccion = 0; ///0 hacia haedo 1 hacia ituzaingo
    int opcion;
    int dniAux;
    int seguir;
    int bajan;

    ///creo las paradas
    strcpy(pParadaAux->nombre, "ituzaingo");
    pParadaAux->id = 1;
    AgregarAlFinal(pListaParadas, pParadaAux, sizeof(parada));
    strcpy(pParadaAux->nombre, "castelar");
    pParadaAux->id = 2;
    AgregarAlFinal(pListaParadas, pParadaAux, sizeof(parada));
    strcpy(pParadaAux->nombre, "moron");
    pParadaAux->id = 3;
    AgregarAlFinal(pListaParadas, pParadaAux, sizeof(parada));
    strcpy(pParadaAux->nombre, "haedo");
    pParadaAux->id = 4;
    AgregarAlFinal(pListaParadas, pParadaAux, sizeof(parada));

    paradaActual = *pListaParadas;

    ///recorrer paradas infinitamente
    while(1){
        seguir = 0;
        pParadaAux = paradaActual->data;
        bajan = CantidadDeApariciones(pListaPasajeros, pParadaAux->nombre, CmpNombreBajada);
        for(int i = 0; i<bajan; i++){
            BuscarNodoYSacar(pListaPasajeros, pPasajeroAux, pParadaAux->nombre, CmpNombreBajada);
            printf("Pasajero Baja: %d\n", pPasajeroAux->dni);
        }

        system("pause");

        while(seguir != 1){
            system("cls");
            printf("Usted esta en %s\n", pParadaAux->nombre);
            printf("Cantidad de pasajeros: %d\n\n", CantidadElementos(pListaPasajeros));
            printf("Acciones: \n1.Subir Pasajero\n2.Terminar Recorrido\n3.Ir a la siguiente parada\n");
            scanf("%d", &opcion);
            switch(opcion){
            case 1:
                printf("Ingrese el dni del pasajero: ");
                scanf("%d", &dniAux);
                pPasajeroAux->dni = dniAux;
                strcpy(pPasajeroAux->paradaAscenso, pParadaAux->nombre);
                AgregarAlFinal(pListaPasajeros, pPasajeroAux, sizeof(pasajero));
                system("pause");
                break;

            case 2:
                DestruirLista(pListaParadas);
                return 0;
                break;

            case 3:
                seguir = 1;
                break;
            }

        }


        if(direccion == 0){
            paradaActual = paradaActual->sig;
        }
        else if(direccion == 1){
            paradaActual = paradaActual->ant;
        }

        if(paradaActual->sig == NULL){
            direccion = 1;
        }
        if(paradaActual->ant == NULL){
            direccion = 0;
        }

    }

}
