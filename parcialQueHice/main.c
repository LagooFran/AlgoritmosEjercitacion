#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "puntaje.h"

int main()
{
    ///leer los puntajes del archivo y declarar la lista
    char codigo[4];
    int puntaje;
    int tam;
    FILE *fp = fopen("puntajes.txt", "r");
    t_tabla_puntos tablaPuntos;
    t_tabla_puntos *pTablaPuntos = &tablaPuntos;

    t_puntaje ptos;
    t_puntaje *pPtos = &ptos;

    if(fp == NULL){
        printf("Error de lectura de archivo");
        return 0;
    }

    ///leo la cantidad del top N
    fscanf(fp, "%d", &tam);
    printf("Cantidad del TOP: %d\n\n", tam);
    crear_tabla_puntos(pTablaPuntos, tam);
    ///despues leo cada registro
    printf("Registros leidos: \n");
    while(fscanf(fp, "%s %d", codigo, &puntaje) != EOF){
        printf("cod: %s, %d\n", codigo, puntaje);
        strcpy(pPtos->iniciales, codigo);
        pPtos->puntaje = puntaje;
        agregar_puntaje(pTablaPuntos, pPtos);
    }

    imprimir_tabla_puntos(pTablaPuntos);


}
