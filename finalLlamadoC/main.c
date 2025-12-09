#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
    ///EJERCICIO POLINOMIOS
    ///Leo el archivo con los polinomios

    char linea[10];
    termino t;
    termino *pT = &t;

    termino t1;
    termino *pT1 = &t1;

    termino t2;
    termino *pT2 = &t2;

    tLista p1;
    tLista *pP1 = &p1;
    tLista p2;
    tLista *pP2 = &p2;

    tLista rFinal;
    tLista *pRFinal = &rFinal;

    CrearLista(pP1);
    CrearLista(pP2);



    CrearLista(pRFinal);


    FILE *fp = fopen("p1.txt", "r");
    while(fgets(linea, 10, fp) != NULL){
        sscanf(linea, "X(%d)(%d)", &pT->potencia, &pT->base);
        AgregarTerminoOrd(pP1, pT, sizeof(termino));
        ///printf("Termino: %dX elevado a %d\n", pT->base, pT->potencia);
    }
    fclose(fp);

    fp = fopen("p2.txt", "r");
    while(fgets(linea, 10, fp) != NULL){
        sscanf(linea, "X(%d)(%d)", &pT->potencia, &pT->base);
        AgregarTerminoOrd(pP2, pT, sizeof(termino));
        ///printf("Termino: %dX elevado a %d\n", pT->base, pT->potencia);
    }
    fclose(fp);


    tNodo *aux1 = *pP1;
    tNodo *aux2 = *pP2;

    printf("Leido del archivo 1\n");
    MostrarTodosLosDatos(pP1);
    printf("\n\n");
    printf("Leido del archivo 2\n");
    MostrarTodosLosDatos(pP2);


    ///juntar los dos polinomios y escribirlo en el archivo
    while(aux2 != NULL){
        memcpy(pT1, aux1->data, sizeof(termino));
        memcpy(pT2, aux2->data, sizeof(termino));
        if(pT1->potencia == pT2->potencia){
            pT1->base = pT1->base + pT2->base;
            AgregarTerminoOrd(pRFinal, pT1, sizeof(termino));
            aux1 = aux1->sig;
            aux2 = aux2->sig;
        }
        else if(pT1->potencia > pT2->potencia){
            AgregarTerminoOrd(pRFinal, pT1, sizeof(termino));
            aux1 = aux1->sig;
        }
        else{
            AgregarTerminoOrd(pRFinal, pT2, sizeof(termino));
            aux2 = aux2->sig;
        }
    }


    ///los que queden en la lista uno los agrego ordanadamente al final
    while(aux1 != NULL){
        memcpy(pT1, aux1->data, sizeof(termino));
        AgregarTerminoOrd(pRFinal, pT1, sizeof(termino));
        aux1 = aux1->sig;
    }


    printf("\n\n");
    MostrarTodosLosDatos(pRFinal);


    aux1 = *pRFinal;
    ///cargar el resultado al archivo
    fp = fopen("resultado.txt", "w");
    while(aux1 != NULL){
        memcpy(pT1, aux1->data, sizeof(termino));
        if(pT1->base > 0){
            fprintf(fp, "+ (%dX)**(%d)", pT1->base, pT1->potencia);
        }
        else{
            fprintf(fp, "(%dX)**(%d)", pT1->base, pT1->potencia);
        }
        aux1 = aux1->sig;
    }

}
