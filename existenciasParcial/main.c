#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MiArbol.h"
#include "MiLista.h"

typedef struct{
    int id_producto;
    char desc[30];
    float p_unitario;
    int existencias;
}existencias;

typedef struct{
    int id_producto;
    char tipo;
    int cantidad;
}operacion;

typedef struct{
    int id_producto;
    int balance;
}resumen;

int CmpId(void *data1, void *data2){
    indice *dataCast1 = (indice *)data1;
    indice *dataCast2 = (indice *)data2;
    if(dataCast1->id > dataCast2->id){
        return 1;
    }
    else if(dataCast1->id < dataCast2->id){
        return -1;
    }
    else{
        return 0;
    }
}

int CmpIdRes(void *data1, void *data2){
    resumen *dataCast1 = (resumen *)data1;
    resumen *dataCast2 = (resumen *)data2;
    if(dataCast1->id_producto > dataCast2->id_producto){
        return 1;
    }
    else if(dataCast1->id_producto < dataCast2->id_producto){
        return -1;
    }
    else{
        return 0;
    }
}

void MostrarIndice(void *data1){
    indice *dataCast1 = (indice *)data1;
    printf("Indice ID: %d, offset: %ld\n", dataCast1->id, dataCast1->offset);
}

void AcumularRes(void *data1, void *data2){
    resumen *dataCast1 = (resumen *)data1;
    resumen *dataCast2 = (resumen *)data2;

    dataCast1->balance = dataCast1->balance + dataCast2->balance;
}

int main()
{
    FILE *fp;
    /*
    ///cargar archivo existencias
    fp = fopen("maestro_de_existencias.dat", "wb");
    existencias auxExis;
    strcpy(auxExis.desc, "leche");
    auxExis.id_producto = 1;
    auxExis.p_unitario = 20;
    auxExis.existencias = 10;
    fwrite(&auxExis, sizeof(existencias), 1, fp);
    strcpy(auxExis.desc, "arroz");
    auxExis.id_producto = 2;
    auxExis.p_unitario = 20;
    auxExis.existencias = 3;
    fwrite(&auxExis, sizeof(existencias), 1, fp);
    strcpy(auxExis.desc, "carne");
    auxExis.id_producto = 3;
    auxExis.p_unitario = 30;
    auxExis.existencias = 5;
    fwrite(&auxExis, sizeof(existencias), 1, fp);
    strcpy(auxExis.desc, "fideos");
    auxExis.id_producto = 4;
    auxExis.p_unitario = 40;
    auxExis.existencias = 20;
    fwrite(&auxExis, sizeof(existencias), 1, fp);
    fclose(fp);

    ///cargar archivo movimientos
    fp = fopen("movimientos.dat", "wb");
    operacion auxOp;
    auxOp.id_producto = 1;
    auxOp.cantidad = 3;
    auxOp.tipo = 'i';
    fwrite(&auxOp, sizeof(operacion), 1, fp);
    auxOp.id_producto = 2;
    auxOp.cantidad = 4;
    auxOp.tipo = 'e';
    fwrite(&auxOp, sizeof(operacion), 1, fp);
    auxOp.id_producto = 3;
    auxOp.cantidad = 2;
    auxOp.tipo = 'i';
    fwrite(&auxOp, sizeof(operacion), 1, fp);
    auxOp.id_producto = 3;
    auxOp.cantidad = 1;
    auxOp.tipo = 'e';
    fwrite(&auxOp, sizeof(operacion), 1, fp);
    fclose(fp);
    */
    ///una vez cargados los archivos puedo comenzar con el ej.

    ///punto1 genere un indice (arbol)
    existencias auxEx;
    existencias *pAuxEx = &auxEx;
    tArbol indiceExistencias;
    tArbol *pIndiceExistencias = &indiceExistencias;
    CrearArbol(pIndiceExistencias);

    long offset;

    fp = fopen("maestro_de_existencias.dat", "rb");
    indice indexAux;
    indice *pIndexAux = &indexAux;
    while(!feof(fp)){
        fread(pAuxEx, sizeof(existencias), 1, fp);
        offset = ftell(fp) - sizeof(existencias);
        pIndexAux->id = pAuxEx->id_producto;
        pIndexAux->offset = offset;
        InsertarEnArbol(pIndiceExistencias, pIndexAux, sizeof(indice), CmpId);
    }
    fclose(fp);

    ///ej2
    fp = fopen("movimientos.dat", "rb");
    operacion auxOp;
    operacion *pAuxOp = &auxOp;
    resumen auxRes;
    resumen *pAuxRes = &auxRes;
    pAuxRes->balance = 0;
    tLista resumenes;
    tLista *pResumenes = &resumenes;
    CrearLista(pResumenes);
    while(!feof(fp)){
        fread(pAuxOp, sizeof(operacion), 1, fp);
        pAuxRes->id_producto = pAuxOp->id_producto;
        if(pAuxOp->tipo == 'i'){
            pAuxRes->balance = pAuxRes->balance + pAuxOp->cantidad;
        }
        else{
            pAuxRes->balance = pAuxRes->balance - pAuxOp->cantidad;
        }
        InsertarSinDuplicados(pResumenes, pAuxRes, sizeof(resumen), CmpIdRes, AcumularRes);
    }
    fclose(fp);

    ///ej4
    RecorrerInOrden(pIndiceExistencias, MostrarIndice);
}
