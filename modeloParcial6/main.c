#include <stdio.h>
#include <stdlib.h>
#include "miArbol.h"
#define MAXLINEA 10

int EsLetra(char ltr){

    if(ltr >= 65 && ltr <= 90){
        return 1;
    }
    else if(ltr >= 97 && ltr <= 122){
        return 1;
    }
    else{
        return 0;
    }
}

int EsEspecial(char ltr){
    if(ltr == '\n' || ltr == '\0'){
        return 1;
    }
    else{
        return 0;
    }
}

int EsMayus(char ltr){
    if(ltr >= 65 && ltr <= 90){
        return 1;
    }
    else{
        return 0;
    }
}

int CmpPalabras(void *data1, void *data2){
    char *dataCast1 = (char *)data1;
    char *dataCast2 = (char *)data2;

    if(strcmp(dataCast1, dataCast2) > 0){
        return 1;
    }
    else if(strcmp(dataCast1, dataCast2) < 0){
        return -1;
    }
    else{
        return 0;
    }
}

void MostrarPal(void *data1){
    char *dataCast1 = (char *)data1;
    printf("%s\n", dataCast1);
}

int main()
{
    tArbol arbolA;
    tArbol *pArbolA = &arbolA;
    tArbol arbolB;
    tArbol *pArbolB = &arbolB;
    CrearArbol(pArbolA);
    CrearArbol(pArbolB);
    FILE *fp;
    char palabra[MAXLINEA];
    char ltr;
    int longitud;

    fp = fopen("A.txt", "r");
    while(( ltr = fgetc(fp)) >= 0){
        if(EsLetra(ltr) || EsEspecial(ltr)){
            if(EsMayus(ltr)){
                if(strlen(palabra)>0){
                InsertarEnArbol(pArbolA, palabra, sizeof(palabra), CmpPalabras);
                strcpy(palabra, "");
                }
            }
            if(EsLetra(ltr)){
            longitud = strlen(palabra);
            palabra[longitud] = ltr;
            palabra[longitud+1] = '\0';
            }
        }
        else{
            if(strlen(palabra)>0){
                InsertarEnArbol(pArbolA, palabra, sizeof(palabra), CmpPalabras);
                strcpy(palabra, "");
            }
        }
    }

    fp = fopen("B.txt", "r");
    while(( ltr = fgetc(fp)) >= 0){
        if(EsLetra(ltr) || EsEspecial(ltr)){
            if(EsMayus(ltr)){
                if(strlen(palabra)>0){
                InsertarEnArbol(pArbolB, palabra, sizeof(palabra), CmpPalabras);
                strcpy(palabra, "");
                }
            }
            if(EsLetra(ltr)){
            longitud = strlen(palabra);
            palabra[longitud] = ltr;
            palabra[longitud+1] = '\0';
            }
        }
        else{
            if(strlen(palabra)>0){
                InsertarEnArbol(pArbolB, palabra, sizeof(palabra), CmpPalabras);
                strcpy(palabra, "");
            }
        }
    }

    RecorrerInOrden(pArbolB, MostrarPal);
    printf("\n");
    RecorrerInOrden(pArbolA, MostrarPal);
    printf("\nDiferencia:\n");
    Diferencia(pArbolA, pArbolB, CmpPalabras, MostrarPal);
    ///faltaria agregar el archivo de texto para cumplir con todo lo q pide
    return 0;
}
