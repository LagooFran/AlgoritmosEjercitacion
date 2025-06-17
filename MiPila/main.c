#include <stdio.h>
#include <stdlib.h>
#include "MiPila.h"

typedef struct{
    char nombre[20];
    int num;
}persona;



int main()
{
    ///implementacion de pila testeo
    tPila pilaPruebas;
    tPila *pPilaPruebas = &pilaPruebas;

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

    void * pPres = malloc(sizeof(persona));
    persona *pRes;

    CrearPila(pPilaPruebas);
    Apilar(pPilaPruebas, pp1, sizeof(persona));
    Apilar(pPilaPruebas, pp2, sizeof(persona));
    Apilar(pPilaPruebas, pp3, sizeof(persona));

    DesApilar(pPilaPruebas, pPres);
    pRes = (persona *)pPres;
    printf("nombre: %s\n", pRes->nombre);
    DesApilar(pPilaPruebas, pPres);
    pRes = (persona *)pPres;
    printf("nombre: %s\n", pRes->nombre);
    DesApilar(pPilaPruebas, pPres);
    pRes = (persona *)pPres;
    printf("nombre: %s\n", pRes->nombre);
}
