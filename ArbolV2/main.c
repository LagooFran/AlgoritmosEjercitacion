
#include "MiArbol.h"
typedef struct{
    char nombre[20];
    int num;
}persona;

int cmp(const void* data, const void* data2){

    int *dataCast = (int*)data;
    int *data2Cast = (int*)data2;

    if(*dataCast > *data2Cast){
        return 1;
    }
    else if(*dataCast < *data2Cast){
        return -1;
    }
    else{
        return 0;
    }
}

void Mostrar(const void *data){
    persona *dataCast = (persona*)data;
    printf("Persona: %s, Nro: %d\n", dataCast->nombre, dataCast->num);
}

int main()
{
    ///Prueba de primitivas arbol binario
    tArbol arbolPruebas;
    tArbol *pArbolPruebas = &arbolPruebas;

    persona p1;
    persona *pp1 = &p1;
    strcpy(pp1->nombre, "Franco");
    pp1->num = 21;
    persona p2;
    persona *pp2 = &p2;
    strcpy(pp2->nombre, "Agus");
    pp2->num = 20;

    CrearArbol(pArbolPruebas);

    printf("Arbol: %d\n", ArbolVacio(pArbolPruebas));
    InsertarEnArbol(pArbolPruebas, pp1, sizeof(persona), cmp);
    printf("Arbol: %d\n", ArbolVacio(pArbolPruebas));
    InsertarEnArbol(pArbolPruebas, pp2, sizeof(persona), cmp);
    printf("Arbol: %d\n", ArbolVacio(pArbolPruebas));

    RecorrerEnOrden(pArbolPruebas, Mostrar);
    RecorrerEnPosOrden(pArbolPruebas, Mostrar);
    RecorrerEnPreOrden(pArbolPruebas, Mostrar);


    return 0;

}
