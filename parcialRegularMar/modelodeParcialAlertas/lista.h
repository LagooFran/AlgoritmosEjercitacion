#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct sNodo{
    void *data;
    size_t dataSize;
    struct sNodo *sig;
    struct sNodo *ant;
}tNodo;

typedef tNodo *lista;

int ListaVacia(lista *);
void CrearLista(lista *);
void InsertarAlFinal(lista *, void *, size_t);
void ExtraerUltimo(lista *, void *);
void VaciarLista(lista *);

#endif // LISTA_H_INCLUDED
