
#include "MiArbol.h"

typedef struct{
    char nombre[20];
    int num;
}persona;

int cmp(const void* data, const void* data2){

    persona *dataCast = (persona*)data;
    persona *data2Cast = (persona*)data2;

    if(dataCast->num > data2Cast->num){
        return 1;
    }
    else if(dataCast->num < data2Cast->num){
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

    ///cargo un monton de personas para probar
    persona p1;
    persona *pp1 = &p1;
    strcpy(pp1->nombre, "Franco");
    pp1->num = 21;
    persona p2;
    persona *pp2 = &p2;
    strcpy(pp2->nombre, "Agus");
    pp2->num = 20;
    persona p3;
    persona *pp3 = &p3;
    strcpy(pp3->nombre, "Joaco");
    pp3->num = 24;
    persona p4;
    persona *pp4 = &p4;
    strcpy(pp4->nombre, "Camilo");
    pp4->num = 13;
    persona p5;
    persona *pp5 = &p5;
    strcpy(pp5->nombre, "Mariano");
    pp5->num = 1;
    persona p6;
    persona *pp6 = &p6;
    strcpy(pp6->nombre, "Alejo");
    pp6->num = 29;
    persona p7;
    persona *pp7 = &p7;
    strcpy(pp7->nombre, "Facu");
    pp7->num = 14;
    persona p8;
    persona *pp8 = &p8;
    strcpy(pp8->nombre, "Harry");
    pp8->num = 23;

    //persona pRes;
    //persona *ppRes = &pRes;

    CrearArbol(pArbolPruebas);

    InsertarEnArbol(pArbolPruebas, pp1, sizeof(persona), cmp);
    InsertarEnArbol(pArbolPruebas, pp2, sizeof(persona), cmp);
    InsertarEnArbol(pArbolPruebas, pp3, sizeof(persona), cmp);
    InsertarEnArbol(pArbolPruebas, pp4, sizeof(persona), cmp);
    InsertarEnArbol(pArbolPruebas, pp5, sizeof(persona), cmp);
    InsertarEnArbol(pArbolPruebas, pp6, sizeof(persona), cmp);
    InsertarEnArbol(pArbolPruebas, pp7, sizeof(persona), cmp);
    InsertarEnArbol(pArbolPruebas, pp8, sizeof(persona), cmp);


    RecorrerEnOrden(pArbolPruebas, Mostrar);

    printf("\n");

    EliminarNodo(pArbolPruebas, pp1, cmp);

    RecorrerEnOrden(pArbolPruebas, Mostrar);

    return 0;

}
