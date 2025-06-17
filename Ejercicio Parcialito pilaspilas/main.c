#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MiPila.h"
#include "MiLista.h"

typedef struct{
    char nombre[20];
    int num;
}persona;

int main()
{
    tPila pila1;
    tPila *pPila1 = &pila1;
    CrearPila(pPila1);

    tPila pila2;
    tPila *pPila2 = &pila2;
    CrearPila(pPila2);

    tPila pila3;
    tPila *pPila3 = &pila3;
    CrearPila(pPila3);

    tPila pilaPilas;
    tPila *pPilaPilas = &pilaPilas;
    CrearPila(pPilaPilas);

    ///una pila que adentro guarda otras pilas.
    ///Una funcion que de la pila de pilas haga una pila entera

    tLista lista;
    tLista *pLista = &lista;
    CrearLista(pLista);

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

    void *pPres = malloc(sizeof(persona));
    persona *pRes;

    ///hago 3 pilas para poder probar
    Apilar(pPila1, pp1, sizeof(persona));
    Apilar(pPila1, pp2, sizeof(persona));
    Apilar(pPila1, pp3, sizeof(persona));

    Apilar(pPila2, pp4, sizeof(persona));
    Apilar(pPila2, pp5, sizeof(persona));
    Apilar(pPila2, pp6, sizeof(persona));

    Apilar(pPila3, pp7, sizeof(persona));
    Apilar(pPila3, pp8, sizeof(persona));

    ///apilo las pilas dentro de otra pila. PilaPilas!

    Apilar(pPilaPilas, pPila1, sizeof(tPila));
    Apilar(pPilaPilas, pPila2, sizeof(tPila));
    Apilar(pPilaPilas, pPila3, sizeof(tPila));


    ///desapilo y guardo en lista
    DesApilar(pPila1, pPres);
    pRes = (persona *)pPres;
    PonerAlFinal(pLista, pRes, sizeof(persona));

    DesApilar(pPila1, pPres);
    pRes = (persona *)pPres;
    PonerAlFinal(pLista, pRes, sizeof(persona));

    DesApilar(pPila1, pPres);
    pRes = (persona *)pPres;
    PonerAlFinal(pLista, pRes, sizeof(persona));

    ///saco de la lista
    SacarDelFinal(pLista, pPres);
    pRes = (persona *)pPres;
    printf("nombre: %s\n", pRes->nombre);

    SacarDelFinal(pLista, pPres);
    pRes = (persona *)pPres;
    printf("nombre: %s\n", pRes->nombre);

    SacarDelFinal(pLista, pPres);
    pRes = (persona *)pPres;
    printf("nombre: %s\n", pRes->nombre);
    ///deberia salir en el orden que fue cargado pp1 pp2 pp3

    ///para hacer esto necesito primero implementar pila con una estrucctura de datos que tenga una pila adentro
    ///luego guardar esa pila de alguna manera que me permita recorrerla en orden

    free(pPres);

}
