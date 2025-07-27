#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#define MAXLEN 300
#define MAXTAG 100

typedef struct{
    char palabraInicio[MAXTAG];
}tagLeido;

typedef struct{
    int a;
    int b;
}test;

int main()
{
    tPila pilaTags;
    tPila *pPilaTags = &pilaTags;
    CrearPila(pPilaTags);
    int i;
    int leyendoTag;
    char auxPalabra[MAXTAG];
    char palabraTope[MAXTAG];
    strcpy(auxPalabra, "");
    int numLinea=1;
    char ltrAux[2];
    char linea[MAXLEN];
    char *pLinea = linea;
    char *pLineaAux;
    char lineaAux[MAXLEN];
    FILE *fp = fopen("archivoPrueba.xml", "r");
    strcpy(auxPalabra, "");
    int cierre=0;
    int cuentaPal=0;

    if(fp == NULL){
        printf("No se pudo abrir el archivo\n");
        return -1;
    }
    else{
        printf("Analizando archivo...\n");
        ///leo la primera linea par la version
        fgets(linea, MAXLEN, fp);
        pLineaAux = strchr(linea, '"');
        if(pLineaAux != NULL){
            *pLineaAux = '\0';
            strcpy(lineaAux, linea);
            if(strcmp(lineaAux, "<?xml version=") == 0){
                *pLineaAux = '"';
                pLineaAux = strrchr(linea, '"');
                strcpy(lineaAux, pLineaAux+1);
                if(strcmp(lineaAux, " >\n") == 0){
                }
                else{
                    printf("\nUn error fue encontrado en el archivo durante su lectura: Error de version\nEl tag de version no tiene el formato correcto\nRecuerde que el formato es <?xml version=\"version\" >\n\n");
                    return -1;
                }
            }
            else{
                printf("\nUn error fue encontrado en el archivo durante su lectura: Error de version\nNo fue posible encontrar la version de xml en el encabezado\nRecuerde que el formato es <?xml version=\"version\" >\n\n");
                return -1;
            }
        }
        else{
            printf("\nUn error fue encontrado en el archivo durante su lectura: Error de version\nNo fue posible encontrar la version de xml en el encabezado\nRecuerde que el formato es <?xml version=\"version\" >\n\n");
            return -1;
        }

        ///agregar codigo de chequeo...


        while(fgets(pLinea, MAXLEN, fp) != NULL){
            ///Leo el archivo linea por linea
            ///Leo la linea y me fijo si tiene tags <>
            strcpy(auxPalabra, "");
            for(i = 0; i<strlen(linea); i++){
                ///printf("%c", *pLinea);
                if(*pLinea == '<' && leyendoTag == 0){
                    ///es el comienzo de un nuevo TAG
                    leyendoTag = 1;
                }
                else if(leyendoTag == 1 && *pLinea != '>'){
                    ///leo la palabra que se encuentra dentro del tag
                    if(cuentaPal != 0){
                        ltrAux[0] = *pLinea;
                        strcat(auxPalabra, ltrAux);
                    }
                    else if(cuentaPal == 0 && *pLinea == '/'){
                        cierre = 1;
                    }
                    else{
                        ltrAux[0] = *pLinea;
                        strcat(auxPalabra, ltrAux);
                    }
                    cuentaPal++;
                }
                else if(leyendoTag == 1 && *pLinea == '>'){
                    ///cierre de tag
                    if(cierre == 0){
                        ///si no es un tag de cierre lo agrego a la pila
                        InsertarEnPila(pPilaTags, auxPalabra, sizeof(auxPalabra));
                    }
                    else{
                        ///si es tag de cierre compara si cierra en orden
                        VerTope(pPilaTags, palabraTope);
                        if(strcmp(palabraTope, auxPalabra) != 0){
                            printf("\nUn error fue encontrado en el archivo durante su lectura: Error de orden\nTag '%s' cerrado previo al cierre de tags con mayor jerarquia en linea %d\nOlvido cerrar algun tag '%s'?\n\n", auxPalabra, numLinea, palabraTope);
                            return -1;
                        }
                        else{
                            DesapilarSinLectura(pPilaTags);
                        }

                    }
                    //printf("Palabra: %s, cierre?: %d\n", auxPalabra, cierre);
                    strcpy(auxPalabra, "");
                    leyendoTag = 0;
                    cuentaPal = 0;
                    cierre = 0;
                }
                ///printf("cuenta pal: %d -- %c\n", cuentaPal, *pLinea);
                pLinea++;
            }
            pLinea = linea;
            strcpy(auxPalabra, "");
            if(leyendoTag == 1){
                ///si al final de una linea no termine de leer un tag
                printf("\nUn error fue encontrado en el archivo durante su lectura: Error de completado\nUn tag quedo incompleto al finalizar la linea %d\nRecuerde que el formato de los tags respeta <tag> o </tag>\n\n", numLinea);
                return -1;
            }
            numLinea++;
        }
        if(!PilaVacia(pPilaTags)){
            printf("\nUn error fue encontrado en el archivo durante su lectura: Error de falta cierre\nUn tag quedo sin finalizacion al terminar de leer el archivo\nOlvido cerrar algun tag?\n\n");
            return -1;
        }

    }
    printf("Archivo validado!\n");
    return 0;
}
