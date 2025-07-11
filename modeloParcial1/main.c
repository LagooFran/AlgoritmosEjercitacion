#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MiArbol.h"
#define MAXLEN 200

typedef struct{
    char nombre[50];
    int edad;
    int valor;
}persona;

int cmp(void *data1, void *data2){
    persona *dataCast1 = (persona *)data1;
    persona *dataCast2 = (persona *)data2;

    if(dataCast1->valor > dataCast2->valor){
        return 1;
    }
    else if(dataCast1->valor < dataCast2->valor){
        return -1;
    }
    else{
        return 0;
    }
}

int cmpdato(void *data1, void *data2){
    int *dataCast = (int*)data1;
    persona *dataCast2 = (persona *)data2;
    if(*dataCast == dataCast2->edad){
        return 0;
    }
    else{
        return -1;
    }
}

void mostrar(void *data){
    persona *dataCast = (persona*)data;
    printf("persona %s, %d, %d\n", dataCast->nombre, dataCast->edad, dataCast->valor);

}

int main()
{
    int valorTesteo = 21;
    tArbol arbol;
    tArbol *pArbol = &arbol;
    CrearArbol(pArbol);
    persona p;
    persona *pp = &p;
    char *aux;
    char linea[MAXLEN];
    FILE *fp;
    fp = fopen("archivo.csv", "r");
    if(!fp){
        printf("Archivo no encontrado");
        return -1;
    }
    printf("Cargando datos de csv\n");
    fgets(linea,MAXLEN,fp); ///tomo los encabezados
    while(fgets(linea,MAXLEN,fp)!=NULL){
        //fgets(linea, MAXLEN, fp);
        //printf("%s", linea);
        ///trozar campos
        aux = strrchr(linea, '\n');
        *aux = '\0';

        aux = strrchr(linea, ',');
        sscanf(aux+1, "%d", &(pp->valor));
        *aux = '\0';

        aux = strrchr(linea, ',');
        sscanf(aux+1, "%d", &(pp->edad));
        *aux = '\0';

        strcpy(pp->nombre, linea);


        InsertarEnArbol(pArbol, pp, sizeof(persona), cmp);
    }

    RecorrerInOrden(pArbol, mostrar);
    printf("Cantidad de apariciones: %d", ContarOcurrenciasNoClave(pArbol, &valorTesteo, cmpdato));
    EspejarArbol(pArbol);
    RecorrerInOrden(pArbol, mostrar);
    return 0;
}
