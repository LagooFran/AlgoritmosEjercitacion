#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MiLista.h"

typedef struct{
    int dia;
    int mes;
    int anio;
}fecha;

typedef struct{
    char patente[300]; ///mas espacio para acumular patentes
    char nroCuota[26]; ///cantidad de meses mas cantidad de comas mas 2 por las dudas para ir acumulando cuotas 1,2,3,4,5, etc
    char titular[25];
    int dni;
    fecha vto;
    float importe;
}registroDeuda;

int CompararFecha(fecha f1, fecha f2){
    int total1;
    int total2;

    total1 = f1.mes+f1.dia;
    total2 = f2.mes+f2.dia;

    if(f1.anio > f2.anio ){
        return 1;
    }
    else if(f1.anio < f2.anio){
        return -1;
    }
    else{
        if(total1 > total2){
            return 1;
        }
        else if(total1 < total2){
            return -1;
        }
        else{
            return 0;
        }
    }

}

void AcumularDeudas(void *data1Guardar, void *data2Acumular){
    registroDeuda *dataGuardar = (registroDeuda *)data1Guardar;
    registroDeuda *dataAcumular = (registroDeuda *)data2Acumular;

    if(strcmp(dataGuardar->patente, dataAcumular->patente) != 0){
        strcat(dataGuardar->patente, " - ");
        strcat(dataGuardar->patente, dataAcumular->patente);
    }

    strcat(dataGuardar->nroCuota, ",");
    strcat(dataGuardar->nroCuota, dataAcumular->nroCuota);

    dataGuardar->importe = dataGuardar->importe + dataAcumular->importe;

    ///comparo las fechas y me fijo cual es mayor
    if(CompararFecha(dataGuardar->vto, dataAcumular->vto) == 1){
        return;
    }
    else{
        dataGuardar->vto = dataAcumular->vto;
    }
}

int CmpDni(void *data1, void *data2){
    registroDeuda *dataCast1 = (registroDeuda *)data1;
    registroDeuda *dataCast2 = (registroDeuda *)data2;

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

int CmpDniyPatente(void *data1, void *data2){
    registroDeuda *dataCast1 = (registroDeuda *)data1;
    registroDeuda *dataCast2 = (registroDeuda *)data2;

    if(dataCast1->dni > dataCast2->dni){
        return 1;
    }
    else if(dataCast1->dni < dataCast2->dni){
        return -1;
    }
    else{
        if(strcmp(dataCast1->patente, dataCast2->patente)>0){
            return 1;
        }
        else if(strcmp(dataCast1->patente, dataCast2->patente)<0){
            return -1;
        }
        else{
            return 0;
        }
    }
}


int main()
{
    FILE *fp;
    fp = fopen("impuestosVencidos", "wb");
    tLista listaDeudas;
    tLista *pListaDeudas = &listaDeudas;
    CrearLista(pListaDeudas);
    tLista listaDeudasFinal;
    tLista *pListaDeudasFinal = &listaDeudasFinal;
    CrearLista(pListaDeudasFinal);
    int opcion;

    registroDeuda deudaAux;
    registroDeuda *pDeudaAux = &deudaAux;
    pDeudaAux->dni = 1;
    pDeudaAux->importe = 200;
    strcpy(pDeudaAux->patente, "AA123BB");
    strcpy(pDeudaAux->titular, "fran");
    pDeudaAux->vto.anio = 2024;
    pDeudaAux->vto.dia = 1;
    pDeudaAux->vto.mes = 1;
    strcpy(pDeudaAux->nroCuota, "3");
    fwrite(pDeudaAux, sizeof(registroDeuda), 1, fp);
    pDeudaAux->dni = 2;
    pDeudaAux->importe = 200;
    strcpy(pDeudaAux->patente, "AA124BB");
    strcpy(pDeudaAux->titular, "fran2");
    pDeudaAux->vto.anio = 2024;
    pDeudaAux->vto.dia = 1;
    pDeudaAux->vto.mes = 1;
    strcpy(pDeudaAux->nroCuota, "3");
    fwrite(pDeudaAux, sizeof(registroDeuda), 1, fp);
    pDeudaAux->dni = 1;
    pDeudaAux->importe = 200;
    strcpy(pDeudaAux->patente, "AA125BB");
    strcpy(pDeudaAux->titular, "fran");
    pDeudaAux->vto.anio = 2024;
    pDeudaAux->vto.dia = 1;
    pDeudaAux->vto.mes = 1;
    strcpy(pDeudaAux->nroCuota, "3");
    fwrite(pDeudaAux, sizeof(registroDeuda), 1, fp);
    pDeudaAux->dni = 1;
    pDeudaAux->importe = 200;
    strcpy(pDeudaAux->patente, "AA125BB");
    strcpy(pDeudaAux->titular, "fran");
    pDeudaAux->vto.anio = 2024;
    pDeudaAux->vto.dia = 1;
    pDeudaAux->vto.mes = 1;
    strcpy(pDeudaAux->nroCuota, "4");
    fwrite(pDeudaAux, sizeof(registroDeuda), 1, fp);

    fclose(fp);

    fp = fopen("impuestosVencidos", "rb");
    while(fread(pDeudaAux, sizeof(registroDeuda), 1, fp) == 1){
        AgregarAlFinal(pListaDeudas, pDeudaAux, sizeof(registroDeuda));
    }

    fclose(fp);

    printf("Que resumen desea generar\n1.Por dni\n2.Por dni y patente\n");
    scanf("%d", &opcion);

    switch(opcion){

    case 1:
        while(!ListaVacia(pListaDeudas)){
            SacarDelFinal(pListaDeudas, pDeudaAux);
            InsertarSinDuplicadosOrdenado(pListaDeudasFinal, pDeudaAux, sizeof(registroDeuda), CmpDni, AcumularDeudas);
        }
        fp = fopen("deuda.txt", "w");
        while(!ListaVacia(pListaDeudasFinal)){
            SacarDelFinal(pListaDeudasFinal, pDeudaAux);
            fprintf(fp,"Deuda: Dni: %d Importe: %f\n", pDeudaAux->dni, pDeudaAux->importe);
        }
        break;

    case 2:
        while(!ListaVacia(pListaDeudas)){
            SacarDelFinal(pListaDeudas, pDeudaAux);
            InsertarSinDuplicadosOrdenado(pListaDeudasFinal, pDeudaAux, sizeof(registroDeuda), CmpDniyPatente, AcumularDeudas);
        }
        fp = fopen("deuda.txt", "w");
        while(!ListaVacia(pListaDeudasFinal)){
            SacarDelFinal(pListaDeudasFinal, pDeudaAux);
            fprintf(fp,"Deuda: Dni/Patente: %d/%s Importe: %f\n", pDeudaAux->dni, pDeudaAux->patente, pDeudaAux->importe);
        }
        break;
    }
    ///hacer menu para el coso y ir acumulando y ordenando dependiendo de distintas condiciones... Al acumular se suman las cuotas y se preserva la fecha de vencimiento MAS CERCANA

    DestruirLista(pListaDeudas);
    DestruirLista(pListaDeudasFinal);
    return 0;
}
