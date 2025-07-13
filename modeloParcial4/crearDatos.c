#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char codLote[5];
    int id;
    char resul[6];
}produLote;

void crearDatos(){
    produLote pl;
    produLote *pPl = &pl;
    FILE *fp;
    fp = fopen("entrada.bin", "wb");

    strcpy(pPl->codLote, "L001");
    pPl->id = 1;
    strcpy(pPl->resul, "OK");
    fwrite(pPl, sizeof(produLote), 1, fp);
    strcpy(pPl->codLote, "L001");
    pPl->id = 2;
    strcpy(pPl->resul, "OK");
    fwrite(pPl, sizeof(produLote), 1, fp);
    strcpy(pPl->codLote, "L001");
    pPl->id = 3;
    strcpy(pPl->resul, "OK");
    fwrite(pPl, sizeof(produLote), 1, fp);
    strcpy(pPl->codLote, "L001");
    pPl->id = 4;
    strcpy(pPl->resul, "OK");
    fwrite(pPl, sizeof(produLote), 1, fp);

    strcpy(pPl->codLote, "L002");
    pPl->id = 1;
    strcpy(pPl->resul, "OK");
    fwrite(pPl, sizeof(produLote), 1, fp);
    strcpy(pPl->codLote, "L002");
    pPl->id = 2;
    strcpy(pPl->resul, "FALLA");
    fwrite(pPl, sizeof(produLote), 1, fp);

    strcpy(pPl->codLote, "L003");
    pPl->id = 1;
    strcpy(pPl->resul, "OK");
    fwrite(pPl, sizeof(produLote), 1, fp);
    strcpy(pPl->codLote, "L003");
    pPl->id = 2;
    strcpy(pPl->resul, "OK");
    fwrite(pPl, sizeof(produLote), 1, fp);
    strcpy(pPl->codLote, "L003");
    pPl->id = 3;
    strcpy(pPl->resul, "OK");
    fwrite(pPl, sizeof(produLote), 1, fp);

    strcpy(pPl->codLote, "L004");
    pPl->id = 1;
    strcpy(pPl->resul, "OK");
    fwrite(pPl, sizeof(produLote), 1, fp);
    strcpy(pPl->codLote, "L004");
    pPl->id = 2;
    strcpy(pPl->resul, "FALLA");
    fwrite(pPl, sizeof(produLote), 1, fp);
    strcpy(pPl->codLote, "L004");
    pPl->id = 3;
    strcpy(pPl->resul, "FALLA");
    fwrite(pPl, sizeof(produLote), 1, fp);
    strcpy(pPl->codLote, "L004");
    pPl->id = 4;
    strcpy(pPl->resul, "FALLA");
    fwrite(pPl, sizeof(produLote), 1, fp);

    fclose(fp);

}
