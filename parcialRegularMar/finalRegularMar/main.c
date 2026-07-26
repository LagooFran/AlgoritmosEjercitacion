#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

typedef struct{
    char codigo[5];
    int destino;
    char tipo;
}ingreso;


int main()
{
    char categoria[4];
    char *auxPosicion;
    char linea[50];

    int cantidadPorDespacho, cantidadDeDestinos, destinoDesp;
    //ingreso ing;
    ingreso ing;
    ingreso *pIng = &ing;

    tNodo *lecturaActual;


    FILE *fp = fopen("operaciones.txt", "r");
    if(!fp){
        //error al abrir el archivo
        return -1;
    }
    //leo la primer linea
    fgets(linea, 50, fp);
    sscanf(linea, "%d,%d", &cantidadPorDespacho, &cantidadDeDestinos);
    printf("K = %d, D = %d\n", cantidadPorDespacho, cantidadDeDestinos);

    //creo un vector de listas para cada destino
    lista *paquetesIngresadosDestino;
    paquetesIngresadosDestino = malloc(cantidadDeDestinos * sizeof(lista));
    for(int i=0; i<cantidadDeDestinos; i++){
        CrearLista(&paquetesIngresadosDestino[i]);
    }

    //una vez leida la primer linea voy leyendo las demas
    while(fgets(linea, 50, fp) != NULL){
        strncpy(categoria, linea, 3);
        if(strcmp("ING", categoria)==0){
            printf("Ingreso Leido\n");
            //cargo en la lista
            auxPosicion = strrchr(linea, '|');
            sscanf(auxPosicion+1, "%c", &pIng->tipo);
            *auxPosicion = '\0';

            auxPosicion = strrchr(linea, '|');
            sscanf(auxPosicion+1, "%d", &pIng->destino);
            *auxPosicion = '\0';

            auxPosicion = strrchr(linea, '|');
            sscanf(auxPosicion+1, "%s", pIng->codigo);
            *auxPosicion = '\0';

            //cargo cada ingreso en su correspondiente lista
            AgregarAlFinal(&paquetesIngresadosDestino[pIng->destino-1], pIng, sizeof(ingreso));
        }
        else if(strcmp("DES", categoria)==0){
            printf("Despacho\n");
            //si ocurre un despacho tengo que quitar elementos de la lista del destino ccorrespondiente hasta que no queden
            //o se cumpla el maximo por despacho.
            auxPosicion = strrchr(linea, '|');
            sscanf(auxPosicion+1, "%d", &destinoDesp);
            *auxPosicion = '\0';
            printf("Destino: %d\n",destinoDesp);

            //extraigo el destino del despacho
            if(CantidadElementos(&paquetesIngresadosDestino[destinoDesp-1])==0){
                //despacho vacio
                FILE *fp2 = fopen("despachos_ineficientes.txt", "a");
                if(!fp){
                    //error al abrir el archivo
                    return -1;
                }
                fprintf(fp2,"DES|%d|VACIO\n", destinoDesp);
                fclose(fp2);
            }
            else if(CantidadElementos(&paquetesIngresadosDestino[destinoDesp-1])<cantidadPorDespacho){
                //despacho inccompleto
                FILE *fp2 = fopen("despachos_ineficientes.txt", "a");
                if(!fp){
                    //error al abrir el archivo
                    return -1;
                }
                fprintf(fp2,"DES|%d|INCOMPLETO|%d|%d\n", destinoDesp, cantidadPorDespacho, CantidadElementos(&paquetesIngresadosDestino[destinoDesp-1]));
                BorrarLista(&paquetesIngresadosDestino[destinoDesp-1]);
                fclose(fp2);
            }
            else{
                //despacho ok
                for(int i=0;i<cantidadPorDespacho;i++){
                    BorrarUltimoElemento(&paquetesIngresadosDestino[destinoDesp-1]);
                }
            }
        }

    }
    fclose(fp);
    //cuando termino de leer el archivo voy escribiendo ordenadamente los restantes
    FILE *fp3 = fopen("pendientes.txt", "a");
    for(int i=0; i<cantidadDeDestinos; i++){
        lecturaActual = paquetesIngresadosDestino[i];
        while(lecturaActual != NULL){
            pIng = lecturaActual->data;
            fprintf(fp3, "ING|%s|%d|%c\n", pIng->codigo, pIng->destino, pIng->tipo);
            lecturaActual = lecturaActual->sig;
        }
        BorrarLista(&paquetesIngresadosDestino[i]);
    }
    free(paquetesIngresadosDestino);
}
