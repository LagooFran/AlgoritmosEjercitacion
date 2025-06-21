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

int CmpIdIndice(void *data1, void *data2){
    int *dataCast1 = (int *)data1;
    indice *dataCast2 = (indice *)data2;
    if(*dataCast1 > dataCast2->id){
        return 1;
    }
    else if(*dataCast1 < dataCast2->id){
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
    auxOp.cantidad = 1;
    auxOp.tipo = 'i';
    fwrite(&auxOp, sizeof(operacion), 1, fp);
    auxOp.id_producto = 1;
    auxOp.cantidad = 4;
    auxOp.tipo = 'e';
    fwrite(&auxOp, sizeof(operacion), 1, fp);
    auxOp.id_producto = 2;
    auxOp.cantidad = 1;
    auxOp.tipo = 'i';
    fwrite(&auxOp, sizeof(operacion), 1, fp);
    auxOp.id_producto = 3;
    auxOp.cantidad = 1;
    auxOp.tipo = 'e';
    fwrite(&auxOp, sizeof(operacion), 1, fp);
    fclose(fp);

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

    ///ej2 generar una lista con los resumenes de los movimientos
    fp = fopen("movimientos.dat", "rb");
    operacion auxOp2;
    operacion *pAuxOp2 = &auxOp2;
    resumen auxRes;
    resumen *pAuxRes = &auxRes;
    pAuxRes->balance = 0;
    tLista resumenes;
    tLista *pResumenes = &resumenes;
    CrearLista(pResumenes);
    while(fread(pAuxOp2, sizeof(operacion), 1, fp)==1){
        pAuxRes->balance = 0;
        pAuxRes->id_producto = pAuxOp2->id_producto;
        if(pAuxOp2->tipo == 'i'){
            pAuxRes->balance = pAuxRes->balance + pAuxOp2->cantidad;
        }
        else{
            pAuxRes->balance = pAuxRes->balance - pAuxOp2->cantidad;
        }
        InsertarSinDuplicados(pResumenes, pAuxRes, sizeof(resumen), CmpIdRes, AcumularRes);
    }
    fclose(fp);

    ///ej3 actualizar el archivo de existencias utilizando el indice
    fp = fopen("maestro_de_existencias.dat", "rb+");
    long offsetBusqueda = 0;
    int auxId;
    int *pAuxId = &auxId;
    indice indiceRes;
    indice *pIndiceRes = &indiceRes;
    existencias exisLeida;
    existencias *pExisLeida = &exisLeida;

    while(!ListaVacia(pResumenes)){
        SacarDelFinal(pResumenes, pAuxRes);
        auxId = pAuxRes->id_producto;
        BuscarEnArbol(pIndiceExistencias, pIndiceRes, pAuxId, CmpIdIndice);
        offsetBusqueda = pIndiceRes->offset;
        fseek(fp, offsetBusqueda, SEEK_SET);
        fread(pExisLeida, sizeof(existencias), 1, fp);
        pExisLeida->existencias = pExisLeida->existencias + pAuxRes->balance;
        fseek(fp, offsetBusqueda, SEEK_SET);
        fwrite(pExisLeida, sizeof(existencias), 1, fp);
        printf("Existencia actualizada ID %d, nueva cantidad %d\n", pExisLeida->id_producto, pExisLeida->existencias);
    }

    fclose(fp);

    ///ej4 mostrar in orden el indice
    RecorrerInOrden(pIndiceExistencias, MostrarIndice);
}
