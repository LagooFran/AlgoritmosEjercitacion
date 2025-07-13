#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"

typedef struct{
    char codLote[5];
    int id;
    char resul[6];
}produLote;

void mostrarProd(produLote *p){
    printf("Producto: cod %d, lote %s, control %s\n", p->id, p->codLote, p->resul);
}

void GenerarArchivos(tCola *colaOk, tCola *colaFallas, float porcMax){
    produLote pl;
    produLote *pPl = &pl;
    char stringNombre1[100];
    char stringNombre2[100];
    FILE *fp;

    ///armo los nombres
    sprintf(stringNombre1, "lotesObservados-%d.txt", (int)(porcMax*100));
    sprintf(stringNombre2, "lotesAprobados-%d.txt", (int)(porcMax*100));
    ///primero me fijo en que archivo iria el lote.
    float cantOk = CantDeElementosEnCola(colaOk);
    float cantFallas = CantDeElementosEnCola(colaFallas);
    float total = cantOk + cantFallas;
    float promFallas = (cantFallas)/total;
    printf("cant ok: %f, cant fallas %f, total %f\n", cantOk, cantFallas, total);
    printf("prom fallas %f\n", promFallas);
    if(promFallas >= porcMax){
        ///lote fallado
        ///inserto ordenadamente en el archivo
        fp = fopen(stringNombre1, "a");
        while(ColaVacia(colaFallas) != 1){
            SacarElemento(colaFallas, pPl);
            fprintf(fp,"%s,%d,%s\n", pPl->codLote, pPl->id,pPl->resul);
        }
        while(ColaVacia(colaOk) != 1){
            SacarElemento(colaOk, pPl);
            fprintf(fp,"%s,%d,%s\n", pPl->codLote, pPl->id,pPl->resul);
        }
        fclose(fp);
    }
    else{
        ///lote ok
        ///inserto ordenadamente en el archivo
        fp = fopen(stringNombre2, "a");
        while(ColaVacia(colaOk) != 1){
            SacarElemento(colaOk, pPl);
            fprintf(fp,"%s,%d,%s\n", pPl->codLote, pPl->id,pPl->resul);
        }
        while(ColaVacia(colaFallas) != 1){
            SacarElemento(colaFallas, pPl);
            fprintf(fp,"%s,%d,%s\n", pPl->codLote, pPl->id,pPl->resul);
        }
        fclose(fp);
    }
}

int main()
{
    tCola colaOk;
    tCola *pColaOk = &colaOk;
    CrearCola(pColaOk);
    tCola colaFallas;
    tCola *pColaFallas = &colaFallas;
    CrearCola(pColaFallas);
    produLote pl;
    produLote *pPl = &pl;
    char auxLectura[50];
    FILE *fp;
    float porcentajeFallas = 0.5; ///porcentaje por defecto
    int opcion, aux;
    char loteActual[5];
    char stringNombre1[100];
    char stringNombre2[100];

    printf("Porcentaje de fallas por defecto 50 porciento\n");
    sprintf(stringNombre1, "lotesObservados-%d.txt", (int)(porcentajeFallas*100));
    sprintf(stringNombre2, "lotesAprobados-%d.txt", (int)(porcentajeFallas*100));
    while(1){

        printf("Que desea hacer: \n1.Mostrar archivo de entrada completo\n2.Generar Archivos de salida\n3.Cargar porcentaje de fallas\n4.Mostrar Archivos generdaos\n5.Salir\n");
        scanf("%d", &opcion);

        if(opcion == 1){
            ///Leo el archivo y lo muestro FUNCION DE PRUEBA NO EXISTIRIA EN EL PROGRAMA REAL
            fp = fopen("entrada.bin", "rb");
            while(fread(pPl, sizeof(produLote), 1, fp) == 1){
                mostrarProd(pPl);
            }
            fclose(fp);
        }
        else if(opcion == 2){
            ///tengo que generar los 2 archivos uno con los lotes observados y otro con los lotes aprobados
            fp = fopen("entrada.bin", "rb");
            ///leo el primer registro
            aux = fread(pPl, sizeof(produLote), 1, fp);
            strcpy(loteActual, pPl->codLote);
            ///inserto el primer registro si fuera necesario:
            if(aux == 1){
                if(strcmp(pPl->resul, "OK") == 0){
                    InsertarEnCola(pColaOk, pPl, sizeof(produLote));
                }
                else{
                    InsertarEnCola(pColaFallas, pPl, sizeof(produLote));
                }
                while(fread(pPl, sizeof(produLote), 1, fp) == 1){
                    if(strcmp(loteActual, pPl->codLote) == 0){
                        if(strcmp(pPl->resul, "OK") == 0){
                            InsertarEnCola(pColaOk, pPl, sizeof(produLote));
                        }
                        else{
                            InsertarEnCola(pColaFallas, pPl, sizeof(produLote));
                        }
                    }
                    else{
                        ///cargo archivos
                        GenerarArchivos(pColaOk, pColaFallas, porcentajeFallas);
                        ///vacio colas
                        VaciarCola(pColaOk);
                        VaciarCola(pColaFallas);
                        CrearCola(pColaOk);
                        CrearCola(pColaFallas);

                        ///inserto el primer elemento del nuevo lote
                        if(strcmp(pPl->resul, "OK") == 0){
                            InsertarEnCola(pColaOk, pPl, sizeof(produLote));
                        }
                        else{
                            InsertarEnCola(pColaFallas, pPl, sizeof(produLote));
                        }
                        strcpy(loteActual, pPl->codLote);
                    }

                }
                ///ultimo lote
                ///cargo archivos
                GenerarArchivos(pColaOk, pColaFallas, porcentajeFallas);
                ///vacio colas
                VaciarCola(pColaOk);
                VaciarCola(pColaFallas);
                CrearCola(pColaOk);
                CrearCola(pColaFallas);
            }
            else{
                printf("Archivo Vacio");
            }

        }
        else if(opcion == 3){
            printf("Ingrese el nuevo porcentaje de fallas: ");
            scanf(" %f", &porcentajeFallas);
            porcentajeFallas = porcentajeFallas/100;
            printf("Nuevo seteo: %f", porcentajeFallas);
            sprintf(stringNombre1, "lotesObservados-%d.txt", (int)(porcentajeFallas*100));
            sprintf(stringNombre2, "lotesAprobados-%d.txt", (int)(porcentajeFallas*100));
        }
        else if(opcion == 4){
            fp = fopen(stringNombre1, "r");
            if(!fp){
                printf("aaa");
            }
            printf("Observados:\n");
            printf("LOTE,ID,ESTADO\n");
            while(fgets(auxLectura, 50, fp) != NULL){
                printf("%s\n",auxLectura);
            }
            fclose(fp);
            fp = fopen(stringNombre2, "r");
             if(!fp){
                printf("aaa");
            }
            printf("Aprobados:\n");
            printf("LOTE,ID,ESTADO\n");
            while(fgets(auxLectura, 50, fp) != NULL){
                printf("%s\n",auxLectura);
            }
            fclose(fp);
        }
        else if(opcion == 5){
            break;
        }
        else{
            printf("Opcion invalida");
        }
    }
}
