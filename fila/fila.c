#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila.h"
#include "../no/no.h"

struct fila
{
    int tamanho;
    NO *inicio;
    NO *fim;
};

FILA *fila_criar(void){

    FILA *fila = (FILA *)malloc(sizeof(FILA));

    if (fila != NULL)
    {
        fila->tamanho = 0;
        fila->inicio = NULL;
        fila->fim = NULL;
    }

    return fila;
}

bool fila_vazia(FILA *fila){
    if (fila != NULL)
    {
        return fila->tamanho == 0;
    }

    return false;

}


bool fila_cheia(FILA *fila){
    if (fila != NULL)
    {

        NO *tentativa = no_criar(NULL, NULL);

        if (tentativa == NULL)
        {
            return true;
        }

        free(tentativa);
        return false;
    }

    return false;
}


int fila_tamanho(FILA *fila){
    if (fila != NULL)
    {
        return fila->tamanho;
    }

    return -1;
}

void *fila_remover(FILA *fila){
    NO *no;
    if ((fila != NULL) && (!fila_vazia(fila)))
    {

        no = fila->inicio;

        void *no_valor = no_get_valor(no);

        fila->inicio = no_get_anterior(no);

        if (fila->inicio == NULL) {
            fila->fim = NULL;
        }
        no_remover(&no);

        fila->tamanho--;

        return no_valor;
    }

    return NULL;
}


bool fila_inserir(FILA *fila, void *valor){
    NO *no = no_criar(valor, NULL);

    if (no == NULL)
        return false;

    if ((fila != NULL) && (!fila_cheia(fila)))
    {
        if (fila_vazia(fila))
        {
            fila->inicio = no;
            fila->fim = no;
        }
        else
        {
            no_set_anterior(fila->fim, no);
            fila->fim = no;
        }

        fila->tamanho++;

        return true;
    }

    return false;
}

void fila_apagar(FILA **fila){
    if(fila_vazia(*fila)){
        free(*fila);
        *fila = NULL;
    }

    while (fila_tamanho(*fila) > 0)
    {
        NO *no_temp = fila_remover(*fila);
        // printf("valor_no: %s ", no_get_valor(no_temp));
        no_remover(&no_temp);
        no_set_anterior(no_temp, NULL);
        free(no_temp);
        no_temp = NULL;
    }

    free(*fila);
    *fila = NULL;
}

NO* fila_get_inicio(FILA *fila) {
    if (fila != NULL) {
        return fila->inicio;
    }
    return NULL;
}