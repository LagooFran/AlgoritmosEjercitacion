#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "lista.h"
#include <string.h>

typedef struct{
    int codigo;
    char fecha[9];
    char hora[7];
    int nivel;
}alerta;

typedef struct{
    int codigo;
    char fecha1[9];
    char hora1[7];
    char fecha3[9];
    char hora3[7];
}dispCritico;

int main()
{
    char linea[50];
    int codigoActual;
    lista criticos;
    lista *pCriticos = &criticos;
    CrearLista(pCriticos);
    lista alertas;
    lista *pAlertas = &alertas;
    CrearLista(pAlertas);
    alerta alertaLeida;
    alerta *pAlertaLeida = &alertaLeida;
    dispCritico nuevoCritico;
    dispCritico *pNuevoCritico = &nuevoCritico;
    int cantLeida=0;
    ///abro el archivo y leo los registros
    FILE *fp = fopen("eventos.txt", "r");
    if(!fp){
        return -1;
    }
    while(fgets(linea, 50, fp) != NULL){
        ///leo una linea
        sscanf(linea, "%3d|%8s|%6s|%1d", &pAlertaLeida->codigo, pAlertaLeida->fecha, pAlertaLeida->hora, &pAlertaLeida->nivel);
        if(codigoActual != pAlertaLeida->codigo){
            cantLeida=0;
            codigoActual = pAlertaLeida->codigo;
            VaciarLista(pAlertas);
        }
        else{
            if(pAlertaLeida->nivel == 5){
                cantLeida++;
                InsertarAlFinal(pAlertas, pAlertaLeida, sizeof(alertaLeida));
            }
        }
        if(cantLeida == 3){
            printf("Critico!\n");
            ///agrego un registro a la lista de criticos
            ExtraerUltimo(pAlertas, pAlertaLeida);
            pNuevoCritico->codigo = pAlertaLeida->codigo;
            strcpy(pNuevoCritico->fecha1, pAlertaLeida->fecha);
            strcpy(pNuevoCritico->hora1, pAlertaLeida->hora);
            ExtraerUltimo(pAlertas, pAlertaLeida);
            ExtraerUltimo(pAlertas, pAlertaLeida);
            strcpy(pNuevoCritico->fecha3, pAlertaLeida->fecha);
            strcpy(pNuevoCritico->hora3, pAlertaLeida->hora);
            InsertarAlFinal(pCriticos, pNuevoCritico, sizeof(dispCritico));
        }
    }

    ///una vez lei todo muestro por pantalla y escribo en el archivoo
    while(*pCriticos != NULL){
        ExtraerUltimo(pCriticos, pNuevoCritico);
        printf("Critico %d|%s|%s|%s|%s", pNuevoCritico->codigo, pNuevoCritico->fecha1, pNuevoCritico->hora1, pNuevoCritico->fecha3, pNuevoCritico->hora3);
    }
}
