#include <stdio.h>
#include <stdlib.h>

#include "MiLista.h"
#include "MiArbol.h"

typedef struct{
    char nombre[20];
    int num;
}persona;

int cmp(void* data, void* data2){

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

void AgregarNodosAltura(tArbol *raiz, tArbol *arbol, int altura, int (cmp)(void *, void *),  tLista *listaNodos){
    ///agrega todos los nodos que son de una altura a una lista
    if (*arbol) {
        ///recorro el arbol entero
        AgregarNodosAltura(raiz, &(*arbol)->izq, altura, cmp, listaNodos);

        printf("altura: %d\n", EncontrarAlturaNodo(raiz, (*arbol)->data, cmp));
        if(EncontrarAlturaNodo(raiz, (*arbol)->data, cmp) == altura){
            AgregarAlFinal(listaNodos, (*arbol)->data, (*arbol)->dataSize);
            printf("nodo agregado\n");
        }

        AgregarNodosAltura(raiz, &(*arbol)->der, altura, cmp, listaNodos);
    }
}

void BorrarNodosEnAltura(tArbol *arbol, int altura, int (cmp)(void *, void *)){
    ///wraper para la funcion que agrega los nodos a la lista
    ///agrego los nodos a una lista porque si empiezo a borrar de una los nodos se van a mover y termino borrando cosas que no van.
    tLista listaNodos;
    tLista *pListaNodos = &listaNodos;
    CrearLista(pListaNodos);
    int cont = 0;
    persona data;
    persona *pData = &data;

    AgregarNodosAltura(arbol, arbol, altura, cmp, pListaNodos);

    ///una vez cargue toda la lista de nodos
    while(!ListaVacia(pListaNodos)){
        SacarDelFinal(pListaNodos, pData);
        EliminarNodo(arbol, pData, cmp);
        cont++;
    }
    printf("\nNodos eliminados %d\n", cont);
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

    printf("Cantidad de nodos: %d\n\n", EncontrarCantidadNodos(pArbolPruebas));

    EliminarNodosSuperanAltura(pArbolPruebas, 4, 1);

    RecorrerEnOrden(pArbolPruebas, Mostrar);

    printf("\n");

    ///BorrarNodosEnAltura(pArbolPruebas, 3, cmp);

    ///RecorrerEnOrden(pArbolPruebas, Mostrar);

    return 0;
}
