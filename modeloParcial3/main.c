#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"

typedef struct{

    int dni;
    int nro;

}indiceAlumno;

typedef struct{

    int dni;
    char apyn[40];
    int cant_materias;
    float promedio;
    char estado; ///'A' Activo - 'B' Baja

}alumno;


int cmpIndice(void *data1, void *data2){
    indiceAlumno *dataCast1 = (indiceAlumno *)data1;
    indiceAlumno *dataCast2 = (indiceAlumno *)data2;

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

int cmpIndiceDni(void *data1, void *data2){
    int *dataCast1 = (int *)data1;
    indiceAlumno *dataCast2 = (indiceAlumno *)data2;

    if(*dataCast1 > dataCast2->dni){
        return 1;
    }
    else if(*dataCast1 < dataCast2->dni){
        return -1;
    }
    else{
        return 0;
    }
}

void mostrarIndice(void *data1){
    indiceAlumno *dataCast1 = (indiceAlumno *)data1;

    printf("Indice: dni: %d, nro %d\n", dataCast1->dni, dataCast1->nro);
}

int main()
{
    int opcion, dni;
    tArbol arbolPruebas;
    tArbol *pArbolPruebas = &arbolPruebas;
    tArbol *aux;
    CrearArbol(pArbolPruebas);
    indiceAlumno ia;
    indiceAlumno *pIa = &ia;
    alumno a;
    alumno *pA = &a;

    ///cargo el arbol con el indice
    FILE *fp;
    fp = fopen("alumnos.idx", "r");
    while(!feof(fp)){
        fread(pIa, sizeof(indiceAlumno), 1, fp);
        InsertarEnArbol(pArbolPruebas, pIa, sizeof(indiceAlumno), cmpIndice);
    }
    fclose(fp);

    ///antes de iniciar el programa tengo que cargar todo el arbol con el indice



    ///menu
    while(1){
        printf("Menu\n1.Ver arbol\n2.Dar de baja alumno\n3.Vaciar arbol\n4.Ver Alumnos\n5.Salir\n");
        scanf("%d", &opcion);

        if(opcion == 1){
            RecorrerEnOrden(pArbolPruebas, mostrarIndice);
        }
        else if(opcion == 2){
            ///puntos 1 y 2 borrar el alumno del arbol indice. Acceder al registro desde el indice en el archivo .dat y modificarlo. Luego actualizar el idx con el nuevo indice.
            printf("Ingrese el dni del alumno a dar de baja");
            scanf("%d", &dni);
            ///pongo el alumno en el .dat como baja
            fp = fopen("alumnos.dat", "rb+");
            aux = BuscarRegistroPorClave(pArbolPruebas, &dni, cmpIndiceDni);
            if(fp != NULL && aux != NULL){
                fseek(fp, ((indiceAlumno *)((*aux)->data))->nro*sizeof(alumno), SEEK_SET);
                fread(pA, sizeof(alumno), 1, fp);
                pA->estado = 'B';
                fseek(fp, -sizeof(alumno), SEEK_CUR);
                fwrite(pA, sizeof(alumno), 1, fp);
                EliminarElemento(pArbolPruebas, &dni, cmpIndiceDni);
            }
            else{
                if(fp!= NULL){
                    fclose(fp);
                }
                printf("Archivo o elemento no encontrado volviendo al menu... \n");
            }

        }
        else if(opcion == 3){
            ///punto 3 vaciar el arbol completamente
            VaciarArbol(pArbolPruebas);
            *pArbolPruebas = NULL;
        }
        else if(opcion == 4){
            fp = fopen("alumnos.dat", "r");
            while(!feof(fp)){
                fread(pA, sizeof(alumno), 1, fp);
                printf("Alumno: %d, %s, estado: %c\n", pA->dni, pA->apyn, pA->estado);
            }
            fclose(fp);
        }
        else if(opcion == 5){
            break;
        }
        else{
            printf("Opcion invalida\n");
        }

    }



}
