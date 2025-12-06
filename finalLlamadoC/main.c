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

    tLista p1;
    tLista *pP1 = &p1;

    CrearLista(pP1);


    FILE *fp = fopen("p1.txt", "r");
    while(fgets(linea, 10, fp) != NULL){
        sscanf(linea, "X(%d)(%d)", &pT->potencia, &pT->base);
        printf("Termino: %dX elevado a %d\n", pT->base, pT->potencia);
    }

    printf("%d", ListaVacia(pP1));

}
