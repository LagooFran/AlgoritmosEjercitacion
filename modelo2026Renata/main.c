#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

int main()
{
    char linea[300];
    char lineaFinal[300];
    char dir[30];
    char *posicionActual;
    FILE *fp2;
    FILE *fp = fopen("rutas.txt", "r");
    tPila pila;
    tPila *pPila = &pila;
    CrearPila(pPila);
    int noApilar;
    int resScan;
    while(fgets(linea, 300, fp)){
        ///Lectura del linea
        //printf("\nleyendo %s", linea);

        ///separa los palabras y apilo
        while(posicionActual != linea){
            posicionActual=strrchr(linea, '/');
            resScan = sscanf(posicionActual+1, "%s", dir);
            if(resScan == 1 && noApilar != 1){
                if(strcmp(dir, "..") == 0){
                    noApilar = 1;
                }
                else{
                    if(strcmp(dir, ".") != 0){
                        InsertarEnPila(pPila, dir, 30);
                    }
                }
            }
            else if(resScan == 1){
                if(strcmp(dir, "..") != 0){
                    noApilar = 0;
                }
            }
            *posicionActual = '\0';
        }

        fp2 = fopen("salida.txt", "a");
        strcpy(lineaFinal, "");
        ///Genero la ruta final desapilando
        while(!PilaVacia(pPila)){
            Desapilar(pPila, dir);
            strcat(lineaFinal, "/");
            strcat(lineaFinal, dir);
        }
        if(strcmp(lineaFinal, "") == 0){
            strcpy(lineaFinal, "/");
        }
        printf("Final:      %s",lineaFinal);
        ///escribo el archivo de salida
        fprintf(fp2, "%s\n", lineaFinal);
        fclose(fp2);
        printf("\n");


        posicionActual = NULL;
    }

    fclose(fp);
    return 0;
}
