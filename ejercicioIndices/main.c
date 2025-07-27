#include <stdio.h>
#include <stdlib.h>
#include "MiArbol.h"
#define MAXNOMBRE 100

typedef struct{

    int dni;
    char nombre[MAXNOMBRE];

}tPersona;

typedef struct{

    int dni;
    int offset;

}indicePersona;

int CmpDni(void *data1, void *data2){
    tPersona *dataCast1 = (tPersona *)data1;
    tPersona *dataCast2 = (tPersona *)data2;

    if(dataCast1->dni > dataCast2->dni){
        return 1;
    }
    else if(dataCast1->dni < dataCast2->dni){
        return -1;
    }
    else{
        return 0;
    }

}

void MostrarPersona(void *data1){
    tPersona *dataCast1 = (tPersona *)data1;
    printf("Persona: %s, dni: %d\n", dataCast1->nombre, dataCast1->dni);
}

void MostrarPersonaIndice(void *data1){
    indicePersona *dataCast1 = (indicePersona *)data1;
    printf("Persona: dni: %d, offset: %d\n", dataCast1->dni, dataCast1->offset);
}

int main()
{
    ///crear archivo
    FILE *fp;
    tPersona per;
    tPersona *pPer = &per;
    indicePersona ip;
    indicePersona *pIp = &ip;
    tArbol arbolIndice;
    tArbol *pArbolIndice = &arbolIndice;
    CrearArbol(pArbolIndice);
    int cont = 0;

    /*
    fp = fopen("personas.dat", "wb");

    pPer->dni = 5;
    strcpy(pPer->nombre, "Franco");
    fwrite(pPer, sizeof(tPersona), 1, fp);

    pPer->dni = 7;
    strcpy(pPer->nombre, "Agus");
    fwrite(pPer, sizeof(tPersona), 1, fp);

    pPer->dni = 1;
    strcpy(pPer->nombre, "Joaco");
    fwrite(pPer, sizeof(tPersona), 1, fp);

    pPer->dni = 3;
    strcpy(pPer->nombre, "Camilo");
    fwrite(pPer, sizeof(tPersona), 1, fp);

    pPer->dni = 4;
    strcpy(pPer->nombre, "Facu");
    fwrite(pPer, sizeof(tPersona), 1, fp);

    pPer->dni = 10;
    strcpy(pPer->nombre, "Alejo");
    fwrite(pPer, sizeof(tPersona), 1, fp);

    */

    fp = fopen("personas.dat", "rb");
    while(fread(pPer, sizeof(tPersona), 1, fp) == 1){
        pIp->dni = pPer->dni;
        pIp->offset = cont;
        InsertarEnArbol(pArbolIndice, pIp, sizeof(indicePersona), CmpDni);
        cont++;
    }
    RecorrerInOrden(pArbolIndice, MostrarPersonaIndice);


}
